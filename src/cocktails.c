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
  int           num_fields;
  MYSQL_ROW     row;

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
      add_cocktail_box(row);
  }
  mysql_free_result(result);
  mysql_close(con);
  exit(0);
}

int   add_cocktail_box(MYSQL_ROW row)
{
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  GtkListBox    *box;
  char          new_name[200];
  GtkWidget     *lab_nb;
  GtkWidget     *lab_name;
  GtkWidget     *lab_quantity;


  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_product_box"));
  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  strcpy(new_name, product->brand);
  strcat(strcat(new_name, " : "  ), product->name);
  lab_nb = gtk_label_new("x 0");
  lab_name = gtk_label_new(new_name);
  lab_quantity = gtk_label_new(product->quantity);

  gtk_fixed_put(GTK_FIXED(fixed), lab_nb, 450, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_quantity, 10, 50);

  gtk_container_add(GTK_CONTAINER(new_box), fixed);

  gtk_list_box_insert(box, new_box, 0);
  return (0);
}
