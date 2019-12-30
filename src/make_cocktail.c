#include "../inc/cool.h"

int get_contenant(char * id, int quantity_needed)
{
  char request[255];
  char **res = NULL;
  MYSQL * con;
  MYSQL_RES * result = NULL;

  con = NULL;
  connection_bdd(con);
  sprintf(request, "SELECT * FROM contenant WHERE id_ingredient = '%s'", id);

  if (mysql_query(con, request))
    return 0;
  if (!(result = mysql_store_result(con)))
    return 0;
  if (!(res = format_res(result)))
    return 0;

  use_quantity(res, con, quantity_needed);

}

int use_quantity(char ** res, MYSQL * con, int quantity_needed)
{
  int i = 0;
  int tmp;
  char request[255];
  char ** res_split;
  MYSQL_ROW row;

  while(quantity_needed > 0)
  {
    res_split = ft_split(res[i], ';');
    sprintf(request, "SELECT id,quantite FROM stock WHERE id = '%s'", res_split[0]);
    if (mysql_query(con, request))
      return 0;
    if (!(result = mysql_store_result(con)))
      return 0;
    if(!(row = mysql_fetch_row(result)))
      return 0;
    quantity_needed -= row[1];
    if(quantity_needed > 0){
      delete_stock(row[0], con);
      i++;
    }
    else if (quantity_needed < 0){
      update_stock(row[0], con, quantity_needed);
      return 1;
    }
    else if (quantity_needed == 0){
      update_stock(row[0], con, quantity_needed);
      return 1;
    }
  }
}

void delete_stock(char * id, MYSQL * con)
{
  char request[255];

  sprintf(request, "DELETE FROM contenant WHERE id_stock = '%s'", id);
  if (mysql_query(con, request))
    return ;
  sprinf(request, "DELETE FROM stock WHERE id = '%s'", id);
  if (mysql_query(con, request))
    return ;

}

void update_stock(char * id, MYSQL * con, int new_quantity)
{
  char request[255];

  if(new_quantity != 0)
    new_quantity = fabs(new_quantity);
  sprintf(request, "UPDATE stock SET quantite ='%s' WHERE id ='%s'", new_quantity, id);
  if (mysql_query(con, request))
    return ;

  return ;
}
