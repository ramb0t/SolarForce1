using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iKlwa_Telemetry_System
{
    class TelemetryCommsManager:CommsManager
    {
        private const byte PING = 0x05;
        private const byte ACK = 0x06;
        private const string START = ">>";
        private const string END = "<<";
        private const char DELIMETER = ',';

        public TelemetryCommsManager() { }

        public bool checkForPing()
        {
            int readVal = this.readByte();
            bool pingFound = (readVal==PING);
            if (pingFound)
                this.writeByte(ACK);
            return pingFound;
        }

        public struct Packet
        {
            public int ID;
            public List<string> PAYLOAD;
        }

        private void waitForStart()
        {
            this.readTextUntil(START);
        }
        private string getFrame()
        {
            return this.readTextUntil(END);
        }

        private Packet populate()
        {
            Packet pkt;
            pkt.ID = this.readByte();
            this.readTextUntil(DELIMETER + "");
            pkt.PAYLOAD = this.getFrame().Split(DELIMETER).ToList<string>();
            return pkt;
        }

        public Packet readTelemetryInput()
        {
            waitForStart();
            return populate();
        }


        public void MavLinkInit()
        {
            try
            {
                baud_rate = 9600;
                data_bits = 8;
                stop_bits = 1;
                parity = (int)Parities.NoParity;
                interrupt_bytes_threshold = 1;
            }
            catch (Exception e)
            { System.Windows.Forms.MessageBox.Show(e.Message); }
        }

    }
}
