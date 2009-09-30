#include <gtk/gtk.h>
int GSGLoginWindow()
{
	GtkWidget *window;
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window),"Happy Fish");
	gtk_container_set_border_width(GTK_CONTAINER(window),20);
	GtkWidget *table;
	table = gtk_table_new(2,2,TRUE);
	gtk_container_add(GTK_CONTAINER(window),table);
	GtkWidget *button1;
	button1 = gtk_button_new_with_label("Button 1");
	gtk_table_attach_defaults(GTK_TABLE(table),button1,0,1,0,1);
	GtkWidget *button2;
	button2 = gtk_button_new_with_label("Button 2");
	gtk_table_attach_defaults(GTK_TABLE(table),button2,1,2,0,1);
	gtk_widget_show(button2);
	gtk_widget_show (button1);
	gtk_widget_show  (window);


	return 0;
}
int main(int argc,char *argv[])
{
	gtk_init (&argc, &argv);
	GSGLoginWindow();
	gtk_main ();
	return 0;
}
