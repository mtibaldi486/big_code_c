#include "../inc/cool.h"

int get_contenant(char * id, char * quantity_needed)
{
  char request[255];
  char **res = NULL;
  char * unity;
  double quantity;
  MYSQL * con;
  MYSQL_RES * result = NULL;

  con = NULL;
  connection_bdd(con);

  quantity = strtod(quantity_needed, &unity);

  sprintf(request, "SELECT * FROM contenant WHERE id_ingredient = '%s'", id);

  if (mysql_query(con, request))
    return 0;
  if (!(result = mysql_store_result(con)))
    return 0;
  if (!(res = format_res(result)))
    return 0;

  if(use_quantity(res, con, quantity, unity) == 1){
    mysql_free_result(result);
    free_res(res, 1);
    mysql_close(con);
    return 0;
  }

}

int use_quantity(char ** res, MYSQL * con, double quantity_needed, char * unity)
{
  int i = 0;
  int tmp;
  char request[255];
  char ** res_split;
  MYSQL_RES * result;
  MYSQL_ROW row;

  while(quantity_needed > 0)
  {
    res_split = ft_split(res[i], ';');
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
    quantity_needed -= row[1];
    if(quantity_needed > 0){
      delete_stock(row[0], con);
      i++;
    }
    else if (quantity_needed < 0){
      update_stock(row[0], con, quantity_needed, unity);
      mysql_free_result(result);
      free_res(res_split, 3);
      return 1;
    }
    else if (quantity_needed == 0){
      update_stock(row[0], con, quantity_needed, unity);
      mysql_free_result(result);
      free_res(res_split, 3);
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

void update_stock(char * id, MYSQL * con, double new_quantity, unity)
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
