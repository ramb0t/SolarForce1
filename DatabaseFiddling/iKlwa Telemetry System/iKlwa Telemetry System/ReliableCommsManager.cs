using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace iKlwa_Telemetry_System
{
    class ReliableCommsManager:CommsManager
    {
        private const byte PING = 0x05;
        private const byte ACK = 0x06;

        public ReliableCommsManager() { }

        public bool checkForPing()
        {
            int readVal = this.readByte();
            bool pingFound = (readVal==PING);
            if (pingFound)
                this.writeByte(ACK);
            return pingFound;
        }
    }
}
