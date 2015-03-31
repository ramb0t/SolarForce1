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
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            string COM_port = null;
            COM_Port_Select c = new COM_Port_Select();
            Application.Run(c);
            COM_port = c.getPort();
            iKlwaComms comms = new iKlwaComms();
            comms.name = COM_port.ToString();
            comms.OpenPort();
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
            //after this, connection is established.
        }

    }
}
