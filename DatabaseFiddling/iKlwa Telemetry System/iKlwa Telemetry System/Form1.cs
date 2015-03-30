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
            while (comms.checkForPing() == false) ;

        }

    }
}
