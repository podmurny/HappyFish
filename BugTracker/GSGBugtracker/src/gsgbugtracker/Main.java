/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package gsgbugtracker;

import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import org.mozilla.javascript.JavaAdapter;

/**
 *
 * @author slava
 */
public
        class Main
{
    private static
    MainForm mainform;

    /**
     * @param args the command line arguments
     */
    public static
            void main(String[] args)
    {
        try
        {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (ClassNotFoundException ex)
        {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (InstantiationException ex)
        {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex)
        {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        } catch (UnsupportedLookAndFeelException ex)
        {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
        mainform = new MainForm();
        mainform.setVisible(true);
        mainform.setEnabled(true);
    }
}
