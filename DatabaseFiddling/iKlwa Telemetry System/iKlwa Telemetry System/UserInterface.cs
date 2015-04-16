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
        private ReaderWriterLock protection = new ReaderWriterLock();
        private ReportScreen output = new ReportScreen();
        private int counter;//naughty
        string[] list = new string[1];//naughty
        private const string NO_SENSORS_MSG = "No sensors found...";

        public UserInterface()
        {
            InitializeComponent();
            d = new TelemetryDatabase("DemoDb.xml");
            d.NodeTag = "Capture";
        }

        private void button1_Click(object sender, EventArgs e)
        {

        }

        /// <summary>
        /// Event that occurs every 1s that will update the GUI
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void refresh_timer_Tick(object sender, EventArgs e)
        {
            getSensors();

            //naughty things
            if (counter!=list.Length)
            lbl_instSpeed.Text = list[counter++];
            
        }

        /// <summary>
        /// Secret Simulation/Debug Mode - generate data to textfile, read and store to database.
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void pictureBox1_DoubleClick(object sender, EventArgs e)
        {
            try
            {
                protection.AcquireWriterLock(100);
                try
                {
                    MessageBox.Show("Now Entering Simulation Mode.");
                    Simulator s = new Simulator();
                    s.simData();
                    MessageBox.Show("Simulation Data Generated.\n\nNow storing to database");
                    string[,] data = s.getData();

                    for (int rows = 0; rows < 1438; rows++)
                    {
                        d.simulateErrorCapture("RF_Link", "Comms", "Communication Lost");
                        d.addDataCapture("Speed_Sensor", data[rows, 2], data[rows, 0], data[rows, 3]);
                    }
                }
                finally
                {
                    protection.ReleaseWriterLock();
                }
            }
            catch (ApplicationException error)
            {
                MessageBox.Show(error.Message);
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
            gp.Title.Text = "Speed vs Time";
            gp.XAxis.Title.Text = "Time";
            gp.YAxis.Title.Text = "Speed";

            int x = 0;
            foreach (var item in results)
            {
                foreach (var thing in item.Descendants("Value"))
                {
                    listPoints.Add(x++, Convert.ToDouble(thing.Value));
                }
            }
            line_item = gp.AddCurve(null, listPoints, Color.LightSeaGreen, SymbolType.None);
            line_item.Line.Width = 1;
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
                output.Populate(headers, values);
                output.Show();
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
            //naughy
            var results = d.getLatest("Speed_Sensor");
            int c = 0;
            list = new string[results.Count()];
            foreach (var item in results)
            {
                foreach (var thing in item.Descendants("Value"))
                {
                    list[c++] = thing.Value;
                }
            }
            //end naughty

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
            numericUpDown4.Value = DateTime.Now.Hour;
            numericUpDown2.Value = DateTime.Now.Minute;
            numericUpDown1.Value = DateTime.Now.Hour - 1;
            numericUpDown3.Value = DateTime.Now.Minute;
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            button6.Enabled = true;
        }
    }
}
