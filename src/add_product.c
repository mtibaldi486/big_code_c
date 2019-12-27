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

  return 0;
}

void request_stock(t_prod *tmp, char * id_ing, char * peremption, MYSQL * con)
{
  char * date;
  char * res_per;
  char request[200];
  MYSQL_RES * result = NULL;
  MYSQL_ROW row;

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
  sprintf(request, "SELECT id, quantite FROM stock WHERE nom = '%s' AND marque = '%s' AND date_ajout = '%s'", tmp->name, tmp->brand, date );
  if (mysql_query(con, request)){
      finish_with_error(con);
      free(res_per);
      free(date);
      return ;
    }
  if (!(result = mysql_store_result(con))){
    finish_with_error(con);
    free(res_per);
    free(date);
    return ;
  }

  if ((row = mysql_fetch_row(result)) == NULL){
    sprintf(request, "INSERT INTO stock (nom, marque, quantite, date_ajout, date_expire) VALUES ('%s', '%s', '%s', '%s', '%s');", tmp->name, tmp->brand, tmp->quantity, date, res_per);
    if(mysql_query(con, request))
    {
      finish_with_error(con);
    }
    request_contenant(tmp, date, id_ing, con);
    mysql_free_result(result);
    free(res_per);
    free(date);
    return ;
  }
  else{
    final_quantity(tmp->quantity, row[1]);
    sprintf(request, "UPDATE stock SET quantite = '%s' WHERE id = '%s'", tmp->quantity,row[0]);
    if(mysql_query(con, request))
    {
      finish_with_error(con);
    }
    mysql_free_result(result);
    free(res_per);
    free(date);
    return ;
  }
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
    i++;
  }

  return 0;
}
