using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iKlwa_Telemetry_System
{
    class Simulator
    {
        private System.IO.StreamWriter textWrite ;
        private Random gen = new Random();
        private System.IO.StreamReader textRead;

        public Simulator()
        {

        }

        public void simData()
        {
            textWrite = new System.IO.StreamWriter("sim_data.txt");
            textWrite.Flush();
            for (int a = 0; a < 1438; ++a)
            {
                string date = gen.Next(1, 29).ToString() + "-" + gen.Next(1,13).ToString();
                string time = gen.Next(0, 24).ToString() + "h" + gen.Next(0, 60).ToString();
                string speed = gen.Next(0, 126).ToString();
                textWrite.Write("speed"+","+date+","+time+","+speed+Environment.NewLine);
            }
            textWrite.Dispose();
        }

        public string[,] getData()
        {
            textRead = new System.IO.StreamReader("sim_data.txt");
            string[,] allData = new string[1438,4];
            for (int b = 0; b < 1438; b++)
            {
                string[] line = textRead.ReadLine().Split(',');
                for (int c = 0; c < 4; c++)
                {
                    allData[b, c] = line[c];
                }
            }
                return allData;
        }
    
    }
}
