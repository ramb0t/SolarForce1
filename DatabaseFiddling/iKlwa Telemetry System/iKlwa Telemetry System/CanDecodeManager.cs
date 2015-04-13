using System;
using System.Collections.Generic;
using System.Windows.Forms;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace iKlwa_Telemetry_System
{
    class CanDecodeManager
    {
        public struct CAN
        {
            public int ID;
            public int LENGTH;
            public string[] DATA;
            public bool initialised;
        }
        private CAN cPkt;

        private StreamReader reader;
        private StringBuilder stringBuilder = new StringBuilder();
        private string filename;
        private char end_delimeter;
        public char Delimeter
        {
            set
            {
                end_delimeter = value;
            }
            get
            {
                return end_delimeter;
            }
        }

        public CanDecodeManager(string filepath)
        {
            cPkt.initialised = false;
            if (filepath.EndsWith(".txt") == false)
                filepath += ".txt";
            try
            {
                reader = new StreamReader(filepath);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
            filename = filepath;
        }
        
        /// <summary>
        /// Populates the CAN struct from an input string, with a given delimeter.
        /// Assumed standard CAN frame structure.
        /// </summary>
        /// <param name="message"></param>
        /// <param name="split_delimeter"></param>
        /// <returns></returns>
        public CAN populatePacket(string message, char split_delimeter)
        {
            string[] fields = message.Split(split_delimeter);
            
            cPkt.ID = Convert.ToInt16(fields[0], 2);

            cPkt.LENGTH = Convert.ToInt16(fields[1]);
            cPkt.DATA = new string[fields.Length - 2];
            Array.Copy(fields, 2, cPkt.DATA, 0, cPkt.LENGTH);
            return cPkt;
        }

        private enum SensorIds :int
        {
            BMS_ID,
            GPS_ID,
            HE_ID,
            Accel_ID,
            MPPT1_ID,
            MPPT2_ID,
            MPPT3_ID,
            MPPT4_ID,
            MotorDvr_ID
        };

        /// <summary>
        /// Identifies sensor based on ID entered.
        /// </summary>
        /// <returns></returns>
        public string getID()
        {
            string id_string;
            switch(cPkt.ID)
            {
                //ID definitions as per CAN IDs
                case (int)SensorIds.BMS_ID:
                    id_string = "BMS";
                    break;
                case (int)SensorIds.MPPT1_ID:
                    id_string = "MPPT1";
                    break;
                case (int)SensorIds.MPPT2_ID:
                    id_string = "MPPT2";
                    break;
                case (int)SensorIds.MPPT3_ID:
                    id_string = "MPPT3";
                    break;
                case (int)SensorIds.MPPT4_ID:
                    id_string = "MPPT4";
                    break;
                case (int)SensorIds.MotorDvr_ID:
                    id_string = "Motor_Driver";
                    break;
                case (int)SensorIds.GPS_ID:
                    id_string = "GPS";
                    break;
                case (int)SensorIds.Accel_ID:
                    id_string = "Accelerometer";
                    break;
                case (int)SensorIds.HE_ID:
                    id_string = "HE_Sensor";
                    break;
                default:
                    id_string = null;
                    break;
            }
            return id_string;
        }

        /// <summary>
        /// Decodes payload from CAN. Structure of payload depends on the CAN ID.
        /// </summary>
        /// <returns></returns>
        public object getPayloadData()
        {
            object payloadData = null;//payload will depend on what sensor is detected
            switch (cPkt.ID)
            {
                case (int)SensorIds.BMS_ID:
                    //
                    break;
                case (int)SensorIds.MPPT1_ID:
                    //
                    break;
                case (int)SensorIds.MPPT2_ID:
                    //
                    break;
                case (int)SensorIds.MPPT3_ID:
                    //
                    break;
                case (int)SensorIds.MPPT4_ID:
                    //
                    break;
                case (int)SensorIds.MotorDvr_ID:
                    //
                    break;
                case (int)SensorIds.GPS_ID:
                    //
                    break;
                case (int)SensorIds.Accel_ID:
                    //
                    break;
                case (int)SensorIds.HE_ID:
                    //
                    break;
                default:
                    //
                    break;
            }
            return payloadData;
        }

        /// <summary>
        /// Checks for the end delimeter of a CAN frame.
        /// </summary>
        /// <returns></returns>
        public bool frameEnd()
        {
            return reader.Peek() == end_delimeter;
        }

        /// <summary>
        /// Gets all the CAN messages from the text file
        /// </summary>
        public List<CAN> get()
        {
            List<CAN> allFrames = new List<CAN>();
            while (!reader.EndOfStream)
            {
                //read text stream until end of frame delimeter
                do
                {
                    stringBuilder.Append(Convert.ToChar(
                                         reader.Read()));
                } while (frameEnd() == false);
                reader.Read(); //skips over the end of frame delimeter

                string msg = stringBuilder.ToString();
                stringBuilder.Clear();
                populatePacket(msg, ',');
                allFrames.Add(this.cPkt);
            }
            return allFrames;
        }

    }
}
