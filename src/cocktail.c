#include "../inc/cool.h"

void load_cocktail_page(GtkButton *button)
{
  (void)button;
  const gchar *info;

  info = gtk_widget_get_name(GTK_WIDGET(button));
  printf("REAL INFO = '%s'\n", info);
  gtk_container_remove(GTK_CONTAINER(page->window), page->select_page);
  page->cocktail_page = GTK_WIDGET(gtk_builder_get_object(builder, "cocktail_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->cocktail_page);
  display_elem(info);
  gtk_widget_show_all(page->window);

  return ;
}

void display_elem(const gchar *info)
{
  GtkWidget *pic_cocktail;
  GtkWidget *pic_recipe;
  char      **array_info;

  array_info = ft_split(info, ';');
  pic_cocktail = gtk_image_new_from_file(array_info[3] + 3);
  pic_recipe = gtk_image_new_from_file(array_info[4] + 3);

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_cocktail, 980, 100);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_recipe, 135, 200);

}
