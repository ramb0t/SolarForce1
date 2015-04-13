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
using System.Xml.Linq;

namespace iKlwa_Telemetry_System
{
    public partial class UserInterface : Form
    {
        public UserInterface()
        {
            InitializeComponent();
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
            
        }

    }
}
