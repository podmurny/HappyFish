package bugtracker;

import java.io.File;
import org.w3c.dom.*;
import javax.xml.parsers.*;
import javax.xml.transform.*;
import javax.xml.transform.stream.*;
import javax.xml.transform.dom.*;

public class CXML
 {

    public CXML()
    {
    }

    public void Create(int m,String[][] proj_info,int n,String[][][] task_info,int k,String[][][] bug_info)
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

        e2.setAttribute("name",proj_info[i][0]);
        e2.setAttribute("info",proj_info[i][1]);

        Element e3 = doc.createElement("Tasks");
        e2.appendChild(e3);
        for (int j = 0; j < n; j++)
        {
        Element e4 = doc.createElement("Task");
        e3.appendChild(e4);
        e4.setAttribute("status",task_info[i][j][1]);
        e4.setAttribute("info",task_info[i][j][0]);
        }

        Element e5 = doc.createElement("Bugs");
        e2.appendChild(e5);
        for (int t = 0; t < k; t++)
        {
        Element e6 = doc.createElement("Bug");
        e5.appendChild(e6);
        e6.setAttribute("status",bug_info[i][t][1]);
        e6.setAttribute("info",bug_info[i][t][0]);
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
        transformer.transform(domSource, sr);
        String xml = sw.toString();
     }


public void Read (String proj_name,String request)
{
   String[][] ans;
  ans=new String[20][2];
  try {
  File file = new File("D:/output.xml");
  DocumentBuilderFactory dbf = DocumentBuilderFactory.newInstance();
  DocumentBuilder db = dbf.newDocumentBuilder();
  Document doc = db.parse(file);
  doc.getDocumentElement().normalize();
  String Root=doc.getDocumentElement().getNodeName();
  NodeList nodeLst = doc.getElementsByTagName("Project");

  for (int x = 0; x < nodeLst.getLength(); x++)
  {
    Node Project = nodeLst.item(x);

    Element Proj= (Element)nodeLst.item(x);
    String name = Proj.getAttribute("name");
    String info = Proj.getAttribute("info");
    Element fstElmnt = (Element) Project;
    NodeList Tasks_root = fstElmnt.getElementsByTagName("Tasks");

   //Element Task1= (Element)Tasks_root.item(0);
   // String name1 = Task1.getAttribute("name");
   // System.out.println(name1);
    int k=0;
    if ((proj_name.equals(name)) || (proj_name.equals("All")))
     if (request.equals("Tasks"))
     {
      Element Task = (Element) Project;
      NodeList Tasks = Task.getElementsByTagName("Task");
       for (int j = 0; j < Tasks.getLength(); j++)
        {
         Element current_Task = (Element)Tasks.item(j);
         String status = current_Task.getAttribute("status");
         //System.out.println(status);
         main.ans[k][0]=status;
         info = current_Task.getAttribute("info");
         //System.out.println(info);
         main.ans[k][1]=info;
         k++;
        }
     }
    k=0;
    if ((proj_name.equals(name)) || (proj_name.equals("All")))
     if (request.equals("Bugs"))
     {
      Element Bug = (Element) Project;
      NodeList Bugs = Bug.getElementsByTagName("Bug");
       for (int l = 0; l < Bugs.getLength(); l++)
        {
         Element current_Bug = (Element)Bugs.item(l);
         String status = current_Bug.getAttribute("status");
         main.ans[k][0]=status;
         info = current_Bug.getAttribute("info");
         main.ans[k][1]=info;
         k++;
        }
     }


  }
  }
  catch (Exception e) {}
   }
}

/*

package bugtracker;


public class main {
    public static String[][] ans;

    public static void main(String[] args)
    throws javax.xml.parsers.ParserConfigurationException,
             javax.xml.transform.TransformerException,
             javax.xml.transform.TransformerConfigurationException
     {
        int projects=2;
        int tasks=4;
        int bugs=4;


      ans=new String[20][2];
      String[][] proj_info;
      proj_info= new String[6][2];
      proj_info[0][0]="knopochka1";
      proj_info[1][0]="knopochka2";
      proj_info[2][0]="knopochka3";
      proj_info[3][0]="knopochka4";
      proj_info[0][1]="make a button1";
      proj_info[1][1]="make a button2";
      proj_info[2][1]="make a button3";
      proj_info[3][1]="make a button4";

      //

      String[][][] task_info;
      task_info= new String[2][6][2];
      task_info[0][0][0]="vkladka1";
      task_info[0][1][0]="vkladka2";
      task_info[0][2][0]="vkladka3";
      task_info[0][3][0]="vkladka4";
      task_info[0][0][1]="true";
      task_info[0][1][1]="true";
      task_info[0][2][1]="true";
      task_info[0][3][1]="true";
      task_info[1][0][0]="vkladka5";
      task_info[1][1][0]="vkladka6";
      task_info[1][2][0]="vkladka7";
      task_info[1][3][0]="vkladka7";
      task_info[1][0][1]="false";
      task_info[1][1][1]="false";
      task_info[1][2][1]="false";
      task_info[1][3][1]="false";

      //

      String[][][] bug_info;
      bug_info= new String[2][6][2];
      bug_info[0][0][0]="don`t work1";
      bug_info[0][1][0]="don`t work2";
      bug_info[0][2][0]="don`t work3";
      bug_info[0][3][0]="don`t work4";
      bug_info[0][0][1]="true";
      bug_info[0][1][1]="true";
      bug_info[0][2][1]="true";
      bug_info[0][3][1]="true";
      bug_info[1][0][0]="don`t work1";
      bug_info[1][1][0]="don`t work2";
      bug_info[1][2][0]="don`t work3";
      bug_info[1][3][0]="don`t work4";
      bug_info[1][0][1]="true";
      bug_info[1][1][1]="true";
      bug_info[1][2][1]="true";
      bug_info[1][3][1]="true";

      //

      CXML cxml = new CXML();
      cxml.Create(projects, proj_info, tasks, task_info, bugs, bug_info);
      cxml.Read("knopochka1","Bugs");
     // cxml.;
      for(int h=0;h<4;h++)
       System.out.println(ans[h][0]);

     }
}

*/


