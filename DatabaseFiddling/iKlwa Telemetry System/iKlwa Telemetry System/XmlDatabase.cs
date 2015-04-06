using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Windows.Forms;
using System.Xml.Linq;
using System.Threading.Tasks;

namespace iKlwa_Telemetry_System
{
    class XmlDatabase
    {
        private XDocument xml_file; //XElement object to be used for creating nodes
        private string file_name; //address of XML database
        private string root; //root node tag
        private string node_tag; //Level 1 node tag

        //Constructors
        public XmlDatabase() { }
        public XmlDatabase(string filename, string rootname)
        {
            createXml(filename, rootname);
        }

        //Create XML file, return whether it currently exists or not
        public bool createXml(string filename, string rootname)
        {
            bool exists = File.Exists(filename); //check if specified filename exists
            if (!exists) //if file does not exist, create file
            {
                try
                {
                    xml_file = new XDocument(new XDeclaration("1.0", "utf-", "true"), new XElement(rootname)); //declare XML version and encoding
                    xml_file.Save(filename); //save XML file
                }
                catch (Exception e)
                {
                    MessageBox.Show(e.ToString());
                }
            }
            root = rootname; //set root node of XML database
            file_name = filename; //set address of XML database
            try
            {
                xml_file = XDocument.Load(filename); //load XML file
            }
            catch (Exception e)
            {
                MessageBox.Show(e.ToString());
            }
            return exists; //return flag indicating if XML file exists or not
        }

        //adds node to XML file
        public void addNode(XElement element)
        {
            try
            {
                xml_file.Element(root).Add(element); //add node
                xml_file.Save(file_name, SaveOptions.OmitDuplicateNamespaces); //save changes
            }
            catch (Exception ex) //adding new node may return exception if structure of XML file is breached
            {
                MessageBox.Show(ex.ToString()); //display error message
            }
        }

        //create XML Element
        public XElement createElement(string label, object value)
        {
            XElement xelem = new XElement(node_tag, new XElement(label, value));
            return xelem;
        }

        //create XML Element with attribute
        public XElement createElement( string attLabel, object att, string label, object value)
        {
            XElement xelem = createElement(label, value);
            xelem.SetAttributeValue(attLabel, att);
            return xelem;
        }

        public IEnumerable<XElement> queryLvl1()
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                                            select n;
            return results;
        }

        public IEnumerable<XElement> queryLvl1ByAttributes(string attr_name, string attr)
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                        where n.Attribute(attr_name).Value == attr
                        select n;
            return results;
        }

        public IEnumerable<XElement> queryLvl1Range(string field, object start, object end)
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag).Descendants(field)
                                            where n.Value.CompareTo(start) > 0 && n.Value.CompareTo(end) < 0
                                            select n;
            return results;
        }

        
        // May not actually need this
        public IEnumerable<XElement> queryLvl2(string lvl2_tag)
        {
            var nodes = from n in xml_file.Descendants(node_tag).Descendants(lvl2_tag)
                        select n;
            IEnumerable<XElement> results = nodes;
            return results;
        }

        public IEnumerable<IGrouping<IEnumerable<XElement>, XElement>>
            queryLvl2Grp(string lvl2_tag)
        {
            var k = from n in xml_file.Descendants(node_tag).Descendants(lvl2_tag)
                    group n by xml_file.Descendants(node_tag).Descendants(lvl2_tag);
            IEnumerable<IGrouping<IEnumerable<XElement>, XElement>> results = k;
            return results;
        }

        

        public string NodeTag
        {
            set
            {
                bool acceptable = true; //flag indicating acceptability
                try
                {
                    XElement x = new XElement(value); //attempt creating XElement object with specified node tag
                                                      //if an XElement can be created, the tag is valid
                }
                catch (System.Xml.XmlException) //if invalid string entered, XmlException is thrown
                {
                    acceptable = false; //set acceptability flag to false
                }
                node_tag = acceptable ? value : null;
            }
            get
            {
                return node_tag;
            }
        }

    }
}

