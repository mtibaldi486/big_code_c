#include "../inc/cool.h"

char * get_id_ing(char * id_cocktail, MYSQL * con)
{
  char request[255];
  char ** res = NULL;
  int i = 0;
  int j = 0;
  MYSQL_RES * result = NULL;

  sprintf(request,"SELECT id_ingredient FROM necessaire WHERE id_cocktail = '%s'", id_cocktail);
  if(mysql_query(con, request))
    return NULL;
  if (!(result = mysql_store_result(con))){
    mysql_free_result(result);
    return NULL;
  }
  if (!(res = format_res(result))){
    mysql_free_result(result);
    return NULL;
  }

  while(res[i]){
      if(check_stock(res[i], con) != NULL){
        j++;
        i++;
      }
      else
        i++;
  }
  if(j != i){
    free_res(res, 1);
    mysql_free_result(result);
    return NULL;
  }
  else{
    free_res(res, 1);
    mysql_free_result(result);
    return id_cocktail;
  }
}

char * check_stock(char * id_ing, MYSQL * con)
{
  char request[255];
  MYSQL_RES * result = NULL;
  MYSQL_ROW row;

  sprintf(request,"SELECT id_stock FROM contenant WHERE id_ingredient = '%s'", id_ing);

  if(mysql_query(con, request))
    return NULL;
  if (!(result = mysql_store_result(con))){
    mysql_free_result(result);
    return NULL;
  }
  if((row = mysql_fetch_row(result)) == NULL){
    mysql_free_result(result);
    return NULL;
  }
  else{
    mysql_free_result(result);
    return row[0];
  }

}

int verify_cocktail(MYSQL *con, char * res)
{
  if(get_id_ing(res, con) == NULL)
    return 0;
  else
    return 1;
}

int   generate_cocktail_box(gchar  *info)
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

  del_generated_box();
  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "generated_cocktail"));
  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  //Creation du bouton pour voir la page du cocktail
  button = gtk_button_new_with_label("Voir");
  gtk_widget_set_name (button, info);

  //recuperation du nom de cocktail
  mt_strccpy(name, strchr(info, ';') + 1, ';');

  g_signal_connect(button, "clicked", G_CALLBACK(generate_to_cocktail), NULL);
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
  gtk_widget_show_all(page->window);
  return (0);
}

void del_generated_box()
{
  GtkListBoxRow *box;
  GtkListBox    *list;

  list = GTK_LIST_BOX(gtk_builder_get_object(builder, "generated_cocktail"));
  while ( (box = gtk_list_box_get_row_at_index(list, 0)))
    gtk_widget_destroy(GTK_WIDGET(box));

  return ;
}

void generate_cocktail()
{
  int i = 0;
  char **res_split = NULL;
  char **res = NULL;
  MYSQL * con;
  MYSQL_RES * result = NULL;

  con = NULL;
  if( (con = connection_bdd(con)) == NULL){
    finish_with_error(con);
    return ;
  }


  if (mysql_query(con, "SELECT * FROM cocktails"))
      return ;
  if (!(result = mysql_store_result(con))){
    mysql_free_result(result);
    return ;
  }
  if (!(res = format_res(result))){
      mysql_free_result(result);
      return ;
  }

  while(res[i]){
    res_split = ft_split(res[i], ';');
    if (verify_cocktail(con, res_split[0]) == 1){
      generate_cocktail_box(res[i]);
    }

    i++;
  }
  free_res(res, 100);
  free_res(res_split, 100);
  mysql_free_result(result);
  mysql_close(con);
  return ;
}
