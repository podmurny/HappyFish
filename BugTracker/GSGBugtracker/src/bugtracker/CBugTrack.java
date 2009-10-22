/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package bugtracker;

/**
 *
 * @author G-SG
 */

import java.sql.SQLException;
import java.util.logging.Level;
import java.util.logging.Logger;

public class CBugTrack
{

    java.sql.Connection connection = null;
    java.sql.Statement statement;
    java.sql.ResultSet result;
    static String host = null;
    static String port = null;
    static String login = null;
    static String password = null;
    static boolean default_port = true;
    String[][] Projects;
    String[][] Tasks;
    String[][] Bugs; 
    private int access_level = 0; //TODO
    // about access_level //
    // 0 - guest          //
    // 1 - tester         //
    // 2 - developer      //
    // 3 - lead developer //
    // 4 - project manager//

    //////////////////methods///////////////////////
    
    //Connection method
    public int connect_to_server(String login, String password, String host)
    {
        CBugTrack.login = login;
        String database = "ProjectManagement";
        String url = "jdbc:mysql://" + host + "/" + database;
        try
        {
            connection = java.sql.DriverManager.getConnection(url, login, password);
        } catch (SQLException ex)
        {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        return 0;
    }
    
    //Open forms: Add Project, Add Task, Add Bug
    //types: "Project", "Task", "Bug"
//    public int open_add_form(String type)
//    {
//        String name,info;//Variables that we will write to database
//        //TODO
//        //here we must add open form event
//        //and fill our variables
//        return 0;
//    }
    //Open form that add user
//    public int open_add_user()
//    {
//        String login, password;//variables that
//        int user_access_level;//we will write to database
//        //TODO
//        //Just open add user form and after click "Add" button
//        //read and send data to database
//        return 0;
//    }
    //public int add_user(String )
    
    public int get_all_project_info()
    {
        try
        {
            statement = connection.createStatement();
        } catch (SQLException ex)
        {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try
        {
            statement.executeQuery("SELECT DISTINCT ProjectName, ProjectInfo FROM Project");
        } catch (SQLException ex)
        {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try
        {
            result = statement.getResultSet();
        } catch (SQLException ex)
        {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        int i = 0;
        try {
            while (result.next() == true) {
                Projects[i][0] = result.getString(0);
                Projects[i][1] = result.getString(1);
                i++;
            }
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            statement.executeQuery("SELECT ProjectName, Task, TaskInfo, Priority, Status, Username FROM Task");
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            result = statement.getResultSet();
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        i = 0;
        try {
            while (result.next() == true) {
                Tasks[i][0] = result.getString(0);
                Tasks[i][1] = result.getString(1);
                Tasks[i][2] = result.getString(2);
                Tasks[i][3] = result.getString(3);
                Tasks[i][4] = result.getString(4);
                Tasks[i][5] = result.getString(5);
                i++;
            }
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            statement.executeQuery("SELECT ProjectName, Bug, BugInfo, Priority, Status, Username FROM Bugreports");
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            result = statement.getResultSet();
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        i = 0;
        try {
            while (result.next() == true) {
                Bugs[i][0] = result.getString(0);
                Bugs[i][1] = result.getString(1);
                Bugs[i][2] = result.getString(2);
                Bugs[i][3] = result.getString(3);
                Bugs[i][4] = result.getString(4);
                Bugs[i][5] = result.getString(5);
                i++;
            }
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        return 0;
    }
    
    //get all information from xml
    int read_xml()
    {
        return 0;
    }

    //set all information to xml
    int write_xml()
    {
        return 0;
    }
}
