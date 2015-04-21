using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using ZedGraph;
using System.Xml.Linq;

namespace iKlwa_Telemetry_System
{
    public partial class UserInterface : Form
    {
        private TelemetryDatabase d;
        private TelemetryCommsManager comms = new TelemetryCommsManager();
        private ReaderWriterLock protection = new ReaderWriterLock();
        private enum SENSORS :int{HALL_EFFECT = 420, MOTOR_DRIVER = 421,
                                  BMS, GYRO, MPPT1,
                                  MPPT2, MPPT3, MPPT4,GPS,
                                  SOLAR_CELL, ANEMOMETER}
        private ReportScreen output;
        private bool safe_to_close = true;
        private int unreadErrorCount = 0;
        private bool db_exists = false;
        private string[] error_messages = new string[15];//only show up to 15 error messages at a time unless error report is requested
        private enum TABS : byte {Summary = 1, Graphing = 2,
                                  Motion = 3, Electrical = 4,
                                  Support = 5, RF = 6}
        private TABS selected_tab = TABS.Summary;//keeps track of which tab is selected
        private const string NO_SENSORS_MSG = "No sensors found...";

        public UserInterface()
        {
            InitializeComponent();
            d = new TelemetryDatabase("xmlDatabase_V5.xml");
            d.NodeTag = "Capture";
            db_exists = true;
            refresh_timer.Enabled = true;
        }

        /// <summary>
        /// Connects to the Follower Car Embedded System
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button1_Click(object sender, EventArgs e)
        {
            COM_Port_Select COM_Select = new COM_Port_Select();
            COM_Select.ShowDialog();

            if (COM_Select.NoPortsFound == false)
            {
                comms.name = COM_Select.Port;
                btn_COMPortConnect.ForeColor = Color.Green;
                btn_COMPortConnect.Text = "Connected";
                SerialReadingThread.RunWorkerAsync();
            }
        }

        private void refreshGUI()
        {
            if (db_exists == true)
            try
            {
                protection.AcquireReaderLock(10000);//lock reader
                try
                {
                    string x = null;
                    //refreshing takes place based on selected tab
                    //this prevents querying data from the database that won't need to be displayed
                    //less data queried at a time = better performance
                    switch (selected_tab)
                    {
                        case TABS.Graphing:
                            {
                                getSensors();//keep repopulating sensors
                            }
                            break;

                        case TABS.Summary:
                            {
                                //this is under test. currently only shows HE Speed on a label
                                try
                                {
                                    x = d.getLatestValue("Motor Driver", "Speed");
                                    lbl_instSpeed.Text = x;
                                }
                                catch (Exception error)
                                {
                                    //MessageBox.Show(error.Message);
                                }
                            }
                            break;

                        case TABS.Electrical:
                            break;

                        case TABS.Motion:
                                try
                                {
                                    x = d.getLatestValue("Motor Driver", "Speed");
                                    label12.Text = x;
                                    x = d.getLatestValue("Hall Effect Sensor", "Speed");
                                    label1.Text = x;
                                }
                                catch (Exception error)
                                {
                                    //MessageBox.Show(error.Message);
                                }
                            break;

                        case TABS.Support:
                            break;

                        case TABS.RF:
                            break;
                    }
                }
                finally { protection.ReleaseReaderLock(); } //ensure reader lock is released
            }
            catch(ApplicationException xx)
            { MessageBox.Show(xx.Message); }

        }

        /// <summary>
        /// Event that occurs every 1s that will update the GUI
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void refresh_timer_Tick(object sender, EventArgs e)
        {
            refreshGUI();//refresh GUI method

            //if (unreadErrorCount<15) unreadErrorCount++;//debugging purposes
            if (unreadErrorCount > 0)//update error messages notifications
            {
                btn_ErrorNotifications.ForeColor = Color.Red;
                btn_ErrorNotifications.Text = unreadErrorCount + " New Warnings.";
                taskbar_notification.Visible = true;
            }
        }

        #region not sure how to make this work...
        private delegate IEnumerable<XElement> ReadReq(ref IEnumerable<XElement> xe);

        private IEnumerable<XElement> DB_READ(ReadReq toDo)
        {
            IEnumerable<XElement> xe = null;
            try
            {
                protection.AcquireReaderLock(100);
                try {toDo(ref xe);}
                finally {protection.ReleaseReaderLock();}
            }
            catch (ApplicationException app)
            {
                MessageBox.Show(app.Message);
            }
            return xe;
        }
        #endregion

        /// <summary>
        /// Generate an Error Messages Report
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button2_Click(object sender, EventArgs e)
        {
            //test error message query
            IEnumerable<XElement> errors = null;
            try
            {
                protection.AcquireReaderLock(100);
                try { errors = d.getErrors(); }
                finally { protection.ReleaseReaderLock(); }
            }
            catch (ApplicationException app)
            {
                MessageBox.Show(app.Message);
            }

            List<string> headers = new List<string>(),
                         values = new List<string>();
            foreach (var err in errors)
            {
                foreach (var val in err.Descendants())
                {
                    if (!headers.Contains(val.Name.ToString()))
                        headers.Add(val.Name.ToString());
                    values.Add(val.Value);
                }
            }
            ReportScreen output = new ReportScreen();
            try 
            {
                output.setTitle("Error Report");
                output.Populate(headers, values);
                output.ShowDialog();
            }
            catch(ArgumentException a)
            { MessageBox.Show(a.Message); }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            GraphPane gp = zedGraphControl1.GraphPane;
            gp.CurveList.Clear();
            PointPairList listPoints = new PointPairList();
            LineItem line_item;
            IEnumerable<XElement> results = null;
            try
            {
                protection.AcquireReaderLock(100);
                try
                {
                    results = d.queryRange_valOnly(comboBox1.SelectedItem.ToString(),
                                     numericUpDown1.Value + "h" + numericUpDown3.Value,
                                     numericUpDown4.Value + "h" + numericUpDown2.Value);
                    
                }
                finally
                {
                    protection.ReleaseReaderLock();
                }

            }
            catch (ApplicationException err)
            {
                MessageBox.Show(err.Message);
            }
            int x = 0;
            foreach (var item in results)
            {
                foreach (var thing in item.Descendants(TelemetryDatabase.VAL_TAG))
                {
                    listPoints.Add(x++, Convert.ToDouble(thing.Value));
                }
                foreach (var thing in item.Descendants(TelemetryDatabase.DESCRIP_TAG))
                {
                    gp.YAxis.Title.Text = thing.Value;
                }
            }
            line_item = gp.AddCurve(null, listPoints, Color.LightSeaGreen, SymbolType.None);
            line_item.Line.Width = 1;
            gp.Title.Text = gp.YAxis.Title.Text + " vs Time";
            gp.XAxis.Title.Text = "Time";
            //gp.YAxis.Title.Text = y_axis;
            zedGraphControl1.AxisChange();
            zedGraphControl1.Invalidate();
            zedGraphControl1.Refresh();

            List<string> headers = new List<string>(),
                         values = new List<string>();
            foreach (var res in results)
            {
                foreach (var val in res.Descendants())
                {
                    if (!headers.Contains(val.Name.ToString()))
                        headers.Add(val.Name.ToString());
                    values.Add(val.Value);
                }
            }

            
            try
            {
                output = new ReportScreen();
                output.Populate(headers, values);
                output.Show();
                output.setTitle("Raw Data Entries");
            }
            catch (ArgumentException a)
            { MessageBox.Show(a.Message); }
        }

        private void getSensors()
        {
            if (comboBox1.Items.Contains(NO_SENSORS_MSG)) //if the no sensors message is in the combo box, remove it
                comboBox1.Items.Remove(NO_SENSORS_MSG);
            var sensorGroup = d.getSensors();
            foreach (var sensor in sensorGroup)
            {
                if (comboBox1.Items.Contains(sensor.Key) == false)
                    comboBox1.Items.Add(sensor.Key); //add sensors to combo box if they are not contained in there 
            }
        }

        private void UserInterface_Load(object sender, EventArgs e)
        {
            var sensorGroup = d.getSensors();
            if (sensorGroup.Count() == 0) //check if any sensors found and display message if not
            {
                comboBox1.Items.Add(NO_SENSORS_MSG);
            }
            else //populate combo box
                foreach (var sensor in sensorGroup)
                {
                    comboBox1.Items.Add(sensor.Key);
                }
        }


        /// <summary>
        /// Occurs when the user has selected a sensor to query for graphing data. Enables the "Create Graph" report.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            button6.Enabled = true;
        }

        /// <summary>
        /// Background Thread which handles reading from the COM Port and writing to the Database
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {
            comms.MavLinkInit();
            //comms.defaultInit();
            const long timeoutVal = 100000;//if cannot receive a packet after this number of trials, probably a loss of connection. Test?
            long count = 0;//to compare to timeoutVal
            try
            {
                comms.OpenPort();//open COM Port
                while (count<timeoutVal)
                {
                    count++;//increment timeout counter
                    var packet = comms.readTelemetryInput(); //read telemetry input
                    try
                    {
                        //may want to implement writer lock in addDataCapture...?

                        protection.AcquireWriterLock(200);//lock writer
                        try
                        {
                            safe_to_close = false;
                            switch (packet.ID)//determine sensor based on packet ID
                            {
                                case (int)SENSORS.MOTOR_DRIVER:
                                    {
                                        string str = packet.PAYLOAD.ElementAt(0).ToString();
                                        str = str.Substring(0, 1);
                                        d.addDataCapture("Motor Driver", DateTime.Now.Hour + "h" + DateTime.Now.Minute,
                                                         "Speed", (int)Convert.ToChar(str));
                                    }
                                    break;
                                case (int)SENSORS.HALL_EFFECT:
                                    {
                                        string str = packet.PAYLOAD.ElementAt(0).ToString();
                                        str = str.Substring(0, 1);
                                        d.addDataCapture("Hall Effect Sensor", DateTime.Now.Hour + "h" + DateTime.Now.Minute,
                                                         "Speed", (int)Convert.ToChar(str));

                                    } 
                                    break;

                                case (int)SENSORS.BMS:
                                    { }
                                    break;

                                case (int)SENSORS.GYRO:
                                    { }
                                    break;
                                
                                case (int)SENSORS.MPPT1:
                                case (int)SENSORS.MPPT2:
                                case (int)SENSORS.MPPT3:
                                case (int)SENSORS.MPPT4:
                                    { }
                                    //look to implement generic MPPT function with a different code for each of the 4
                                    //structure of MPPT data entry will essentially be the same
                                    break;

                                case (int)SENSORS.GPS:
                                    { }
                                    break;

                                case (int)SENSORS.SOLAR_CELL:
                                    { }
                                    break;

                                case (int)SENSORS.ANEMOMETER:
                                    { }
                                    break;

                                default:
                                    {
                                        d.addErrorCapture("Support Car Receiver", DateTime.Now.Hour + "h" + DateTime.Now.Minute,
                                                          "Sensor packet with invalid ID detected", "Data Error");
                                    }
                                    break;
                            }
                            count = 0;//if code reaches here, there was a successful write and the timeout counter is cleared.
                        }
                        finally
                        {
                            protection.ReleaseWriterLock();//ensure WriterLock is always released
                            safe_to_close = true;
                        }
                    }
                    catch (ApplicationException error)//Exception from WriterLockTimeout
                    { MessageBox.Show(error.Message); } 
                }
                //MessageBox.Show("thread completed");//debug msg
            }
            catch (Exception err)//Exception from opening COM Port or any other event that wasn't considered
            {
                MessageBox.Show(err.Message);
            }
        }

        /// <summary>
        /// Occurs when Summary Tab is activated.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tabPage6_Enter(object sender, EventArgs e)
        {
            selected_tab = TABS.Summary;//indicate that the summary tab was selected
        }

        /// <summary>
        /// Occurs when Solar Car Motion Tab is activated.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tabPage1_Enter(object sender, EventArgs e)
        {
            selected_tab = TABS.Motion;
        }


        private void btn_ErrorNotifications_TextChanged(object sender, EventArgs e)
        {
            if (btn_ErrorNotifications.ForeColor.Equals(Color.Red))
            {
                taskbar_notification.ShowBalloonTip(10, "Solar Car Warning Message",
                                                    "You have " + unreadErrorCount + " New Warning Messages." +
                                                    "\n\nClick here to display.",
                                                    ToolTipIcon.Warning);
            }
        }

        private void btn_ErrorNotifications_Click(object sender, EventArgs e)
        {
            unreadErrorCount = 0;
            btn_ErrorNotifications.Text = "No New Warnings";
            btn_ErrorNotifications.ForeColor = Color.Black;
            taskbar_notification.Visible = false;
        }

        private void UserInterface_FormClosing(object sender, FormClosingEventArgs e)
        {
            while (safe_to_close == false);//nop nop nop!!
        }

        /// <summary>
        /// Occurs when Graph Tab is activated. Populates all user-definable controls.
        /// Also enables refreshing of user-definable controls every timer tick.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void tabPage5_Enter(object sender, EventArgs e)
        {
            getSensors();//populate sensor select combo box

            //set numeric updowns so that the default is for the last hour of receiving data
            numericUpDown4.Value = DateTime.Now.Hour;
            numericUpDown2.Value = DateTime.Now.Minute;
            numericUpDown1.Value = DateTime.Now.Hour - 1;
            numericUpDown3.Value = DateTime.Now.Minute;
            selected_tab = TABS.Graphing;//indicate that the graphing tab was selected
        }

        private void tabPage4_Enter(object sender, EventArgs e)
        {
            selected_tab = TABS.Support;
        }

        private void tabPage3_Enter(object sender, EventArgs e)
        {
            selected_tab = TABS.RF;
        }

        private void tabPage2_Enter(object sender, EventArgs e)
        {
            selected_tab = TABS.Electrical;
        }

    }
}
