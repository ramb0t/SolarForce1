using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace iKlwa_Telemetry_System
{
    public partial class COM_Port_Select : Form
    {
        private string selected_port = "None";

        public COM_Port_Select()
        {
            InitializeComponent();
        }

        public string getPort()
        {
            return selected_port.ToString();
        }

        private void COM_Port_Select_Load(object sender, EventArgs e)
        {
            comboBox1.Items.AddRange(
                System.IO.Ports.SerialPort.GetPortNames());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                selected_port = comboBox1.SelectedItem.ToString();
                this.Dispose();
            }
            catch (NullReferenceException n)
            { MessageBox.Show(n.Message); }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            string[] allPorts = System.IO.Ports.SerialPort.GetPortNames();
            for (int i = 0; i < allPorts.Length; i++)
            {
                if (comboBox1.Items.Contains(allPorts[i]) == false)
                    comboBox1.Items.Add(allPorts[i]);
            }
        }
    }
}
