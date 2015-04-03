using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
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



        public Form1()
        {
            InitializeComponent();

            XmlDatabase d = new XmlDatabase("I LIKE PI.xml", "potato");
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
            Application.Run(c);
            string COM_port = c.getPort();
            comms.name = COM_port.ToString();
            comms.OpenPort();
        }

    }
}
