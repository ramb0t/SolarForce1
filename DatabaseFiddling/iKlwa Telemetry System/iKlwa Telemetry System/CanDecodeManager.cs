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

        private static StreamReader reader;
        StringBuilder stringBuilder = new StringBuilder();
        string filename;

        public CanDecodeManager(string filepath)
        {
            cPkt.initialised = false;
            if (filepath.EndsWith(".txt") == false)
                filepath += ".txt";
            try
            {
                reader = new StreamReader(filename);
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message);
            }
            filename = filepath;
        }
        
        public CAN populatePacket(string message, char split_delimeter)
        {
            string[] fields = message.Split(split_delimeter);
            cPkt.ID = Convert.ToInt16(fields[0]);
            cPkt.LENGTH = Convert.ToInt16(fields[1]);
            cPkt.DATA = new string[fields.Length-2];
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

        //interpret things from payload according to the sensor 
        public object getPayloadData()
        {
            string[] payloadData = new string[cPkt.LENGTH];
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

    }
}
