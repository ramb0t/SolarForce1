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
using ZedGraph;                     //for the graphical components

namespace BasicTestAppDesign3
{
    //see data only form detail about the derping when switching between/to forms.
    
    public partial class graphScreen : Form
    {
        //private bool graphScreenIsOpen = false;                   //can't get visibility across forms yet need to sheck this

        //public bool getGraphScreenActive()
        //{
        //    return graphScreenIsOpen;
        //}

        //public void setGraphScreenActive(bool status)
        //{
        //    graphScreenIsOpen = status;
        //}

        public graphScreen()
        {
            InitializeComponent();
        }

        private void graphScreen_Load(object sender, EventArgs e)
        {
            
        }

        private void graphScreen_Shown(object sender, EventArgs e)
        {

        }

        private void zedGraphControl1_Load(object sender, EventArgs e)
        {

        }

        private void graphScreen_FormClosing(object sender, FormClosingEventArgs e)
        {
            switch (e.CloseReason)              //confirm with user to go back to data-only screen --will terminate this form if Yes
            {
                case CloseReason.UserClosing: if (MessageBox.Show("Return to data-only screen?", "Are you sure?", MessageBoxButtons.YesNo) == DialogResult.No)
                    {
                        e.Cancel = true;          //stops app from closing
                    }
                 break;
                default: this.Dispose(true); break;
            }
            
        }

        private void toolStripMenuItem7_Click(object sender, EventArgs e)
        {
            this.Close();
            this.Dispose(true);
            //OR this.WindowState = FormWindowState.Minimized;       //minimised current view?? not suree if we should close or just minimise?
                        
        }
    }
}
