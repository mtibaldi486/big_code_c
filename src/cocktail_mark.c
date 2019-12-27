#include "../inc/cool.h"

void display_mark(const gchar *mark, char *id)
{
  GtkWidget     *fixed;
  GtkWidget     *button_pos;
  GtkWidget     *button_neg;
  GtkWidget     *img;
  const gchar   path_img[25];

  printf("display mark = %s\n", mark);
  fixed = gtk_fixed_new();
  gtk_widget_set_name (fixed, mark);
  button_pos = gtk_button_new_with_label("+");
  button_neg = gtk_button_new_with_label("-");
  gtk_widget_set_name (button_pos, id);
  gtk_widget_set_name (button_neg, id);
  strcpy((char *)path_img, "img/mark/");
  strcat((char *)path_img, mark);
  strcat((char *)path_img, ".png");
  printf("path = '%s'\n", path_img);
  img = gtk_image_new_from_file(path_img);

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), fixed, 120, 550);
  gtk_fixed_put(GTK_FIXED(fixed), button_neg, 0, 0);
  gtk_fixed_put(GTK_FIXED(fixed), button_pos, 260, 0);
  gtk_fixed_put(GTK_FIXED(fixed), img, 40, 0);

  g_signal_connect(button_pos, "clicked", G_CALLBACK(mark_up), (void *)fixed);
  g_signal_connect(button_neg, "clicked", G_CALLBACK(mark_down), (void *)fixed);

  gtk_widget_show_all(page->window);
}

void mark_up(GtkButton *button, gpointer *data)
{
  GtkWidget     *fixed;
  const gchar   *name;
  char          tmp[2];
  char          id[4];

  fixed = (void *)data;
  name = gtk_widget_get_name(fixed);
  strcpy(id, gtk_widget_get_name(GTK_WIDGET(button)));
  printf("id = '%s'\n", id);
  printf("name = '%s'\n", name);
  if (*name == '5')
    return ;
  strcpy(tmp, name);
  tmp[0]++;
  gtk_widget_destroy(fixed);
  display_mark((const gchar *)tmp, id);
}

void mark_down(GtkButton *button, gpointer *data)
{
  GtkWidget     *fixed;
  const gchar   *name;
  char          tmp[3];
  char          id[4];

  fixed = (void *)data;
  name = gtk_widget_get_name(fixed);
  strcpy(id,  gtk_widget_get_name(GTK_WIDGET(button)));
  printf("name = '%s'\n", name);
  printf("id = '%s'\n", id);
  if (*name == '0')
    return ;
  strcpy(tmp, name);
  tmp[0]--;
  gtk_widget_destroy(fixed);
  display_mark((const gchar *)tmp, id);
}
