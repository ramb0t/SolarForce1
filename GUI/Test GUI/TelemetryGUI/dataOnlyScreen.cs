using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using BasicTestAppDesign3;
using ZedGraph;                     //for comms with the graphical screen's graphical components

namespace BasicTestAppDesign3
{

    public partial class dataOnlyScreen : Form
    {
        public dataOnlyScreen()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void actionsToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void textBox3_TextChanged(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void dataOnlyScreen_Load(object sender, EventArgs e)
        {
            //set up DB logging etc.
        }

        private void dataOnlyScreen_FormClosing(object sender, FormClosingEventArgs e)
        {
            switch(e.CloseReason)               //warns user when quitting app, will also close graphing window
            { 
                case CloseReason.UserClosing:  if(MessageBox.Show("This will quit the iKlwa Telemetry System. If the Real-Time Graph page is still open, this will also close. Are you sure?", "Are you sure?", MessageBoxButtons.YesNo) == DialogResult.No)
                {
                    e.Cancel=true;          //stops app from closing
                }
            break;
            }
         }

        //when switching between the graphing and data only windows, using the menu, when going data-> graph, the data window stays open in the background. That's fine but if, with data & graph window running, you click "graph" again on the data page, you get multiple instances of the graph page. If you go data-> graph -> data it neatly closes the graph window (only 1 isntance of data window open at any time) so that's weird. Will fix later hopefully!

        private void realTimeGraphsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            graphScreen gactive = new graphScreen();                            //attempting to allow only one graphing instance at once...broken??
            if (gactive.Visible==true)
            {
                graphPageIsOpenInBackgroundToolStripMenuItem.Visible = true;

            }
            else if (gactive.Visible==false)
            {
                graphScreen gscreen = new graphScreen();
                gscreen.Show();
            }
            //this.WindowState = FormWindowState.Minimized;       //minimised current view (must leave running to log data!)
            //this.Visible = false;
        }

       
    }
}
