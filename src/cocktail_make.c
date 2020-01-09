#include "../inc/cool.h"

void substract_quantity(GtkButton *button)
{
  const gchar *res;
  char ** res_split;
  int i = 0;

  res = gtk_widget_get_name(GTK_WIDGET(button));
  res_split = ft_split(res, ';');
  while(res_split[i]){
    printf("ON REVIENT\n");
    if (!(find_ingredient(res_split[i])))
      return ;
    if( (find_ingredient(res_split[i])) == NULL )
      return ;
    printf("RESULT SPLIT : %s\n", res_split[i]);
    get_contenant(res_split[i]);
    i++;
  }
  return ;
}

int get_contenant(char * ing)
{
  char request[255];
  char **res = NULL;
  char ** ing_split;
  char * unity;
  double quantity;
  MYSQL * con;
  MYSQL_RES * result = NULL;

  ing_split = ft_split(ing, ';');
  con = NULL;
  con = connection_bdd(con);
  quantity = strtod(ing_split[0], &unity);

  printf("%s\n", ing_split[1]);

  sprintf(request, "SELECT * FROM contenant WHERE id_ingredient = '%s'", ing_split[1]);

  if (mysql_query(con, request))
    return 0;
  if (!(result = mysql_store_result(con)))
    return 0;
  if (!(res = format_res(result)))
    return 0;

  printf("RES : %s\n", res[0]);

  if( res[0] == NULL)
    return 0;

  if(use_quantity(res, con, quantity) == 1){
    printf("ON A LE PRODUIT\n");
    /*free_res(res, 1);
    free_res(ing_split, 2);*/
    mysql_free_result(result);
    mysql_close(con);
    return 0;
  }
  else{
  printf("PLUS DE PRODUIT\n");
  /*free_res(res, 1);
  free_res(ing_split, 2);*/
  mysql_free_result(result);
  mysql_close(con);
  return 0;
  }
}

char * find_ingredient(char * string)
{
  MYSQL *con = NULL;
  MYSQL_RES *result;
  int i = 0;
  char ** res;
  char ** res_split;
  char    buff[20];

  strcpy(buff, string);
  con = connection_bdd(con);
  if (mysql_query(con, "SELECT id,nom FROM ingredient"))
    return NULL;
  if (!(result = mysql_store_result(con)))
    return NULL;
  if (!(res = format_res(result)))
    return NULL;
  while(res[i]){
    res_split = ft_split(res[i], ';');
    if(strstr(string, res_split[1]) != NULL){
      sprintf(string, "%s;%s", buff, res_split[0]);
      free_res(res, 50);
      free_res(res_split, 2);
      mysql_free_result(result);
      mysql_close(con);
      printf("%s\n", string);
      return string;
    }
    i++;
  }
  return NULL;
}

int use_quantity(char ** res, MYSQL * con, double quantity_needed)
{
  int i = 0;
  double tmp;
  char * unity;
  char request[255];
  char ** res_split;
  MYSQL_RES * result;
  MYSQL_ROW row;

  while(quantity_needed > 0)
  {
    if(!(res_split = ft_split(res[i], ';')))
      return 0;
    sprintf(request, "SELECT id,quantite FROM stock WHERE id = '%s'", res_split[0]);
    if (mysql_query(con, request))
      return 0;
    if (!(result = mysql_store_result(con))){
      mysql_free_result(result);
      return 0;
    }
    if(!(row = mysql_fetch_row(result))){
      mysql_free_result(result);
      return 0;
    }
    tmp = strtod(row[1], &unity);
    quantity_needed -= tmp;
    if(quantity_needed > 0){
      delete_stock(row[0], con);
      i++;
    }
    else if (quantity_needed < 0){
      update_stock(row[0], con, quantity_needed, unity);
      free_res(res_split, 3);
      mysql_free_result(result);
      return 1;
    }
    else if (quantity_needed == 0){
      update_stock(row[0], con, quantity_needed, unity);
      free_res(res_split, 3);
      mysql_free_result(result);
      return 1;
    }
  }
  return 1;
}

void update_stock(char * id, MYSQL * con, double new_quantity, char * unity)
{
  char request[255];
  char quantity[100];


  if(new_quantity != 0)
    new_quantity = fabs(new_quantity);

  sprintf(quantity, "%.2lf%s", new_quantity, unity);
  sprintf(request, "UPDATE stock SET quantite ='%s' WHERE id ='%s'", quantity, id);
  if (mysql_query(con, request))
    return ;

  return ;
}
