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

        #region create & modify XML files and nodes

        //Create XML file, return whether it currently exists or not
        protected bool createXml(string filename, string rootname)
        {
            //ensure that filename extension is an XML file
            if (filename.EndsWith(".xml") == false)
                filename = filename + ".xml";

            bool exists = File.Exists(filename); //check if specified filename exists
            if (!exists) //if file does not exist, create file
            {
                try
                {
                    xml_file = new XDocument(new XDeclaration("1.0", "utf-", "true"),
                               new XElement(rootname)); //declare XML version, root tag and encoding
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
        protected void addNode(XElement element)
        {
            try
            {
                xml_file.Element(root).AddFirst(element); //add node to top of file
                xml_file.Save(file_name, SaveOptions.OmitDuplicateNamespaces); //save changes
            }
            catch (Exception ex) //adding new node may return exception if structure of XML file is breached
            {
                MessageBox.Show(ex.ToString()); //display error message
            }
        }

        protected XElement createElement()
        {
            XElement xelem = new XElement(node_tag);
            return xelem;
        }

        //create XML Element
        protected XElement createElement(string label, object value)
        {
            XElement xelem = new XElement(node_tag, new XElement(label, value));
            return xelem;
        }

        protected void setAttribute(ref XElement xelem, string attribute_name, object attribute_value)
        {
            xelem.SetAttributeValue(attribute_name, attribute_value);
        }

        protected void removeAttribute(ref XElement xelem, string attribute_name)
        {
            xelem.SetAttributeValue(attribute_name, null);
        }

        //create XML Element with attribute
        protected XElement createElement( string attLabel, object att, string label, object value)
        {
            XElement xelem = createElement(label, value);
            xelem.SetAttributeValue(attLabel, att);
            return xelem;
        }

        protected void setChild(ref XElement xelem, string node_name, object node_value)
        {
            xelem.SetElementValue(node_name, node_value);
        }

        protected void removeChild(ref XElement xelem, string node_name)
        {
            xelem.SetElementValue(node_name, null);
        }

        #endregion

        #region queries
        protected IEnumerable<XElement> queryLvl1()
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                                            select n;
            return results;
        }

        protected IEnumerable<XElement> queryLvl1ByAttributes(string attr_name, string attr)
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                        where n.Attribute(attr_name).Value == attr
                        select n;
            return results;
        }

        protected IEnumerable<IGrouping<string, XElement>> queryLvl2Group(string lvl2_field)
        {
            IEnumerable<IGrouping<string, XElement>> results = from n in xml_file.Descendants(node_tag).Descendants(lvl2_field)
                                                                    group n by n.Value;
            return results;
        }

        protected IEnumerable<XElement> queryLvl3Range(string field, string start, string end)
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                                            where n.Element(field).Value.CompareTo(start) > 0
                                                  && n.Element(field).Value.CompareTo(end) < 0
                                            select n;
            return results;
        }

        
        protected IEnumerable<XElement> queryLvl3RangeAndTag(string tag_field, string tag, string range_field, string start, string end)
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                                            where n.Element(range_field).Value.CompareTo(start) > 0
                                                  && n.Element(range_field).Value.CompareTo(end) < 0
                                                  && n.Element(tag_field).Value.Equals(tag)
                                            select n;
            return results;
        }

        protected IEnumerable<XElement> queryLvl3RangeAndTag_Ordered(string tag_field, string tag, string range_field, string start, string end)
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                                            where n.Element(range_field).Value.CompareTo(start) > 0
                                                  && n.Element(range_field).Value.CompareTo(end) < 0
                                                  && n.Element(tag_field).Value.Equals(tag)
                                            orderby n.Element(range_field).Value
                                            select n;
            return results;
        }

        protected IEnumerable<XElement> queryLvl3(string tag_field,string tag)
        {
            IEnumerable<XElement> results = from n in xml_file.Descendants(node_tag)
                                            where n.Element(tag_field).Value.Equals(tag)
                                            select n;
            return results;
        }

        #endregion
        
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

