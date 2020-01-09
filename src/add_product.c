#include "../inc/cool.h"

int add_product()
{
  if(!begin)
    return 0;

  t_prod *tmp = begin;

  while(tmp)
  {
    insert_bdd(tmp);
    tmp = tmp->next;
  }

  empty_list();
  return 0;
}

int insert_bdd(t_prod *tmp)
{
  int i = 0;
  char **res = NULL;
  char **res_split = NULL;
  MYSQL * con;
  MYSQL_RES * result = NULL;

  con = NULL;
  if( (con = connection_bdd(con)) == NULL){
    finish_with_error(con);
    return 0;
  }


  if (mysql_query(con, "SELECT * FROM ingredient"))
      return 0;
  if (!(result = mysql_store_result(con)))
    return 0;
  if (!(res = format_res(result)))
      return 0;

  while(res[i]){
    res_split = ft_split(res[i], ';');
    if((strstr(lowercase(tmp->name), lowercase(res_split[1])))){
      request_stock(tmp, res_split[0], res_split[2], con);
    }
    else if((strstr( lowercase(res_split[1]), lowercase(tmp->name)))){
      request_stock(tmp, res_split[0], res_split[2], con);
    }
    i++;
  }

  free_res(res, 500);
  free_res(res_split, 15);
  mysql_free_result(result);
  mysql_close(con);
  return 0;
}

int check_date_per (t_prod * tmp, MYSQL * con)
{
  char request[200];
  MYSQL_RES *result = NULL;
  MYSQL_ROW row;

  sprintf(request, "SELECT id, date_expire, quantite FROM stock WHERE nom = '%s' AND marque = '%s'", tmp->name, tmp->brand);
  if (mysql_query(con, request)){
      finish_with_error(con);
      mysql_free_result(result);
      return 0;
  }
  if (!(result = mysql_store_result(con))){
    finish_with_error(con);
    mysql_free_result(result);
    return 0;
  }
  if(!(row = mysql_fetch_row(result))){
    mysql_free_result(result);
    return 0;
  }


  if( strstr(row[1], "NULL") ){
    final_quantity(tmp->quantity, row[2]);
    sprintf(request, "UPDATE stock SET quantite = '%s' WHERE id = '%s'", tmp->quantity, row[0]);
    mysql_query(con, request);
    mysql_free_result(result);
    return 1;
  }
    else{
      mysql_free_result(result);
      return 0;
  }
}

void make_query(t_prod *tmp, char * date, char * per, char * id_ing, MYSQL *con)
{
  char request[200];
  MYSQL_ROW row;
  MYSQL_RES *result;

  sprintf(request, "SELECT id, quantite FROM stock WHERE nom = '%s' AND marque = '%s' AND date_ajout = '%s'", tmp->name, tmp->brand, date );
  if (mysql_query(con, request)){
      finish_with_error(con);
      free(per);
      free(date);
      return ;
    }
  if (!(result = mysql_store_result(con))){
    finish_with_error(con);
    free_add_product(result, per, date);
    return ;
  }

  if (!(row = mysql_fetch_row(result))){
    sprintf(request, "INSERT INTO stock (nom, marque, quantite, date_ajout, date_expire) VALUES ('%s', '%s', '%s', '%s', '%s');", tmp->name, tmp->brand, tmp->quantity, date, per);
    if(mysql_query(con, request))
      finish_with_error(con);
    request_contenant(tmp, date, id_ing, con);
    free_add_product(result, per, date);
    return ;
  }
  else
  {
    final_quantity(tmp->quantity, row[1]);
    sprintf(request, "UPDATE stock SET quantite = '%s' WHERE id = '%s'", tmp->quantity,row[0]);
    if(mysql_query(con, request))
      finish_with_error(con);
    free_add_product(result, per, date);
    return ;
  }

}
void request_stock(t_prod *tmp, char * id_ing, char * peremption, MYSQL * con)
{
  char * date;
  char * res_per;

  date = malloc(sizeof(char) * 15);
  res_per = malloc(sizeof(char) * 15);
  get_date(date);
  if( peremption[0] == '\0')
    res_per[0] = '\0';
  else
    get_peremption(strcpy(res_per, date), peremption);

  uniform_unit(tmp->quantity);
  total_quantity(tmp->quantity, tmp->nb);
  tmp->name = put_backslash(tmp->name);
  tmp->brand = put_backslash(tmp->brand);

  if( check_date_per( tmp, con ) == 0){
    make_query(tmp, date, res_per, id_ing, con);
  }
  free(date);
  free(res_per);
  return ;
}

void request_contenant(t_prod *tmp, char * date, char * id_ing, MYSQL * con)
{
  MYSQL_RES * result = NULL;
  MYSQL_ROW row;
  char id_stock[10];
  char request[200];

  sprintf(request, "SELECT id FROM stock WHERE nom = '%s' AND marque = '%s' AND date_ajout = '%s' ;", tmp->name, tmp->brand, date);
  if(mysql_query(con, request))
  {
    finish_with_error(con);
    return ;
  }
  result = mysql_store_result(con);
  if(result == NULL){
    finish_with_error(con);
    return ;
  }
  row = mysql_fetch_row(result);
  strcpy(id_stock, row[0]);
  mysql_free_result(result);
  sprintf(request, "INSERT INTO contenant ( id_stock, id_ingredient) VALUES ('%s', '%s');", id_stock, id_ing);
  if(mysql_query(con, request))
  {
    finish_with_error(con);
    return ;
  }
  return ;
}

void free_add_product(MYSQL_RES *result, char *res_per, char *date)
{
  if (result)
    mysql_free_result(result);
  free(res_per);
  free(date);
  return ;
}
