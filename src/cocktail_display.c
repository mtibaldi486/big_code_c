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
  GtkWidget  *fixed;
  int       i;

  i = 0;
  if (!(cocktail = ft_split(info, ';')))
    return (0);
  if (!(str_display = format_ingredient(info, nb)))
    return (0);
  fixed = display_ingredient(str_display);
  display_counter(info, fixed);
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

void  display_counter(const gchar *info, GtkWidget *fixed)
{
  GtkWidget     *button_pos;
  GtkWidget     *button_neg;
  GtkWidget     *entry;
  char          nb[2];

  entry = gtk_entry_new();
  button_pos = gtk_button_new_with_label("+");
  button_neg = gtk_button_new_with_label("-");

  gtk_widget_set_name(entry, info);
  info = strchr(info, ';') + 1;
  info = strchr(info, ';') + 1;
  mt_strccpy(nb, (char *)info, ';');
  gtk_entry_set_text(GTK_ENTRY(entry), nb);

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), button_pos, 1175, 370);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), button_neg, 975, 370);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), entry, 1015, 370);

  g_signal_connect(button_pos, "clicked", G_CALLBACK(inc_entry), (void *)entry);
  g_signal_connect(button_neg, "clicked", G_CALLBACK(dec_entry), (void *)entry);
}

void  inc_entry(GtkWidget *button, gpointer *data)
{
  GtkWidget     *entry;
  const gchar   *nb;
  const gchar   *info;
  int           res;

  (void)button;
  entry = GTK_WIDGET(data);
  info = gtk_widget_get_name(entry);
  printf("INFO TROUVER = %s\n", info);
  nb = gtk_entry_get_text(GTK_ENTRY(entry));
  res = atoi(nb) + 1;
  if (res > 0)
  {
    gtk_entry_set_text(GTK_ENTRY(entry), ft_itoa(res));
    printf("INFO SEND FIRST = %s\n", info);
    display_elem(info, res);
  }

}

void  dec_entry(GtkWidget *button, gpointer *data)
{
  GtkWidget     *entry;
  const gchar   *nb;
  const gchar   *info;
  int           res;

  (void)button;
  entry = GTK_WIDGET(data);
  info = gtk_widget_get_name(entry);

  nb = gtk_entry_get_text(GTK_ENTRY(entry));
  res = atoi(nb) - 1;
  if (res > 0)
  {
    gtk_entry_set_text(GTK_ENTRY(entry), ft_itoa(res));
    display_elem(info, res);
  }


}
