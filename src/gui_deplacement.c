#include "../inc/cool.h"

/****************************************************************************/
/*                 Function of :PAGE MENU, BUTTON                           */
/****************************************************************************/
void go_to_menu(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->home_page);
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), GTK_WIDGET(page->menu_page));
  gtk_widget_show_all(page->window);
  return ;
}

void goto_generate(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->menu_page);
  page->generate_page = GTK_WIDGET(gtk_builder_get_object(builder, "generate_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->generate_page);
  gtk_widget_show_all(page->window);
  generate_cocktail();
  return ;
}

void goto_ressource(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->menu_page);
  page->ressource_page = GTK_WIDGET(gtk_builder_get_object(builder, "ressource_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->ressource_page);
  gtk_widget_show_all(page->window);
  select_ingredient();
  return ;
}

void goto_cocktail(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->menu_page);
  page->select_page = GTK_WIDGET(gtk_builder_get_object(builder, "select_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->select_page);
  load_lst_cocktails();
  gtk_widget_show_all(page->window);
  return ;

}

/****************************************************************************/
/*                 Function of :PAGE RESSOURCE, BUTTON                      */
/****************************************************************************/
void goto_scanner(void)
{
  GtkWidget *lab_ok;
  GtkWidget *lab_ko;

  lab_ok = GTK_WIDGET(gtk_builder_get_object(builder, "lab_add_ok"));
  lab_ko = GTK_WIDGET(gtk_builder_get_object(builder, "lab_add_ko"));
  gtk_container_remove(GTK_CONTAINER(page->window), page->ressource_page);
  page->scanner_page = GTK_WIDGET(gtk_builder_get_object(builder, "scanner_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->scanner_page);
  gtk_widget_show_all(page->window);
  gtk_widget_hide(lab_ok);
  gtk_widget_hide(lab_ko);
  return ;
}

void goto_form(void)
{
  return ;
}
/****************************************************************************/
/*                Function of: Return Button                                */
/****************************************************************************/
void generate_to_menu(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->generate_page);
  //page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
  return ;
}

void ressource_to_menu(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->ressource_page);
  //page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
  return ;
}

void cocktail_to_menu(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->select_page);
  //page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
  return ;
}

void scanner_to_ressource(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->scanner_page);
  //page->ressource_page = GTK_WIDGET(gtk_builder_get_object(builder, "ressource_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->ressource_page);
  gtk_widget_show_all(page->window);
  select_ingredient();
  return ;
}

void cocktail_to_select(void)
{
  gtk_widget_destroy(page->cocktail_page);
  //page->select_page = GTK_WIDGET(gtk_builder_get_object(builder, "select_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->select_page);
  load_lst_cocktails();
  gtk_widget_show_all(page->window);
  return ;
}

void cocktail_to_generate(void)
{
  gtk_widget_destroy(page->cocktail_page);
  //page->select_page = GTK_WIDGET(gtk_builder_get_object(builder, "select_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->generate_page);
  load_lst_cocktails();
  gtk_widget_show_all(page->window);
  return ;
}

/****************************************************************************/
/*                Function of:DYNAMIC BUTTON                                */
/****************************************************************************/
void select_to_cocktail(GtkButton *button)
{
  const gchar *info;
  GtkWidget   *button2;
  GtkWidget   *backscreen;

  info = gtk_widget_get_name(GTK_WIDGET(button));
  button2 = gtk_button_new_with_label ("Retour");
  page->cocktail_page = GTK_WIDGET(gtk_builder_get_object(builder, "cocktail_page"));
  backscreen = gtk_image_new_from_file(page->img);
  g_signal_connect(button2, "clicked", G_CALLBACK(cocktail_to_select), NULL);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), backscreen, 0, 0);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page),button2, 76, 41);
  gtk_container_remove(GTK_CONTAINER(page->window), page->select_page);
  gtk_container_add(GTK_CONTAINER(page->window), page->cocktail_page);
  load_cocktail_page(info);
  gtk_widget_show_all(page->window);
  return ;
}

void generate_to_cocktail(GtkButton *button)
{
  const gchar *info;
  GtkWidget   *button2;
  GtkWidget   *backscreen;

  button2 = gtk_button_new_with_label ("Retour");
  page->cocktail_page = GTK_WIDGET(gtk_builder_get_object(builder, "cocktail_page"));
  info = gtk_widget_get_name(GTK_WIDGET(button));
  backscreen = gtk_image_new_from_file("img/background/red_screen.png");
  g_signal_connect(button2, "clicked", G_CALLBACK(cocktail_to_generate), NULL);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), backscreen, 0, 0);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page),button2, 76, 41);
  gtk_container_remove(GTK_CONTAINER(page->window), page->generate_page);
  gtk_container_add(GTK_CONTAINER(page->window), page->cocktail_page);
  load_cocktail_page(info);
  gtk_widget_show_all(page->window);
  return ;
}
