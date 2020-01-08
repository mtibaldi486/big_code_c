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

void display_name(const gchar *info)
{
  GtkWidget      *lab_name;
  GtkWidget      *lab_nb;
  gchar          tmp_name[25];
  gchar          tmp[200];
  gchar          *name;

  mt_strccpy(tmp_name, strchr(info, ';') + 1, ';');
  sprintf(tmp, "<span face=\"Verdana\" underline=\"double\"foreground=\"#ffffff\" size=\"xx-large\"><b>%s</b></span>\n", tmp_name);
  name = g_locale_to_utf8(tmp, -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
  lab_name=gtk_label_new(name); // Application de la convertion à notre label
  g_free(name); // Libération de la mémoire
  name = g_locale_to_utf8("<span face=\"Verdana\" foreground=\"#ffffff\" size=\"medium\"><b>Nombre de personnes :</b></span>", -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
  lab_nb=gtk_label_new(name); // Application de la convertion à notre label
  g_free(name); // Libération de la mémoire
  gtk_label_set_use_markup(GTK_LABEL(lab_name), TRUE); // On dit que l'on utilise les balises pango
  gtk_label_set_use_markup(GTK_LABEL(lab_nb), TRUE); // On dit que l'on utilise les balises pango
  gtk_label_set_justify(GTK_LABEL(lab_name), GTK_JUSTIFY_CENTER); // On centre notre texte

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), lab_nb, 975, 370);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), lab_name, 500, 200);
}

int     display_elem(const gchar *info, int nb)
{
  char        **str_display;
  char        **cocktail;
  t_data      *data;

  if (!(data = malloc(sizeof(t_data))))
    return (0);
  if (!(cocktail = ft_split(info, ';')))
    return (0);
  if (!(str_display = format_ingredient(info, nb)))
    return (0);
  data->fixed = display_ingredient(str_display);
  gtk_widget_show_all(page->window);
  display_counter(info, data, nb);

  free(str_display);
  return 1;
}

GtkWidget *display_ingredient(char **str_display)
{
  GtkWidget   *fixed;
  GtkWidget   *label;
  gchar       format_display[200];
  gchar       buff[1024] = {0};
  gchar       *res;
  GtkWidget   *button;
  int         y;
  int         i;

  i = 0;
  y = 0;
  fixed = gtk_fixed_new();
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), fixed, 500, 250);
  while (str_display[i])
  {
    sprintf(format_display, "<span face=\"Verdana\" foreground=\"#ffffff\" size=\"medium\"><b>%s</b></span>\n", str_display[i]);
    res = g_locale_to_utf8(format_display, -1, NULL, NULL, NULL);  //Convertion du texte avec les balises
    label=gtk_label_new(res); // Application de la convertion à notre label
    g_free(res); // Libération de la mémoire
    gtk_label_set_use_markup(GTK_LABEL(label), TRUE); // On dit que l'on utilise les balises pango
    gtk_fixed_put(GTK_FIXED(fixed), label, 0, y);
    y += 32 ;
    i++;
  }
  i = 0;
  strcpy(buff, str_display[i++]);
  while(str_display[i])
  {
    printf("str = %s\n", str_display[i]);
    strcat(buff, ";");
    strcat(buff, str_display[i]);
    i++;
  }
  printf("BUF = %s\n", buff);
  button = gtk_button_new_with_label("Do it !");
  gtk_widget_set_name(button, buff);
  g_signal_connect(button, "clicked", G_CALLBACK(substract_quantity), NULL);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), button, 1100, 500);
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

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), button_pos, 1175, 400);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), button_neg, 975, 400);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), data->entry, 1015, 400);

  g_signal_connect(button_pos, "clicked", G_CALLBACK(inc_entry), (void *)data);
  g_signal_connect(button_neg, "clicked", G_CALLBACK(dec_entry), (void *)data);
  g_signal_connect(data->entry, "activate", G_CALLBACK(nothing), NULL);

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

void substract_quantity(GtkButton *button)
{
  const gchar *res;

  res = gtk_widget_get_name(GTK_WIDGET(button));
  printf("RESULT = %s\n", res);
  return ;
}

void nothing()
{
  return ;
}
