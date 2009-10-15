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
    //private boolean login; Зачем?
    // about access_level //
    // 0 - guest          //
    // 1 - tester         //
    // 2 - developer      //
    // 3 - lead developer //
    // 4 - project manager//
    
    //constructor
    public CBugTrack(String login, String password, String host)
    {
        access_level = 0; //TODO
        CBugTrack.login = login;
        String database = "ProjectManagement";
        String url = "jdbc:mysql://" + host + "/" + database;
        try {
            connection = java.sql.DriverManager.getConnection(url, login, password);
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    //////////////////methods///////////////////////
    //login method 
    public int login(String login, String password)
    {
        //TODO
        //add here connection to database and login check
        return 0;
    }

    public int get_all_project_info() {

       String[] ProjectName;
       String[] ProjectInfo;
       String[] Tasks;
       String[] Bugs;

        try {
           statement = connection.createStatement();
        } catch (SQLException ex) {
           Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            statement.executeQuery("SELECT DISTINCT Task.ProjectName, Task.Task, Task.TaskInfo, Task.Priority, Task.Status, Project.ProjectInfo FROM Task INNER JOIN Project ON Task.ProjectName = Project.ProjectName WHERE Task.Username='" + login + "");
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        try {
            result = statement.getResultSet();
        } catch (SQLException ex) {
            Logger.getLogger(CBugTrack.class.getName()).log(Level.SEVERE, null, ex);
        }
        return 0;
     }
}
