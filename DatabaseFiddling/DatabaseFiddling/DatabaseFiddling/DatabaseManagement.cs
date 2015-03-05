using System;
using System.Xml;
using System.Xml.Linq;
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
            Database db = new Database("xmlTrialDb.xml");
            db.addData("Speed", 100);
            db.addData("InputCurrent", 23);
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

        private XElement xml_file;
        private string file_name;
        private string root = "DataLog";

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
                XDocument x = new XDocument(new XDeclaration("1.0", "utf-", "true"), new XElement(root)); //declare XML version and encoding
                x.Save(filename); //save XML file
                Console.WriteLine("XML Database Created"); //confirm message displayed in console
            }
            else //XML file already exists
            {
                Console.WriteLine("XML Database already exists."); //indicate file already exists in console
            }
            xml_file = XElement.Load(filename); //load XML file
            file_name = filename;
            return exists; //return flag indicating if XML file exists or not
        }

        public void addData(String label, Object value)
        {
            Console.WriteLine("Trying to create element...");
            try
            {
                XElement newX = new XElement("Packet", new XElement(label, value), new XElement("Time", DateTime.Now));
                xml_file.Add(newX);
                Console.WriteLine("Node Addition Code Executed...\n"+newX);
                xml_file.Save(file_name, SaveOptions.OmitDuplicateNamespaces);

            }
            catch (Exception ex)
            {
                Console.WriteLine("Error: " + ex + "\nNode not created.");
            }
        }
    }
}
