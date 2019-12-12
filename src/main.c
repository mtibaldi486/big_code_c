#include "../inc/cool.h"

int   main(int ac, char **av)
{
    printf("begin = %p\nbegin_cocktail = %p\n", begin, begin_cocktail);
    gtk_init(&ac, &av);
    if(!(page = malloc(sizeof(t_page))))
      return (0);

    builder = gtk_builder_new_from_file("gladeproject.glade");
    page->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(page->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

    page->home_page = GTK_WIDGET(gtk_builder_get_object(builder, "home_page"));
    gtk_container_add(GTK_CONTAINER(page->window), GTK_WIDGET(page->home_page));
    gtk_widget_show(page->window);

    gtk_main();
    /*
    Free t'es list ici
    */
    free(page);
    return (0);
  }
