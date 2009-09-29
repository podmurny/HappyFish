#include "GSGgtk.h"
#include <gtk-2.0/gtk/gtkobject.h>
#include <gtk-2.0/gtk/gtk.h>
int GsgLoginWindow(int argc,char *argv[])
{
    GtkWidget *window;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_show  (window);

    gtk_main ();

    return 0;
}