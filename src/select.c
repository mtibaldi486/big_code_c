#include "../inc/cool.h"

int load_lst_cocktails()
{
  MYSQL         *con = NULL;
  MYSQL_RES     *result = NULL;
  MYSQL_ROW     row;
  int           num_fields;
  gchar         *info;
  static int    i;

  if (i)
    return (0);
  i++;
  if (!(con = connection_bdd(con)))
    return (0);
  if (mysql_query(con, "SELECT * FROM cocktails"))
  {
      finish_with_error(con);
      return (0);
  }

  if (!(result = mysql_store_result(con)))
  {
    finish_with_error(con);
    return (0);
  }
  num_fields = mysql_num_fields(result);
  while ((row = mysql_fetch_row(result)))
  {
      info = join_row(row, num_fields);
      add_cocktail_box(info);
  }
  free(info);
  mysql_free_result(result);
  mysql_close(con);
  return (0);
}

int   add_cocktail_box(gchar  *info)
{
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  GtkWidget     *lab_name;
  GtkWidget     *lab_mark;
  GtkWidget     *lab_delim;
  GtkWidget     *button;
  GtkListBox    *box;
  gchar         name[200];
  char          mark[30];

  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_cocktails"));
  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  //Creation du bouton pour voir la page du cocktails
  button = gtk_button_new_with_label("Voir");
  gtk_widget_set_name (button, info);

  //recuperation de nom de cocktail
  mt_strccpy(name, strchr(info, ';') + 1, ';');

  g_signal_connect(button, "clicked", G_CALLBACK (load_cocktail_page), info);
  //Formatage de la note pour affichage
  strcpy(mark, "Note : ");
  strcat(mark, strchr((strrchr(info, ';') - 4), ';') + 1);
  strcat(mark, "/5");

  lab_name = gtk_label_new(name);
  lab_mark = gtk_label_new(mark);
  lab_delim = gtk_label_new("     ___________________     ");

  gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_mark, 10, 50);
  gtk_fixed_put(GTK_FIXED(fixed), lab_delim, 250, 75);
  gtk_fixed_put(GTK_FIXED(fixed), button, 450, 40);

  gtk_container_add(GTK_CONTAINER(new_box), fixed);

  gtk_list_box_insert(box, new_box, 0);
  return (0);
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  return ;
}
