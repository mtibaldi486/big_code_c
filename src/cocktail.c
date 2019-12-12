#include "../inc/cool.h"

void load_cocktail_page(GtkButton *button, gchar info[255])
{
  (void)button;

  gtk_container_remove(GTK_CONTAINER(page->window), page->select_page);
  page->cocktail_page = GTK_WIDGET(gtk_builder_get_object(builder, "cocktail_page"));
  gtk_container_add(GTK_CONTAINER(page->window), page->cocktail_page);
  display_elem(info);
  gtk_widget_show_all(page->window);

  return ;
}

char *make_path_cocktail(const char *s1, char *s2)
{
  char *path;

  if (!(path = malloc(sizeof(char) * 200)))
    return (NULL);
  strcpy(path, s1);
  strcat(path, s2);
  return (path);

}

void display_elem(gchar info[255])
{
  char      **array_info;
  int       i;
  GtkWidget *pic_cocktail;
  GtkWidget *pic_recipe;


  i = -1;
  array_info = ft_split(info, ';');
  while (array_info[++i])
    printf("info[%d] = '%s'\n",i,  array_info[i]);
  pic_cocktail = gtk_image_new_from_file(array_info[3] + 3);
  pic_recipe = gtk_image_new_from_file(array_info[4] + 3);

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_cocktail, 600, 100);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_recipe, 50, 50);

}
