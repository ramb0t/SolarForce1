using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iKlwa_Telemetry_System
{
    class TextFileManager
    {
        private string filename;
        //private BufferedStream text_stream;
        private TelemetryDatabase t = new TelemetryDatabase("textfile_things");
        private StreamReader reader;
        private StringBuilder stringb = new StringBuilder();

        public TextFileManager(string file = "TestText.txt")
        {
            if (file.EndsWith(".txt")==false)
                file += ".txt";
            filename = file;
            t.NodeTag = "root";
            /*
            text_stream = new BufferedStream(
                          new FileStream(file, FileMode.OpenOrCreate,
                          FileAccess.ReadWrite, FileShare.None, 25, true));
            */
            System.Windows.Forms.MessageBox.Show(file);
            reader = new StreamReader(file);
        }

        struct decoded
        { 
            public string sensor;
            public string message;
            public string value;
            public string hour;
            public string minute;
        };

        public void getAndWrite()
        {
            while(!reader.EndOfStream)
            {
                int[] buffer = new int[50];
                int index = 0;
                do
                {
                    buffer[index] = reader.Read();
                    stringb.Append(Convert.ToChar(buffer[index]));
                } while (buffer[index++] != '.');

                //5 values expected: sensor, message, value, hour, minute.
                string msg = stringb.ToString();
                stringb.Clear();

                string[] chunks = msg.Split(',');
                decoded pkt;
                pkt.sensor = chunks[0];
                pkt.message = chunks[1];
                pkt.value = chunks[2];
                pkt.hour = chunks[3];
                pkt.minute = chunks[4].Substring(0,chunks[4].Length - 1);

                t.addDataCapture(pkt.sensor, pkt.hour + 'h' + pkt.minute, pkt.message, pkt.value);

            }
        }
    }
}
