/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package com.toy.anagrams.lib;

/**
 *
 * @author Home
 */
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
      bug_info[1][0][0]="don`t work5";
      bug_info[1][1][0]="don`t work6";
      bug_info[1][2][0]="don`t work7";
      bug_info[1][3][0]="don`t work8";
      bug_info[1][0][1]="true";
      bug_info[1][1][1]="true";
      bug_info[1][2][1]="true";
      bug_info[1][3][1]="true";

      //

      CXML cxml = new CXML();
      cxml.Create(projects, proj_info, tasks, task_info, bugs, bug_info);
      cxml.Read("All","Tasks");
            
     }
}
