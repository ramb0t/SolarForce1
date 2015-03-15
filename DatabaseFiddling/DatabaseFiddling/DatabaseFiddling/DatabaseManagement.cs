using System;
using System.Xml;
using System.Xml.Linq;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Collections.Generic;
using System.Threading;
using System.Linq;
using System.Threading.Tasks;

namespace DatabaseFiddling
{
    class Test
    {
        static void Main(string[] args)
        {
            Database db = new Database("xmlTrialDb.xml");
            SerialCommsManager a = new SerialCommsManager();
            a.setDefaultPort();
            a.activate();
            db.setNodeLabel("Packet");
            db.addData("OutputCurrent", 12, "Type", "Data");
            db.setNodeLabel("Packet");
            db.addData("Speed", "Hall Effect sensor not found", "Type", "Error");
            db.setNodeLabel("Packet");
            db.addData("InclineX", 16.2);
            Console.ReadKey();
        }
    }

    /*
     * Database Class should manage all interactions with database
     * including the creation of the database,
     * adding entries to the database,
     * extracting information from the database
    */
    class Database
    {
        public Database() { }

        private XElement xml_file; //XElement object to be used for creating nodes
        private string file_name; //address of XML database
        private string node_label; //label associated to each node of database

        //Constructors
        public Database(String filename)
        {
            createXML(filename); 
        }

        //Create XML file, return whether it currently exists or not
        public bool createXML(String filename)
        {
            bool exists = File.Exists(filename); //check if specified filename exists
            if (!exists) //if file does not exist, create file
            {
                XDocument x = new XDocument(new XDeclaration("1.0", "utf-", "true"), new XElement("DataLog")); //declare XML version and encoding
                x.Save(filename); //save XML file
                Console.WriteLine("XML Database Created"); //confirm message displayed in console
            }
            else //XML file already exists
            {
                Console.WriteLine("XML Database already exists."); //indicate file already exists in console
            }
            xml_file = XElement.Load(filename); //load XML file
            file_name = filename; //set address of XML database
            return exists; //return flag indicating if XML file exists or not
        }

        //creates data node for XML file
        public void addData(String label, Object value)
        {
            try
            {
                XElement x = new XElement(node_label, new XElement(label, value), new XElement("Time", DateTime.Now)); //create node
                addNode(x);
            }
            catch (Exception ex) //adding new node may return exception if structure of XML file is breached
            {
                Console.WriteLine("Error: " + ex + "\n\nNode not created."); //display error message
            }
        }

        //creates data node for XML file with attributes
        public void addData(String label, Object value, String attr, Object attrVal)
        {
            try
            {
                XElement x = new XElement(node_label, new XAttribute(attr, attrVal), new XElement(label, value), new XElement("Time", DateTime.Now)); //create node
                addNode(x);
            }
            catch (Exception ex) //adding new node may return exception if structure of XML file is breached
            {
                Console.WriteLine("Error: " + ex + "\n\nNode not created."); //display error message
            }
        }

        //adds node to XML file
        private void addNode(XElement element)
        {
            Console.WriteLine("Trying to create element...");
            try
            {
                xml_file.Add(element); //add node
                xml_file.Save(file_name, SaveOptions.OmitDuplicateNamespaces); //save changes
            }
            catch (Exception ex) //adding new node may return exception if structure of XML file is breached
            {
                Console.WriteLine("Error: " + ex + "\n\nNode not created."); //display error message
            }
        }

        //get the root node label
        public string getNodeLabel()
        { return node_label; }
        //set the root node label
        public void setNodeLabel(string label)
        {
            bool acceptable = true; //flag indicating acceptability
            try
            {
                XElement x = new XElement(label); //attempt creating XElement object with specified node
            }
            catch (System.Xml.XmlException inv) //if invalid string entered, XmlException is thrown
            {
                acceptable = false; //set acceptability flag to false
                Console.WriteLine(inv+"\n\nInvalid input - setting to default.");
            }
            node_label = acceptable ? label : "Level_1"; //set node_label to "Level_1" by default 
        }
    }

    class SerialCommsManager
    {
        private SerialPort port = new SerialPort();

        private string baudRate;
        public void setBaudRate(string br)
        {
            baudRate = br;
        }
        public string getBaudRate()
        { return baudRate; }

        /*add for parity, stop bits and other params*/

        void received_data(object sender, SerialDataReceivedEventArgs e)
        {
            int vals = port.BytesToRead;
            byte[] buffer = new byte[vals];
            port.Read(buffer,0,vals);
            for (int i = 0; i < vals; ++i)
                Console.WriteLine(buffer[i]);
        }

        public void setDefaultPort()
        {
            port.DataBits = 8;
            port.PortName = "COM9";
            port.BaudRate = 4800;
            port.Parity = Parity.Odd;
            port.StopBits = StopBits.Two;

            port.DataReceived += new SerialDataReceivedEventHandler(received_data);
        }

        public void activate()
        {
            if (port.IsOpen)
                port.Close();

            port.Open();
        }
    }
}
