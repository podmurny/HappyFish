/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package bugtracker;

/**
 *
 * @author slava
 */
public class CBugTrack
{

    private boolean login;
    // about access_level //
    // 0 - guest          //
    // 1 - tester         //
    // 2 - developer      //
    // 3 - lead developer //
    // 4 - project manager//
    private int access_level;
    //constructor

    public CBugTrack(String IP, String password)
    {
        login = false;
        access_level = 0;
    }
    //////////////////methods///////////////////////
    //login method 
    public int login(String login, String password)
    {
        //TODO
        //add here connection to database and login check
        return 0;
    }
}
