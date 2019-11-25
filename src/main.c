#include "../inc/cool.h"

// GLOBAL Variables
t_page       *page;

GtkBuilder   *builder;
GtkListBox    *box;

int   main(int ac, char **av)
{
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

    free(page);
    return (0);
}

/****************************************************************************/
/*                 Function of :BUTTON RESSOURCE PAGE                       */
/****************************************************************************/
int add_product()
{
  static int    nb_product;
  const char    *id_product;
  GtkWidget     *new_box;
  GtkWidget     *label;
  GtkEntry      *input_idproduct;

  nb_product = 0;
  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_product_box"));

  new_box = gtk_list_box_new();

  input_idproduct = GTK_ENTRY(gtk_builder_get_object(builder, "input_idproduct"));
  id_product    = gtk_entry_get_text(GTK_ENTRY(input_idproduct));
  label = gtk_label_new(id_product);

  gtk_container_add(GTK_CONTAINER(new_box), label);
  printf("idproduct = %s\n", id_product);
  gtk_list_box_insert(box, new_box, nb_product);
  gtk_widget_show_all(page->window);
  gtk_entry_set_text(GTK_ENTRY(input_idproduct), "");
  nb_product++;
  return (0);
}

/****************************************************************************/
/*                 Function of :PAGE MENU, BUTTON                           */
/****************************************************************************/
void go_to_menu()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->home_page);
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), GTK_WIDGET(page->menu_page));
  gtk_widget_show_all(page->window);
}

void goto_generate()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->menu_page);
  page->generate_page = GTK_WIDGET(gtk_builder_get_object(builder, "generate_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->generate_page);
  gtk_widget_show_all(page->window);
}

void goto_ressource(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->menu_page);
  page->ressource_page = GTK_WIDGET(gtk_builder_get_object(builder, "ressource_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->ressource_page);
  gtk_widget_show_all(page->window);
}

void goto_cocktail()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->menu_page);
  page->cocktail_page = GTK_WIDGET(gtk_builder_get_object(builder, "cocktail_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->cocktail_page);
  gtk_widget_show_all(page->window);

}

/****************************************************************************/
/*                 Function of :PAGE RESSOURCE, BUTTON                      */
/****************************************************************************/
void goto_scanner()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->ressource_page);
  page->scanner_page = GTK_WIDGET(gtk_builder_get_object(builder, "scanner_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->scanner_page);
  gtk_widget_show_all(page->window);
}

void goto_form()
{
  return ;
}
/****************************************************************************/
/*                Function of: Return Button                                */
/****************************************************************************/
void generate_to_menu()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->generate_page);
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
}

void ressource_to_menu()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->ressource_page);
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
}

void cocktail_to_menu()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->cocktail_page);
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
}

void scanner_to_ressource()
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->scanner_page);
  page->ressource_page = GTK_WIDGET(gtk_builder_get_object(builder, "ressource_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->ressource_page);
  gtk_widget_show_all(page->window);
}
