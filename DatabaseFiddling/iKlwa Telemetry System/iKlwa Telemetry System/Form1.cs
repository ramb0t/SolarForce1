using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ZedGraph;

namespace iKlwa_Telemetry_System
{
    public partial class Form1 : Form
    {
        private const string NO_SENSORS_MSG = "No sensors found...";

        private COM_Port_Select c = new COM_Port_Select(); //the COM Port Selection Form that may be opened
        private ReliableCommsManager comms = new ReliableCommsManager(); 
        private TelemetryDatabase d;

        public Form1()
        {
            InitializeComponent();

            d = new TelemetryDatabase("xmlTrialDb_v3.xml");//loading XML file to be used when form opens
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
            d.simulateDataCapture("HE_Sensor1", "Speed", 103);
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
        }

        //a test query - will remove and refine
        private void button5_Click(object sender, EventArgs e)
        {
            var results = d.queryRange("17h30", "17h45");
            richTextBox1.Text = "Results found: " + results.Count().ToString() + "\n\n";
            foreach (var item in results)
            {
                richTextBox1.AppendText(item.ToString() + "\n");
            }
        }
    }
}
