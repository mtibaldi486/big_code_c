#include "../inc/cool.h"

void display_mark(const gchar *mark, char *id)
{
  GtkWidget     *fixed;
  GtkWidget     *button_pos;
  GtkWidget     *button_neg;
  GtkWidget     *img;
  const gchar   path_img[25];

  fixed = gtk_fixed_new();
  gtk_widget_set_name (fixed, mark);
  button_pos = gtk_button_new_with_label("+");
  button_neg = gtk_button_new_with_label("-");
  gtk_widget_set_name (button_pos, id);
  gtk_widget_set_name (button_neg, id);
  strcpy((char *)path_img, "img/mark/");
  strcat((char *)path_img, mark);
  strcat((char *)path_img, ".png");
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
  const gchar   *mark;
  char          tmp[2];
  char          id[4];

  fixed = (void *)data;
  mark = gtk_widget_get_name(fixed);
  strcpy(id, gtk_widget_get_name(GTK_WIDGET(button)));
  if (*mark == '5')
    return ;
  strcpy(tmp, mark);
  tmp[0]++;
  gtk_widget_destroy(fixed);
  update_mark(tmp, id);
  display_mark((const gchar *)tmp, id);
}

void mark_down(GtkButton *button, gpointer *data)
{
  GtkWidget     *fixed;
  const gchar   *mark;
  char          tmp[3];
  char          id[4];

  fixed = (void *)data;
  mark = gtk_widget_get_name(fixed);
  strcpy(id,  gtk_widget_get_name(GTK_WIDGET(button)));
  if (*mark == '0')
    return ;
  strcpy(tmp, mark);
  tmp[0]--;
  gtk_widget_destroy(fixed);
  update_mark(tmp, id);
  display_mark((const gchar *)tmp, id);
}

void update_mark(char *mark, char *id)
{
  MYSQL *con = NULL;
  char  request[50];

  sprintf(request, "UPDATE cocktails SET star = %s WHERE id = %s", mark, id);
  if (!(con = connection_bdd(con)))
    return ;
  if (mysql_query(con, request))
      return ;
  return ;
}
