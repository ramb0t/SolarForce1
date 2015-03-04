using System;
using System.Xml;
using System.IO;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace DatabaseFiddling
{
    class DatabaseManagement
    {
        static void Main(string[] args)
        {
            Database db = new Database();
            db.createXML("xmlTrialDb.xml");
            Console.ReadKey();
        }
    }

    class Database
    {
        public Database() { }

        public bool createXML(String filename)
        {
            bool exists = File.Exists(filename);
            if (!exists)
            {
                XmlTextWriter writer = new XmlTextWriter(filename, Encoding.UTF8);
                writer.WriteStartDocument();
                writer.WriteStartElement("Telemetry_Data");
                writer.WriteEndElement();
                writer.Close();
                Console.WriteLine("XML Database Created");
            }
            else Console.WriteLine("XML Database already exists.");
            return exists;
        }

    }
}
