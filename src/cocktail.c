#include "../inc/cool.h"

void load_cocktail_page(GtkButton *button)
{
  GtkWidget   *backscreen;
  GtkWidget   *button2;
  const gchar *info;

  info = gtk_widget_get_name(GTK_WIDGET(button));
  gtk_container_remove(GTK_CONTAINER(page->window), page->select_page);
  page->cocktail_page = GTK_WIDGET(gtk_builder_get_object(builder, "cocktail_page"));
  button2 = gtk_button_new_with_label ("Retour");
  g_signal_connect(button2, "clicked", G_CALLBACK(cocktail_to_select), NULL);
  gtk_container_add(GTK_CONTAINER(page->window), page->cocktail_page);
  backscreen = gtk_image_new_from_file("img/backscreen.png");
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), backscreen, 0, 0);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page),button2, 76, 41);
  display_elem(info);
  gtk_widget_show_all(page->window);

  return ;
}

void display_elem(const gchar *info)
{
  GtkWidget   *pic_cocktail;
  GtkWidget   *pic_recipe;
  char        **array_cocktail;
  char        **array_quantite;
  char        **array_ingredient;
  char        str_display[15][255];
  int         i;


  i = 0;
  if (!(array_cocktail = ft_split(info, ';')))
    return ;
  while(array_cocktail[i])
    {
      printf("icocktail= '%s'\n", array_cocktail[i]);
      i++;
    }
  if (!(array_quantite = get_quantite(array_cocktail)))
    return ;
  i = 0;
  while(array_quantite[i])
  {
    printf("quantite = '%s'\n", array_quantite[i]);
    i++;
  }
  if (!(array_ingredient = get_ingredient(array_quantite)))
    return ;
  i = 0;
  while(array_ingredient[i])
  {
    printf("ingredient = '%s'\n", array_ingredient[i]);
    i++;
  }
  i = 0;
  while (array_quantite[i])
  {
    strcpy(str_display[i], strchr(strchr(array_quantite[i], ';') + 1, ';') + 1);
    if (str_display[i][0])
      strcat(str_display[i], " de ");
    strcat(str_display[i], strchr(array_ingredient[i], ';') + 1);
    str_display[i][strchr(str_display[i], ';') - str_display[i]] = 0;
    printf("display2 = '%s'\n", str_display[i]);
    i++;
  }

  pic_cocktail = gtk_image_new_from_file(array_cocktail[3] + 3);
  pic_recipe = gtk_image_new_from_file(array_cocktail[4] + 3);

  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_cocktail, 980, 100);
  gtk_fixed_put(GTK_FIXED(page->cocktail_page), pic_recipe, 135, 200);

  free_res(array_cocktail, 30);
  free_res(array_quantite, 30);
  free_res(array_ingredient, 30);
}

char  **get_quantite(char **array_cocktail)
{
  MYSQL        *con = NULL;
  MYSQL_RES    *result = NULL;
  MYSQL_ROW    row;
  char         request[255];
  char         **res = NULL;
  int          num_fields;
  int          nb_row;
  int          i = 0;

  if (!(con = connection_bdd(con)))
    return (NULL);
  strcpy(request, "SELECT * FROM necessaire WHERE id_cocktail = ");
  strcat(request, array_cocktail[0]);
  printf("request = '%s'\n", request);
  if (mysql_query(con, request))
  {
      finish_with_error(con);
      return (NULL);
  }

  if (!(result = mysql_store_result(con)))
  {
    finish_with_error(con);
    return (NULL);
  }

  nb_row = mysql_num_rows(result);
  num_fields = mysql_num_fields(result);
  if (!(res = malloc(sizeof(char **) * (nb_row + 1))))
    return (NULL);
  while ((row = mysql_fetch_row(result)))
  {
      res[i] = join_row(row, num_fields);
      /*if (!(res[i] = join_row(row, num_fields)))
      {
        free_res(res, i);
        return (NULL);
      }*/
      i++;
  }
  res[i] = NULL;
  mysql_free_result(result);
  mysql_close(con);
  return (res);
}

char    **get_ingredient(char **array_quantite)
{
  MYSQL        *con = NULL;
  MYSQL_RES    *result = NULL;
  MYSQL_ROW    row;
  char         request[255];
  char         tmp[5];
  char         **res = NULL;
  int          num_fields;
  int          nb_row;
  int          i = 0;

  if (!(con = connection_bdd(con)))
    return (NULL);
  strcpy(request, "SELECT * FROM ingredient WHERE id IN (");
  while (array_quantite[i])
  {
    mt_strccpy(tmp, strchr(array_quantite[i], ';') + 1, ';');
    strcat(request, tmp);
    if (array_quantite[i + 1])
      strcat(request, ", ");
    i++;
  }
  strcat(request, ")");
  if (mysql_query(con, request))
  {
      finish_with_error(con);
      return (NULL);
  }

  if (!(result = mysql_store_result(con)))
  {
    finish_with_error(con);
    return (NULL);
  }

  nb_row = mysql_num_rows(result);
  num_fields = mysql_num_fields(result);
  if (!(res = malloc(sizeof(char **) * (nb_row + 1))))
    return (NULL);
  i = 0;
  while ((row = mysql_fetch_row(result)))
  {
      if (!(res[i] = join_row(row, num_fields)))
      {
        free_res(res, i);
        return (NULL);
      }
      i++;
  }
  res[i] = NULL;
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
