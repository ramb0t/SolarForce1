using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZedGraph;

namespace iKlwa_Telemetry_System
{
    public partial class Form1 : Form
    {
        private const string NO_SENSORS_MSG = "No Sensors";

        private COM_Port_Select c = new COM_Port_Select(); //the COM Port Selection Form that may be opened
        private TelemetryCommsManager comms = new TelemetryCommsManager(); 
        private TelemetryDatabase d;

        public Form1()
        {
            InitializeComponent();

            d = new TelemetryDatabase("xmlTrialDb_v4.xml");//loading XML file to be used when form opens
            d.NodeTag = "Packet"; //setting level 1 node name, I chose to call it "Packet"
        }

        //some micro things that aren't used atm
        private void checkForConnection()
        {
            int trials = 0;
            while (comms.checkForPing() == false)
            {
                trials++;
                try
                {
                    if (trials == 1000)
                        throw new TimeoutException("Communication to Target Failed: Please Reset Hardware");
                }
                catch (TimeoutException t)
                {
                    MessageBox.Show(t.Message);
                    trials = 0;
                }
            }
        }

        private void button1_Click(object sender, EventArgs e)
        {
            c.ShowDialog(); //open the COM Port Select form
            string COM_port = c.getPort(); //get the selected port, if valid
            comms.name = COM_port.ToString();
            comms.OpenPort();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //test error message query
            var errors = d.getErrors();
            richTextBox1.Text = "Errors found: "+ errors.Count().ToString() + "\n\n";
            foreach (var err in errors)
            {
                foreach (var val in err.Descendants())
                richTextBox1.AppendText(val.Name + ": " + val.Value + "\n");//display errors with mild formatting
            }
            richTextBox1.AppendText("\n");
        }

        private void button3_Click(object sender, EventArgs e)
        {
            if (comboBox1.Items.Contains(NO_SENSORS_MSG)) //if the no sensors message is in the combo box, remove it
                comboBox1.Items.Remove(NO_SENSORS_MSG);
            var sensorGroup = d.getSensors();
            richTextBox1.Text = "Sensors found: " + sensorGroup.Count().ToString() + "\n\n"; //indicate no. of sensors found
            foreach (var sensor in sensorGroup)
            {
                if (comboBox1.Items.Contains(sensor.Key) == false)
                    comboBox1.Items.Add(sensor.Key); //add sensors to combo box if they are not contained in there already
                richTextBox1.AppendText(sensor.Key + "\n"); //display sensor found
            }
            richTextBox1.AppendText("\n");
        }

        private void button4_Click(object sender, EventArgs e)
        {
            //manually add some data and error packets - for testing purposes
            d.simulateDataCapture("HE_Sensor1", "Speed", new Random().Next(100));
            d.simulateDataCapture("HE_Sensor2", "Speed", 102);
            d.simulateErrorCapture("RF_Link", "Comms", "Communication Lost");
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            //populate combo box with available sensors when form loads
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

        //a test query - will remove and refine
        private void button5_Click(object sender, EventArgs e)
        {
            
        }

        private void button6_Click(object sender, EventArgs e)
        {
            string sensor = comboBox1.SelectedItem.ToString();
            if (sensor.Equals(null) == false)
            {
                var results = d.queryRange_valOnly(sensor, numericUpDown1.Value + "h" + numericUpDown3.Value, numericUpDown4.Value + "h" + numericUpDown2.Value);
                richTextBox1.Text = "Results found: " + results.Count().ToString() + "\n\n";
                foreach (var item in results)
                {
                    richTextBox1.AppendText(item.ToString() + "\n");
                }
            }
            else MessageBox.Show("No sensor selected...");
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            button6.Enabled = true;
        }

        private void button7_Click(object sender, EventArgs e)
        {
            GraphPane gp = zedGraphControl1.GraphPane;
            gp.CurveList.Clear();
            gp.Title.Text = "Speed vs Time";
            gp.XAxis.Title.Text = "Time";
            gp.YAxis.Title.Text = "Speed";

            PointPairList listPoints = new PointPairList();
            LineItem line_item;

            var results = d.queryRange_valOnly("HE_Sensor1", numericUpDown1.Value + "h" + numericUpDown3.Value, numericUpDown4.Value + "h" + numericUpDown2.Value);
            richTextBox1.Text = "Results found: " + results.Count().ToString() + "\n\n";
            int x = 0;
            foreach (var item in results)
            {
                foreach (var thing in item.Descendants("Value"))
                {
                    richTextBox1.AppendText(thing.Value + "\n");
                    listPoints.Add(x++, Convert.ToDouble(thing.Value));
                }
            }
            line_item = gp.AddCurve(null,listPoints,Color.LightSeaGreen,SymbolType.None);
            line_item.Line.Width = 1;
            zedGraphControl1.AxisChange();
            zedGraphControl1.Invalidate();
            zedGraphControl1.Refresh();
        }

        private void button8_Click(object sender, EventArgs e)
        {
            TextFileManager txt = new TextFileManager();
            txt.getAndWrite();
        }

        private void button9_Click(object sender, EventArgs e)
        {
            CanDecodeManager can_can = new CanDecodeManager("Random_Sim.txt");
            can_can.Delimeter = '\n';
            can_can.get();
        }

        private void button10_Click(object sender, EventArgs e)
        {
            comms.MavLinkInit();
            //MessageBox.Show("YOU WILL SEE ERRORS IF YOU DIDNT CONNECT TO THE COM PORT!");
            for (int a = 0; a < 40; a++)
            {
                comms.readTextUntil(">>");
                int header = (int)comms.readTextUntil(",").ToCharArray()[0];
                richTextBox1.Text += header;
                string[] received = comms.readTextUntil("<<").Split(',');

                switch (header)
                { 
                    case 421:
                        d.addDataCapture("Motor Driver",DateTime.Now.Hour+"h"+DateTime.Now.Minute,"Speed",(int)received[0].ToCharArray()[0]);
                    break;
                    case 420:
                    {
                        d.addDataCapture("Hall Effect 1", DateTime.Now.Hour + "h" + DateTime.Now.Minute, "Speed", (int)received[0].ToCharArray()[0]);
                        //more things related to flags
                    }
                    break;
                }
                foreach (string entry in received)
                {
                    //richTextBox1.Text += entry + ' ';
                    char[] potato = entry.ToCharArray();
                    foreach (var letter in potato)
                    {
                        if (String.IsNullOrWhiteSpace(letter + "") == false)
                        {
                            richTextBox1.Text += ((int)letter).ToString() + ' ';
                        }
                    }
                }
                richTextBox1.Text += '\n';
            }

        }

    }
}
