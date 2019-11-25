#include "../inc/cool.h"

// GLOBAL Variables
GtkWidget    *window;


  GtkWidget    *menu_page;
  GtkWidget    *generate_page;
  GtkWidget    *ressource_page;
  GtkWidget    *scroll_window;

GtkWidget    *btn_first;
GtkWidget    *btn_home_cocktail;
GtkWidget    *btn_home_generate;
GtkWidget    *btn_return_menu;
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
  gtk_container_remove(GTK_CONTAINER(window), btn_first);

  menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  btn_home_generate = GTK_WIDGET(gtk_builder_get_object(builder, "btn_home_generate "));

  gtk_container_add(GTK_CONTAINER(window), menu_page);

  gtk_widget_show_all(window);
}

void goto_generate()
{
  gtk_container_remove(GTK_CONTAINER(window), menu_page);

  generate_page = GTK_WIDGET(gtk_builder_get_object(builder, "generate_page"));
  btn_return_menu = GTK_WIDGET(gtk_builder_get_object(builder, "btn_return_menu "));

  gtk_container_add(GTK_CONTAINER(window), generate_page);

  gtk_widget_show_all(window);
}

void button_return_menu()
{
  gtk_container_remove(GTK_CONTAINER(window), generate_page);

  menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));

  gtk_container_add(GTK_CONTAINER(window), menu_page);

  gtk_widget_show_all(window);
}

void goto_ressource()
{
  gtk_container_remove(GTK_CONTAINER(window), menu_page);

  ressource_page = GTK_WIDGET(gtk_builder_get_object(builder, "ressource_page"));
  scroll_window = GTK_WIDGET(gtk_builder_get_object(builder, "scroll_window"));

  gtk_container_add(GTK_CONTAINER(window), ressource_page);

  gtk_widget_show_all(window);
}
