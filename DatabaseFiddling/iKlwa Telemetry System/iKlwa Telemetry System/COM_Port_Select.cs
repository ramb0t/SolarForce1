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
        private object selected_port = "None";

        public COM_Port_Select()
        {
            InitializeComponent();
        }

        public COM_Port_Select(ref object choice)
        {
            InitializeComponent();
            choice = selected_port;
        }

        private void COM_Port_Select_Load(object sender, EventArgs e)
        {
            comboBox1.Items.AddRange(
                System.IO.Ports.SerialPort.GetPortNames());
        }

        private void button1_Click(object sender, EventArgs e)
        {
            selected_port = comboBox1.SelectedText;
            this.Dispose();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            comboBox1.Items.AddRange(
                System.IO.Ports.SerialPort.GetPortNames());
        }
    }
}
