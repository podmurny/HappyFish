package bugtracker;

import java.io.File;
import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import javax.xml.transform.dom.*;


public class CXML
 {
    public void Create(int m,String[] proj_info,int n,String task_info,int k,String bug_info)
      throws javax.xml.parsers.ParserConfigurationException,
             javax.xml.transform.TransformerException,
             javax.xml.transform.TransformerConfigurationException
    {

        DocumentBuilderFactory factory
          = DocumentBuilderFactory.newInstance();
        DocumentBuilder builder = factory.newDocumentBuilder();
        DOMImplementation impl = builder.getDOMImplementation();

        Document doc = impl.createDocument(null,null,null);
        Element e1 = doc.createElement("Projects");
        doc.appendChild(e1);
        for (int i = 0; i < m; i++)
        {
        Element e2 = doc.createElement("Project");
        e1.appendChild(e2);

        e2.setAttribute("name","");
        e2.setAttribute("info","");

        Element e3 = doc.createElement("Tasks");
        e2.appendChild(e3);
        for (int j = 1; j <= n; j++)
        {
        Element e4 = doc.createElement("Task");
        e3.appendChild(e4);
        e4.setAttribute("status","");
        e4.setAttribute("info",task_info);
        }

        Element e5 = doc.createElement("Bugs");
        e2.appendChild(e5);
        for (int t = 1; t <= k; t++)
        {
        Element e6 = doc.createElement("Bug");
        e5.appendChild(e6);
        e6.setAttribute("status","");
        e6.setAttribute("info",bug_info);
        }
        }
        DOMSource domSource = new DOMSource(doc);
        TransformerFactory tf = TransformerFactory.newInstance();
        Transformer transformer = tf.newTransformer();
        transformer.setOutputProperty(OutputKeys.METHOD, "xml");
        transformer.setOutputProperty(OutputKeys.ENCODING,"UTF-8");
        transformer.setOutputProperty("{http://xml.apache.org/xslt}indent-amount", "4");
        transformer.setOutputProperty(OutputKeys.INDENT, "yes");
        java.io.StringWriter sw = new java.io.StringWriter();
        StreamResult sr = new StreamResult("D:/output.xml");
     }


public void Read ()
{

  try {
  File file = new File("D:/output.xml");
  DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
  DocumentBuilder db = dbf.newDocumentBuilder();
  Document doc = db.parse(file);
  doc.getDocumentElement().normalize();
  String Root=doc.getDocumentElement().getNodeName();
  NodeList nodeLst = doc.getElementsByTagName("Project");
  System.out.println("Information of all employees");

  for (int i = 0; i < nodeLst.getLength(); i++)
  {
    Node Project = nodeLst.item(i);

    Element Proj= (Element)nodeLst.item(i);
    String name = Proj.getAttribute("name");
    System.out.println(name);
    String info = Proj.getAttribute("info");
    System.out.println(info);

    Element fstElmnt = (Element) Project;
    NodeList Tasks_root = fstElmnt.getElementsByTagName("Tasks");

    Element Task1= (Element)Tasks_root.item(0);
    String name1 = Task1.getAttribute("name");
    System.out.println(name1);

    Element Task = (Element) Project;
    NodeList Tasks = Task.getElementsByTagName("Task");
      for (int j = 0; j < Tasks.getLength(); j++)
      {
        Element current_Task = (Element)Tasks.item(j);
        String status = current_Task.getAttribute("status");
        System.out.println(status);
        info = current_Task.getAttribute("info");
        System.out.println(info);
      }
      Element Bug = (Element) Project;
      NodeList Bugs = Bug.getElementsByTagName("Bug");
      for (int j = 0; j < Bugs.getLength(); j++)
      {
        Element current_Bug = (Element)Bugs.item(j);
        String status = current_Bug.getAttribute("status");
        System.out.println(status);
        info = current_Bug.getAttribute("info");
        System.out.println(info);
      }


  }
  }
  catch (Exception e) {}
 }






    public static void main( String args[])
      throws javax.xml.parsers.ParserConfigurationException,
             javax.xml.transform.TransformerException,
             javax.xml.transform.TransformerConfigurationException,
             java.lang.ArrayIndexOutOfBoundsException
     {
        int projects=10;
        int tasks=2;
        int bugs=2;
        int m=2;

      String proj_info[];
      proj_info= new String[2];
      proj_info[0]="knopochka";
      proj_info[1]="knopochka blin";
     // String proj_info="";
      String task_info="vkladka";
      String bug_info="don`t work";
      new CXML().Create(projects,proj_info,tasks,task_info,bugs,bug_info);
      new CXML().Read();
     }
}
