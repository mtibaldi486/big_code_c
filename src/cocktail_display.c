#include "../inc/cool.h"

void display_picture(const gchar *info)
{
  GtkWidget   *pic_cocktail;
  GtkWidget   *pic_recipe;
  char        **array_cocktail;

  if (!(array_cocktail = ft_split(info, ';')))
    return ;

  pic_cocktail = gtk_image_new_from_file(array_cocktail[3] + 3);
  pic_recipe = gtk_image_new_from_file(array_cocktail[4] + 3);

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_cocktail, 980, 100);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_recipe, 135, 200);

  free_res(array_cocktail, 30);
}

int     display_elem(const gchar *info, int nb)
{
  char      **str_display;
  char      **cocktail;
  t_data    *data;
  int       i;

  i = 0;
  if (!(data = malloc(sizeof(t_data))))
    return (0);
  if (!(cocktail = ft_split(info, ';')))
    return (0);
  if (!(str_display = format_ingredient(info, nb)))
    return (0);
  data->fixed = display_ingredient(str_display);
  gtk_widget_show_all(page->window);
  display_counter(info, data, nb);
  while (str_display[i])
  {
    printf("display = '%s'\n", str_display[i]);
    i++;
  }


  free(str_display);
  return 1;
}

GtkWidget *display_ingredient(char **str_display)
{
  GtkWidget   *fixed;
  GtkWidget   *label;
  int         y;
  int         i;

  i = 0;
  y = 0;
  fixed = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), fixed, 600, 500);
  while (str_display[i])
  {
    label = gtk_label_new(str_display[i]);
    gtk_fixed_put(GTK_FIXED(fixed), label, 0, y);
    y += 21 ;
    i++;
  }
  return (fixed);
}

void  display_counter(const gchar *info, t_data *data, int indice)
{
  GtkWidget     *button_pos;
  GtkWidget     *button_neg;
  char          nb[2];

  data->entry = gtk_entry_new();
  button_pos = gtk_button_new_with_label("+");
  button_neg = gtk_button_new_with_label("-");

  gtk_widget_set_name(data->entry, info);
  if (!indice)
  {
    info = strchr(info, ';') + 1;
    info = strchr(info, ';') + 1;
    mt_strccpy(nb, (char *)info, ';');
    gtk_entry_set_text(GTK_ENTRY(data->entry), nb);
  }
  else
    gtk_entry_set_text(GTK_ENTRY(data->entry), ft_itoa(indice));

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), button_pos, 1175, 370);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), button_neg, 975, 370);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), data->entry, 1015, 370);

  g_signal_connect(button_pos, "clicked", G_CALLBACK(inc_entry), (void *)data);
  g_signal_connect(button_neg, "clicked", G_CALLBACK(dec_entry), (void *)data);
}

void  inc_entry(GtkWidget *button, gpointer *data_receive)
{
  t_data        *data;
  const gchar   *nb;
  const gchar   *info;
  int           res;

  (void)button;
  data = (void *)data_receive;
  info = gtk_widget_get_name(data->entry);
  nb = gtk_entry_get_text(GTK_ENTRY(data->entry));
  res = atoi(nb) + 1;
  if (res <= 0)
    return ;
  gtk_widget_destroy(data->fixed);

  gtk_entry_set_text(GTK_ENTRY(data->entry), ft_itoa(res));
  display_elem(info, res);
  gtk_widget_show_all(page->window);
  free(data);
}

void  dec_entry(GtkWidget *button, gpointer *data_receive)
{
  t_data        *data;
  const gchar   *nb;
  const gchar   *info;
  int           res;

  (void)button;
  data = (void *)data_receive;
  info = gtk_widget_get_name(data->entry);

  nb = gtk_entry_get_text(GTK_ENTRY(data->entry));
  res = atoi(nb) - 1;
  if (res <= 0)
    return ;

  gtk_widget_destroy(data->fixed);
  gtk_entry_set_text(GTK_ENTRY(data->entry), ft_itoa(res));
  display_elem(info, res);
  gtk_widget_show_all(page->window);
  free(data);

}
