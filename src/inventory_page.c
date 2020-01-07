#include "../inc/cool.h"

char * verify_nature(MYSQL * con)
{
  int i = 0;
  int j;
  char **res = NULL;
  char **res_split;
  MYSQL_RES * result = NULL;
  char alcohol[11][255]= { {"Vin"} , {"Aperol"} , {"Vodka"} , {"Liqueur"} , {"Curacao"} , {"Triple"} , {"Rhum"} , {"Tequila"} , {"Champagne"} , {"Gin"} , {"Whisky"} };
  char tmp[150];

  if (mysql_query(con, "SELECT * FROM stock"))
      return NULL;
  if (!(result = mysql_store_result(con)))
    return NULL;
  if (!(res = format_res(result)))
      return NULL;


  while(res[i]){
    res_split = ft_split(res[i], ';');
    j = 0;
    strcpy(tmp, res_split[1]);
    while( j < 11 ){
      if( ( strstr( lowercase(tmp), lowercase(alcohol[j]) ) ) != NULL ) {
        add_inventory_box(res_split, 1);
        break;
      }
      j++;
    }
    if( j == 11)
      add_inventory_box(res_split, 0);
    i++;
  }

  free_res(res, 100);
  free_res(res_split, 100);
  mysql_free_result(result);
  return NULL;
}

void del_inventory_page()
{
  GtkListBoxRow *box;
  GtkListBox    *list;

  list = GTK_LIST_BOX(gtk_builder_get_object(builder, "ressource_alcool"));
  while ( (box = gtk_list_box_get_row_at_index(list, 0)))
    gtk_widget_destroy(GTK_WIDGET(box));

  list = GTK_LIST_BOX(gtk_builder_get_object(builder, "ressource_divers"));
  while ( (box = gtk_list_box_get_row_at_index(list, 0)))
    gtk_widget_destroy(GTK_WIDGET(box));
  return ;
}

int add_inventory_box(char **result, int type)
{
  GtkListBox    *box;
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  GtkWidget     *lab_name;
  GtkWidget     *lab_brand;
  GtkWidget     *lab_quantity;
  GtkWidget     *lab_date;
  GtkWidget     *lab_expiry;
  GtkWidget     *lab_delim;

  lab_name = gtk_label_new(result[1]);
  lab_brand = gtk_label_new(result[2]);
  lab_quantity = gtk_label_new(result[3]);
  lab_date = gtk_label_new(result[4]);
  lab_expiry = gtk_label_new(result[5]);
  lab_delim = gtk_label_new("     ___________________     ");

  if( type == 1){
    box = GTK_LIST_BOX(gtk_builder_get_object(builder, "ressource_alcool"));
    new_box = gtk_list_box_row_new();
    fixed = gtk_fixed_new();

    gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
    gtk_fixed_put(GTK_FIXED(fixed), lab_brand, 10, 35);
    gtk_fixed_put(GTK_FIXED(fixed), lab_date, 10, 60);
    gtk_fixed_put(GTK_FIXED(fixed), lab_expiry, 200, 60);
    gtk_fixed_put(GTK_FIXED(fixed), lab_quantity, 125, 80);
    gtk_fixed_put(GTK_FIXED(fixed), lab_delim, 65, 85);

    gtk_container_add(GTK_CONTAINER(new_box), fixed);

    gtk_list_box_insert(box, new_box, 0);
  }
  else{
    box = GTK_LIST_BOX(gtk_builder_get_object(builder, "ressource_divers"));
    new_box = gtk_list_box_row_new();
    fixed = gtk_fixed_new();

    gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
    gtk_fixed_put(GTK_FIXED(fixed), lab_brand, 10, 35);
    gtk_fixed_put(GTK_FIXED(fixed), lab_date, 10, 60);
    gtk_fixed_put(GTK_FIXED(fixed), lab_expiry, 200, 60);
    gtk_fixed_put(GTK_FIXED(fixed), lab_quantity, 125, 80);
    gtk_fixed_put(GTK_FIXED(fixed), lab_delim, 65, 85);

    gtk_container_add(GTK_CONTAINER(new_box), fixed);

    gtk_list_box_insert(box, new_box, 0);
  }

  gtk_widget_show_all(page->window);

  return (0);
}

int select_ingredient()
{

  MYSQL * con;

  con = NULL;
  if( (con = connection_bdd(con)) == NULL){
    finish_with_error(con);
    return 0;
  }
  del_inventory_page();
  verify_nature(con);

  mysql_close(con);
  return 0;

}
