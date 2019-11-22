#include "../inc/cool.h"

// GLOBAL Variables
GtkWidget    *window;
GtkWidget    *fixed1;
GtkWidget    *btn_first;
GtkWidget    *btn_home_cocktail;
GtkWidget    *btn_home_generate;
GtkWidget    *btn_home_add;
GtkBuilder   *builder;

int   main(int ac, char **av)
{
    gtk_init(&ac, &av);

    builder = gtk_builder_new_from_file("gladeproject.glade");
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_builder_connect_signals(builder, NULL);

    btn_first = GTK_WIDGET(gtk_builder_get_object(builder, "btn_first"));

    gtk_widget_show(window);

    gtk_main();

    return (0);
}

void go_to_home()
{
  gtk_widget_destroy(btn_first);

  fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
  btn_home_cocktail = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_cocktail"));

  gtk_container_add(GTK_CONTAINER(window), fixed1);

  gtk_widget_show_all(window);
}
