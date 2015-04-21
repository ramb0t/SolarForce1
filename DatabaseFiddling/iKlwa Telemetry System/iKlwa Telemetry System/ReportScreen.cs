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

        public void setTitle(string title)
        {
            label1.Text = title;
            ReportScreen.ActiveForm.Text = title;
        }

        public void Populate(List<string> headers, List<string> values)
        {
            grid.Clear();
            grid.Columns.Clear();
            grid.Rows.Clear();
            foreach (string title in headers)
                grid.Columns.Add(title);
            if (values.Count == 0)
                throw new ArgumentException("No results found.");

            for (int i = grid.Columns.Count -1; i < values.Count; i=i+grid.Columns.Count)
            {
                grid.Rows.Add(values.ElementAt(i - 4), values.ElementAt(i - 3),
                              values.ElementAt(i - 2), values.ElementAt(i - 1), values.ElementAt(i));//little hacky?
            }
            dataGridView1.DataSource = grid;
        }

        private void ReportScreen_Load(object sender, EventArgs e)
        {

        }
    }
}
