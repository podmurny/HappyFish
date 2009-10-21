/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bugtracker;

/**
 *
 * @author slava
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
    private int access_level; //TODO
    // about access_level //
    // 0 - guest          //
    // 1 - tester         //
    // 2 - developer      //
    // 3 - lead developer //
    // 4 - project manager//

    //constructor
    public CBugTrack(String login, String password, String host)
    {
        access_level = 0; 
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
    }
    //Destructor
    protected void finalize ()
    {
        //TODO
        //Add disconnect from database
    }
    //
    //////////////////methods///////////////////////
    //login method 

    public int login(String login, String password)
    {
        //TODO
        //add here connection to database and login check
        return 0;
    }
    //Open forms: Add Project, Add Task , Add Bug
    //types: "Project" , "Task" , "Bug"
    public int open_add_form(String type)
    {
        String name,info;//Variables that we will write to database
        //TODO
        //here we must add open form event
        //and fill our variables
        return 0;
    }
    //Open form that add user
    public int open_add_user()
    {
        String login,password;//vaariables that 
        int user_access_level;//we will write to database
        //TODO
        //Just open add user form and after click "Add" button
        //read and send data to database
        return 0;
    }
    //public int add_user(String )
    public int get_all_project_info()
    {

        String[] ProjectName;
        String[] ProjectInfo;
        String[] Tasks;
        String[] Bugs;

        try
        {
            statement = connection.createStatement();
        } catch (SQLException ex)
        {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try
        {
            statement.executeQuery("SELECT DISTINCT Task.ProjectName, Task.Task, Task.TaskInfo, Task.Priority, Task.Status, Project.ProjectInfo FROM Task INNER JOIN Project ON Task.ProjectName = Project.ProjectName WHERE Task.Username='" + login + "");
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
        return 0;
    }
    //get all information from xml
    int get_xml()
    {
        return 0;
    }
    //set all information to xml
    int set_xml()
    {
        return 0;
    }
}
