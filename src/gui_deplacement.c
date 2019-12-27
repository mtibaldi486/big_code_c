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
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
  return ;
}

void ressource_to_menu(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->ressource_page);
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
  return ;
}

void cocktail_to_menu(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->select_page);
  page->menu_page = GTK_WIDGET(gtk_builder_get_object(builder, "menu_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->menu_page);
  gtk_widget_show_all(page->window);
  return ;
}

void scanner_to_ressource(void)
{
  gtk_container_remove(GTK_CONTAINER(page->window), page->scanner_page);
  page->ressource_page = GTK_WIDGET(gtk_builder_get_object(builder, "ressource_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->ressource_page);
  gtk_widget_show_all(page->window);
  return ;
}

void cocktail_to_select(void)
{
  gtk_widget_destroy(page->cocktail_page);
  //page->select_page = GTK_WIDGET(gtk_builder_get_object(builder, "select_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->select_page);
  gtk_widget_show_all(page->window);
  return ;
}
