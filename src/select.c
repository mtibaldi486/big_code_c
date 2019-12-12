#include "../inc/cool.h"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int load_lst_cocktails()
{
  MYSQL         *con;
  MYSQL_RES     *result = NULL;
  MYSQL_ROW     row;
  int           num_fields;
  int           i;
  t_cocktail    *lst_cocktail;

  if (begin_cocktail)
    return (0);
  con = mysql_init(NULL);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "root",
          "aperocool", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "SELECT * FROM cocktails"))
  {
      finish_with_error(con);
  }

  result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  num_fields = mysql_num_fields(result);

  while ((row = mysql_fetch_row(result)))
  {
      if (!(lst_cocktail = lstnew_cocktail()))
        return (0);
      strcpy(lst_cocktail->info, row[0]);
      strcat(lst_cocktail->info, ";");
      i = 1;
      for(i = 1; i < num_fields; i++)
      {
          strcat(lst_cocktail->info, row[i]);
          strcat(lst_cocktail->info, ";");
      }
      lst_cocktail->info[strlen(lst_cocktail->info) - 1] = 0;
      add_cocktail_box(lst_cocktail);
      lstadd_back_cocktail(&begin_cocktail, lst_cocktail);
  }
  mysql_free_result(result);
  mysql_close(con);
  return (0);
}

int   add_cocktail_box(t_cocktail *cocktail)
{
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  GtkListBox    *box;
  gchar         name[200];
  char          mark[30];
  char          *tmp;
  GtkWidget     *lab_name;
  GtkWidget     *lab_mark;
  GtkWidget     *lab_delim;
  GtkWidget     *button;


  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_cocktails"));
  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  //Creation du bouton pour voir la page du cocktails
  button = gtk_button_new_with_label("Voir");

  //recuperation de nom de cocktail
  strcpy(name, strchr(cocktail->info, ';') + 1);
  tmp = name;
  while (!(isdigit(*(strchr(tmp, ';') + 1))))
  {
    tmp = strchr(tmp, ';') + 1;
  }
  tmp = strchr(tmp, ';');
  name[tmp - name] = '\0';

  g_signal_connect(button, "clicked", G_CALLBACK (load_cocktail_page), cocktail->info);
  //Formatage de la note pour affichage
  strcpy(mark, "Note : ");
  strcat(mark, strchr((strrchr(cocktail->info, ';') - 4), ';') + 1);
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
