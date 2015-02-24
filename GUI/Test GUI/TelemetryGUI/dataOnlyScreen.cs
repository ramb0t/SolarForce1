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

        private graphScreen newGraphScreenObject()
        {
            graphScreen gactive = new graphScreen();
            return gactive;                 //returns a form object to use if it isn't loaded already
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
            graphScreen gactive = newGraphScreenObject();
            //set up DB logging etc.
        }

        public bool getMenuitemStatus()           //alloows other form to modify this data
        {
            return graphPageIsOpenInBackgroundToolStripMenuItem.Visible;
        }

        public void setMenuItemStatus(bool menu)           //alloows other form to modify this data
        {
            graphPageIsOpenInBackgroundToolStripMenuItem.Visible=menu;
        }

        private void dataOnlyScreen_FormClosing(object sender, FormClosingEventArgs e)
        {
            switch(e.CloseReason)               //warns user when quitting app, will also close graphing window
            {
                case CloseReason.UserClosing: if (MessageBox.Show("This will quit the iKlwa Telemetry System. If the Real-Time Graph page is still open, this will also close. Are you sure?", "Are you sure?", MessageBoxButtons.YesNo) == DialogResult.No)
                    {
                        e.Cancel = true;          //stops app from closing
                    }
                    break;
            }
         }

        //when switching between the graphing and data only windows, using the menu, when going data-> graph, the data window stays open in the background. That's fine but if, with data & graph window running, you click "graph" again on the data page, you get multiple instances of the graph page. If you go data-> graph -> data it neatly closes the graph window (only 1 isntance of data window open at any time) so that's weird. Will fix later hopefully!

        private void realTimeGraphsToolStripMenuItem_Click(object sender, EventArgs e)
        {
                if (graphPageIsOpenInBackgroundToolStripMenuItem.Visible == false)
                {
                    graphScreen gactive = newGraphScreenObject();
                    graphPageIsOpenInBackgroundToolStripMenuItem.Visible = true;
                    gactive.ShowDialog();                                           //uses modal dialog; can't interact with data screen until graph screen is closed.
                }
                               
        }

       
    }
}
