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
    public partial class ReportScreen : Form
    {
        public ReportScreen()
        {
            InitializeComponent();
        }

        private DataTable grid = new DataTable();

        public void Populate(List<string> headers, List<string> values)
        {
            grid.Clear();
            grid.Columns.Clear();
            grid.Rows.Clear();
            foreach (string title in headers)
                grid.Columns.Add(title);
            if (values.Count == 0)
                throw new ArgumentException("No results found.");
            string[] data = values.ToArray();//rework later
            for (int i = grid.Columns.Count -1; i < values.Count; i=i+5)
            {
                grid.Rows.Add(data[i-4], data[i-3], data[i-2], data[i-1], data[i]);//little hacky?
            }
            dataGridView1.DataSource = grid;
        }

        public void setTitle(string title)
        {
            this.Text = label1.Text = title;
        }

        private void ReportScreen_Load(object sender, EventArgs e)
        {

        }
    }
}
