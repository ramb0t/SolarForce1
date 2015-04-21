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
        private bool no_ports_found = true;

        public COM_Port_Select()
        {
            InitializeComponent();
        }

        public string Port
        {
            get { return selected_port; }
        }

        public bool NoPortsFound
        {
            get { return no_ports_found; }
        }

        private void COM_Port_Select_Load(object sender, EventArgs e)
        {
            comboBox1.Items.AddRange(
                System.IO.Ports.SerialPort.GetPortNames());
            no_ports_found = (comboBox1.Items.Count == 0);
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                selected_port = comboBox1.SelectedItem.ToString();
            }
            catch (NullReferenceException)
            { 
                //MessageBox.Show(n.Message); 
                selected_port = null;
            }
            finally {this.Dispose();}
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
