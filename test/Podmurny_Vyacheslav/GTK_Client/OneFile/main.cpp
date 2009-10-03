#include <gtk/gtk.h>

int GSGLoginWindow()
{
    /*********** Window widget **********/
    GtkWidget *window; //declare widget window
    //create widget - window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    //set title of window widget
    gtk_window_set_title(GTK_WINDOW(window), "Happy Fish");
    //set size of a window
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 300);
    //set size of a border width
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    /*********** Window widget end **********/
    /*********** Vertical box widget **********/
    GtkWidget *vbox; //declare table widget
    //create vertical box true mean equals onjects in container
    //and seciond argument mean spasing between objects
    vbox = gtk_vbox_new(TRUE, 20);
    //adding table in window
    gtk_container_add(GTK_CONTAINER(window), vbox);
    /*********** Vertical box widget end **********/
    /*********** Vertical box widget **********/
    GtkWidget *label_Login; //declare label widget
    //create label with text
    label_Login = gtk_label_new("Login:");
    //set aligment of text
    gtk_misc_set_alignment(GTK_MISC(label_Login), 0, 0);
    //pack label in vertical box
    gtk_box_pack_start_defaults(GTK_BOX(vbox), label_Login);
    //show label
    gtk_widget_show(label_Login);
    GtkWidget *text_login; //
    text_login = gtk_entry_new_with_max_length(15);
    //text_login = gtk_text_view_new();
    gtk_box_pack_start_defaults(GTK_BOX(vbox), text_login);
    gtk_widget_show(text_login); //show widget
    GtkWidget *label_password; //declare widget
    //create label with text
    label_password = gtk_label_new("Password:");
    //set aligment of text
    gtk_misc_set_alignment(GTK_MISC(label_password), 0, 0);
    //pack label in vertical box
    gtk_box_pack_start_defaults(GTK_BOX(vbox), label_password);
    gtk_widget_show(label_password); //show widget
    GtkWidget *button_login;
    button_login = gtk_button_new_with_label("Login");
    gtk_box_pack_start_defaults(GTK_BOX(vbox), button_login);
    GtkWidget *button_exit;
    button_exit = gtk_button_new_with_label("Exit");
    gtk_box_pack_start_defaults(GTK_BOX(vbox), button_exit);

    gtk_widget_show(button_login);
    gtk_widget_show(button_exit);
    gtk_widget_show(vbox);
    gtk_widget_show(window);


    return 0;
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    //create Login window
    GSGLoginWindow();
    gtk_main();
    return 0;
}
