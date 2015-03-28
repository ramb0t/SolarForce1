using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Windows.Forms;

namespace iKlwa_Telemetry_System
{
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new Form1());
        }
    }

    class CommsManager
    {
        private SerialPort port;

        public int baudrate
        {
            get
            {
                return port.BaudRate;
            }
            set
            {
                port.BaudRate = value;
            }
        }//possible need for error checking code

        public enum Parities : int { Odd, Even, NoParity };
        public int parity
        {
            set
            {
                switch (value)
                {
                    case (int)Parities.Odd:
                        port.Parity = Parity.Odd;
                        break;

                    case (int)Parities.Even:
                        port.Parity = Parity.Even;
                        break;

                    case (int)Parities.NoParity:
                    default:
                        port.Parity = Parity.None;
                        break;
                }
            }
        }




        public CommsManager()
        {
            
        }
    }
}
