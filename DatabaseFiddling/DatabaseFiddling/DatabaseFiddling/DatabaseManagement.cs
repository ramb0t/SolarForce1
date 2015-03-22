using System;
using System.Xml;
using System.Xml.Linq;
using System.IO;
using System.IO.Ports;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Threading;
using System.Timers;
using System.Threading.Tasks;

namespace DatabaseFiddling
{
    class Test
    {
        static ReaderWriterLock protectionLock = new ReaderWriterLock();
        static int num = 0;

        private static void timeoutEvent(object s, ElapsedEventArgs e)
        {
            Console.WriteLine("Timeout Event at time "+DateTime.Now);
        }

        private static void runThread2()
        {
            SerialCommsManager a = new SerialCommsManager();
            a.setDefaultPort();
            //a.activate();
            
                for (int loop = 0; loop<3; loop++)
                {
                    Console.WriteLine("Running Thread: " + Thread.CurrentThread.Name + " " + loop);
                    try
                    {
                        protectionLock.AcquireReaderLock(100);
                        try
                        {
                            Console.WriteLine("Reader Thread locked: num = " + num);
                        }
                        finally
                        {
                            protectionLock.ReleaseReaderLock();
                        }
                    }
                    catch (ApplicationException)
                    {
                        Console.WriteLine("ReaderLock Timeout");
                    }
                    Thread.Sleep(400);
                }
        }
        
        static void Main(string[] args)
        {
            System.Timers.Timer timer = new System.Timers.Timer(1000);
            timer.Elapsed += timeoutEvent;
            timer.Enabled = true;
            Console.WriteLine("Timer Started at " + DateTime.Now);
            //Database db = new Database("xmlTrialDb_v2.xml", "Logger");
            Thread backgroundJobby = new Thread(new ThreadStart(runThread2));
            backgroundJobby.Name = "Reader";
            backgroundJobby.Start();
            for (int i = 0; i < 5; i++)
                {
                    Console.WriteLine("Running Thread: Writer " + i);
                    try
                    {
                        protectionLock.AcquireWriterLock(100);
                        try
                        {
                            num = new Random().Next(255);
                            Console.WriteLine("Writer Thread Locked: num set to num = " + num);
                        }
                        finally
                        {
                            protectionLock.ReleaseWriterLock();
                        }
                    }
                    catch(ApplicationException)
                    {
                        Console.WriteLine("Writer Lock timeout");
                    }
                    Thread.Sleep(250);
                }
            //db.setNodeLabel("Packet");
            //db.addData("Speed", 100.5, "Type", "Data");
            //db.addData("MPPT3", "Overheat", "Type", "Error");
            //db.addData("Speed", "Motor RPM and Analogue Voltage Mismatch", "Type", "Error");
            //Console.WriteLine("\n\nGetting Errors:\n");
            //db.getErrors();
            
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

        private XDocument xml_file; //XElement object to be used for creating nodes
        private string file_name; //address of XML database
        private string node_label; //label associated to each node of database
        private string root;

        //Constructors
        public Database(String filename, String root_name)
        {
            createXML(filename, root_name); 
        }

        //Create XML file, return whether it currently exists or not
        public bool createXML(String filename, String rootname)
        {
            root = rootname;
            bool exists = File.Exists(filename); //check if specified filename exists
            if (!exists) //if file does not exist, create file
            {
                xml_file = new XDocument(new XDeclaration("1.0", "utf-", "true"), new XElement(root)); //declare XML version and encoding
                xml_file.Save(filename); //save XML file
                Console.WriteLine("XML Database Created. Name: " + filename); //confirm message displayed in console
            }
            else //XML file already exists
            {
                Console.WriteLine("XML Database already exists. Name: " + filename); //indicate file already exists in console
            }
            xml_file = XDocument.Load(filename); //load XML file
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
                xml_file.Element(root).Add(element); //add node
                xml_file.Save(file_name, SaveOptions.OmitDuplicateNamespaces); //save changes
                Console.WriteLine("Element Created:\n" + element + "\n");
            }
            catch (Exception ex) //adding new node may return exception if structure of XML file is breached
            {
                Console.WriteLine("Error: " + ex + "\n\nNode not created."); //display error message
            }
        }

        //query XML file
        public void getErrors()
        {
            var entries = from e in xml_file.Descendants(node_label)
                          where e.Attribute("Type").Value == "Error"
                          select e;
            foreach (var e in entries)
            {
                Console.WriteLine(e);
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
