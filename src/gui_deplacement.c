#include "../inc/cool.h"

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
