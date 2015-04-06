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
        COM_Port_Select c = new COM_Port_Select();
        ReliableCommsManager comms = new ReliableCommsManager();

        XmlDatabase database;

        public Form1()
        {
            InitializeComponent();

            database = new XmlDatabase("xmlTrialDb_v2.xml", "Logger");
            database.NodeTag = "Packet";
        }

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
            c.ShowDialog();
            string COM_port = c.getPort();
            comms.name = COM_port.ToString();
            comms.OpenPort();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            //test error message query
            var errors = database.queryLvl1ByAttributes("Type", "Error");
            richTextBox1.Text = "Errors found: "+ errors.Count().ToString() + "\n\n";
            foreach (var err in errors)
            {
                foreach (var val in err.Descendants())
                richTextBox1.AppendText(val.Name + ": " + val.Value + "\n");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            var allData = database.queryLvl2("Speed");
            foreach (var err1 in allData)
            {
                richTextBox1.AppendText(err1.ToString()+'\n');
            }
        }

    }
}
