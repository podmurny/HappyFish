/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package Test;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 *
 * @author slava
 */
public class CopyBytes
{
     public static void main(String[] args) throws IOException {
        BufferedWriter out = new BufferedWriter(new FileWriter("D:/output.txt"));
        try {
            String s = "asdfgdf";
            out.write(s);
            out.close();
            } finally
            {
             BufferedReader out1 = new BufferedReader(new FileReader("D:/output.txt"));
             String s1 =null;
             s1=out1.readLine();
             System.out.println(s1);
             out1.close();
            }
        }

}
