using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace iKlwa_Telemetry_System
{
    class TelemetryDatabase:XmlDatabase
    {
        public const string DATA_TYPE = "Data";
        public const string ERROR_TYPE = "Error";

        public const string ROOT_TAG = "TelemDb";

        public const string SENSOR_TAG = "Sensor";
        public const string TYPE_TAG = "Type";
        public const string DESCRIP_TAG = "Description";
        public const string VAL_TAG = "Value";
        public const string TIME_TAG = "Time";
        public const string DATE_TAG = "Date";
        public const string MSG_STATUS_TAG = "MessageStatus";

        public const bool READ_STATUS = true;
        public const bool UNREAD_STATUS = false;

        public TelemetryDatabase(string filename)
        {
            this.createXml(filename, ROOT_TAG);
        }

        private string getCurrentTime()
        {
            return DateTime.Now.ToString("HH") + 'h' + DateTime.Now.ToString("mm");
        }

        private void addCapture(string sensor, object time, string type, string description, object value)
        {
            var xe = this.createElement(SENSOR_TAG, sensor);
            this.setAttribute(ref xe, TYPE_TAG, type);
            this.setChild(ref xe, DESCRIP_TAG, description);
            if (value != null)
                this.setChild(ref xe, VAL_TAG, value);
            this.setChild(ref xe, TIME_TAG, time);
            this.setChild(ref xe, DATE_TAG, DateTime.Now.Day + "-" + DateTime.Now.Month);
            this.setAttribute(ref xe, MSG_STATUS_TAG, UNREAD_STATUS);
            this.addNode(xe);
        }

        public void addDataCapture(string sensor, object time, string description, object value = null)
        {
            addCapture(sensor, time, DATA_TYPE, description, value);
        }

        public void simulateDataCapture(string sensor, string description, object value)
        {
            this.addDataCapture(sensor, this.getCurrentTime(), description, value);
        }

        public void addErrorCapture(string sensor, object time, string description, object value = null)
        {
            addCapture(sensor, time, ERROR_TYPE, description, value);
        }

        public void simulateErrorCapture(string sensor, string description, object value)
        {
            this.addErrorCapture(sensor, this.getCurrentTime(), description, value);
        }

        public IEnumerable<XElement> getErrors()
        {
            return this.queryLvl1ByAttributes(TYPE_TAG, ERROR_TYPE);
        }

        public IEnumerable<IGrouping<string, XElement>> getSensors()
        {
            return this.queryLvl2Group(SENSOR_TAG);
        }

        public IEnumerable<XElement> queryRange(string start_time, string end_time)
        {
            return this.queryLvl3Range(TIME_TAG, start_time, end_time);
        }

        public IEnumerable<XElement> queryRange_valOnly(string val, string start_time, string end_time)
        {
            return this.queryLvl3RangeAndTag_Ordered(SENSOR_TAG, val, TIME_TAG, start_time, end_time);
        }

        public IEnumerable<XElement> queryRange_valOnly(string val, string start_time, string end_time, string start_date, string end_date)
        {
            return this.queryLvl3RangeAndTag_Ordered(SENSOR_TAG, val, TIME_TAG, start_time, end_time,DATE_TAG,start_date,end_date);
        }

        public IEnumerable<XElement> queryRange_valOnly(string val, string start_time, string end_time, string date)
        {
            return this.queryLvl3RangeAnd2Tag_Ordered(SENSOR_TAG, val, DATE_TAG, date, TIME_TAG, start_time, end_time);
        }

        public string getLatestValue(string sensor, string description)
        {
            string latestNode = null;
            try
            { latestNode = this.getNewest(SENSOR_TAG, sensor, DESCRIP_TAG, description).Element(VAL_TAG).Value; }
            catch (NullReferenceException)
            { throw; }
            return latestNode;

        }

        public int count()
        {
            return this.queryLvl1().Count();
        }

    }
}
