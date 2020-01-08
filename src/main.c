#include "../inc/cool.h"

const gchar *load_conf(void)
{
  int     fd;
  int     ret;
  char    buff[1024];

  if (!(fd = open("conf.con" , O_RDONLY)))
  {

    return (NULL);
  }


  return (NULL);
}

int   main(int ac, char **av)
{
    gtk_init(&ac, &av);
    if(!(page = malloc(sizeof(t_page))))
      return (0);

    builder = gtk_builder_new_from_file("gladeproject.glade");
    page->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    g_signal_connect(page->window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_builder_connect_signals(builder, NULL);

  /*page->window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    page->fixed = gtk_fixed_new();
    page->img = gtk_image_new_from_file("img/background/red_home.png");
    g_signal_connect(page->window, "destroy", G_CALLBACK(gtk_main_quit), NULL); */

    page->home_page = GTK_WIDGET(gtk_builder_get_object(builder, "home_page"));
    gtk_container_add(GTK_CONTAINER(page->window), GTK_WIDGET(page->home_page));

    gtk_widget_show(page->window);
//    adjust_stock();

    gtk_main();
    /*
    Free tes list ici
    */
    free(page);
    return (0);
  }
