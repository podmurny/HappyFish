#include "GSGgtk.h"

int GsgLoginWindow(int argc,char *argv[])
{
    GtkWidget *window;


    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_show  (window);

    gtk_main ();

    return 0;
}
int main(int argc,char *argv[])
{
    return 0;
}