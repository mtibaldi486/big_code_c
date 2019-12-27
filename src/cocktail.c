#include "../inc/cool.h"

void load_cocktail_page(GtkButton *button)
{
  GtkWidget   *backscreen;
  GtkWidget   *button2;
  const gchar *info;
  char          id[3];

  info = gtk_widget_get_name(GTK_WIDGET(button));
  mt_strccpy(id, (char *)info, ';');
  gtk_container_remove(GTK_CONTAINER(page->window), page->select_page);
  page->cocktail_page = GTK_WIDGET(gtk_builder_get_object(builder, "cocktail_page"));
  button2 = gtk_button_new_with_label ("Retour");
  g_signal_connect(button2, "clicked", G_CALLBACK(cocktail_to_select), NULL);
  gtk_container_add(GTK_CONTAINER(page->window), page->cocktail_page);
  backscreen = gtk_image_new_from_file("img/backscreen.png");
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), backscreen, 0, 0);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page),button2, 76, 41);
  display_name(info);
  display_mark(strchr((strrchr(info, ';') - 4), ';') + 1, id);
  display_picture(info);
  display_elem(info, 0);
  gtk_widget_show_all(page->window);

  return ;
}

char **format_ingredient(const gchar *info, int nb)
{
  char        **array_cocktail;
  char        **array_necessaire;
  char        **array_ingredient;
  char        **str_display;
  char        *new_quantity;
  int         len;
  int         i;

  i = 0;
  if (!(array_cocktail = ft_split(info, ';')))
    return (NULL);
  if (!(array_necessaire = get_necessaire(array_cocktail)))
    return (NULL);
  if (!(array_ingredient = get_ingredient(array_necessaire)))
    return (NULL);
  while (array_necessaire[i])
    i++;
  if (!(str_display = malloc(sizeof(char *) * (i + 1))))
    return (NULL);
  i = 0;
  while (array_necessaire[i])
  {
    len = 0;
    if (nb > 0)
      new_quantity = ajust_ingredient(array_necessaire[i], nb, array_cocktail[2]);
    else
      new_quantity = strchr(strchr(array_necessaire[i], ';') + 1, ';') + 1;
    len += strlen(new_quantity);
    if (len)
      len += 4;
    len += strlen(strchr(array_ingredient[i], ';') + 1);
    len -= strlen(strchr((strchr(array_ingredient[i], ';') + 1), ';'));
    if (!(str_display[i] = malloc(sizeof(char) * (len + 1))))
      return (NULL);
    strcpy(str_display[i], new_quantity);
    if (str_display[i][0])
      strcat(str_display[i], " de ");
    strncat(str_display[i], strchr(array_ingredient[i], ';') + 1, len - strlen(str_display[i]));
    str_display[i][len] = 0;
    i++;
  }
  str_display[i] = 0;

  free_res(array_cocktail, 30);
  free_res(array_necessaire, 30);
  free_res(array_ingredient, 30);
  return (str_display);
}

char  *ajust_ingredient(char *array_necessaire, int nb, char *ref)
{
  int          quantity_ref;
  int          nb_ref;
  double       new_quantity;
  char         buffer[20];
  char         res[40];
  char         *tmp;

  if (nb < 0)
    return (NULL);
  tmp = array_necessaire;
  sprintf(buffer, "%s", strchr(strchr(strchr(tmp, ';') + 1, ';') + 1, ' '));
  printf("buffer = %s\n", buffer);
  quantity_ref = atoi(strchr(strchr(tmp, ';') + 1, ';') + 1);
  nb_ref = atoi(ref);
  new_quantity = ((double)nb * (double)quantity_ref) / (double)nb_ref;
  if (new_quantity <= 0)
    new_quantity = 0;
  if (!strcmp(buffer, "(null)"))
  {
      tmp = "";
      return (tmp);
  }
  sprintf(res, "%s%s", ft_itoa(new_quantity), buffer);
  strcpy(tmp, res);
  write(1, "OK5\n", 4);
  if (!strcmp(buffer, "(null)"))
    tmp = "";
  return (tmp);
}

char  **get_necessaire(char **array_cocktail)
{
  MYSQL        *con = NULL;
  MYSQL_RES    *result = NULL;
  char         request[255];
  char         **res = NULL;

  if (!(con = connection_bdd(con)))
    return (NULL);
  sprintf(request, "SELECT * FROM necessaire WHERE id_cocktail = %s", array_cocktail[0]);
  printf("request = '%s'\n", request);
  if (mysql_query(con, request))
      return (NULL);

  if (!(result = mysql_store_result(con)))
    return (NULL);

  if (!(res = format_res(result)))
      return (NULL);

  mysql_free_result(result);
  mysql_close(con);
  return (res);
}

char    **get_ingredient(char **array_necessaire)
{
  MYSQL        *con = NULL;
  MYSQL_RES    *result = NULL;
  char         request[255];
  char         tmp[5];
  char         **res = NULL;
  int          i;

  i = 0;
  if (!(con = connection_bdd(con)))
    return (NULL);
  strcpy(request, "SELECT * FROM ingredient WHERE id IN (");
  while (array_necessaire[i])
  {
    mt_strccpy(tmp, strchr(array_necessaire[i], ';') + 1, ';');
    strcat(request, tmp);
    if (array_necessaire[i + 1])
      strcat(request, ", ");
    i++;
  }
  strcat(request, ")");
  if (mysql_query(con, request))
      return (NULL);

  if (!(result = mysql_store_result(con)))
    return (NULL);

  if (!(res = format_res(result)))
        return (NULL);

  mysql_free_result(result);
  mysql_close(con);
  return (res);
}

void  free_res(char **res, int len)
{
  int i;

  i = 0;
  while (i < len && res[i])
  {
    free(res[i]);
    res[i] = NULL;
    i++;
  }
  free(res[i]);
  res[i] = NULL;
  free(res);
  res = NULL;
  return ;
}
