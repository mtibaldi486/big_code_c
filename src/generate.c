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
    mysql_free_result(result);
    return NULL;
  }
  else{
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

int generate_cocktail()
{
  int i = 0;
  char **res = NULL;
  MYSQL * con;
  MYSQL_RES * result = NULL;

  con = NULL;
  if( (con = connection_bdd(con)) == NULL){
    finish_with_error(con);
    return 0;
  }


  if (mysql_query(con, "SELECT id FROM cocktails"))
      return 0;
  if (!(result = mysql_store_result(con)))
    return 0;
  if (!(res = format_res(result)))
      return 0;

  while(res[i]){
    printf("coktail : %s\n", res[i]);
    if(get_id_ing(res[i], con) == NULL)
      printf("non dispo\n");
    else
      printf("dispo\n");
    i++;
  }
  mysql_free_result(result);
  return 0;
}
