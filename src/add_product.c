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

char * put_backslash(char * string)
{
  int i = 0;
  int length = 0;
  int pt;
  char * res;

  while(string[i]){
    if(string[i] == '\'')
      length ++;
    i++;
  }
  if(!(strchr(string, '\'')))
    return string;
  else {
    if(!(res = malloc(sizeof(char) * (strlen(string) + length + 1))))
      return NULL;
    pt = strchr(string, '\'') - string;
    strncpy(res, string, pt);
    res[pt] = '\0';
    strcat(strcat(res,"\\"),strchr(string, '\''));
    free(string);
    return res;
  }

}

char * get_date(char * date)
{
  int day, month, year;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  day = tm.tm_mday;
  month = tm.tm_mon + 1;
  year = tm.tm_year + 1900;
  sprintf(date,"%d-%d-%d", day, month, year);

  return date;

}
char * lowercase(char * string)
{
  int i = 0;

  while (string[i] != '\0'){
    if (string[i] >= 65 && string[i] <= 90){
      string[i] += 32;
    }
    i++;
  }
  return string;
}

char * delete_space(char * string)
{
    while(strchr(string, ' ')){
      strcpy(strchr(string, ' '), strchr(string, ' ') + 1);
    }
   return string;
}

char * uniform_unit(char * quantity)
{
  char * quantite;
  char * unity;
  char * pt;
  double nbquantity;
  char liquidunity[] = "cl";
  char solidunity[] = "g";

  lowercase(quantity);
  delete_space(quantity);
  quantite = strdup(quantity);
  nbquantity=strtod(quantite, &unity);

  if(strstr(unity, "ml") != NULL){
    nbquantity /= 10;
    sprintf(quantity, "%.2lf%s", nbquantity, liquidunity);
    free(quantite);
    return quantity;
  }
  else if(strstr(unity, "cl") != NULL){
    free(quantite);
    return quantity;
  }
  else if( (pt = strstr(unity, "l"))){
    if(*pt++ == ' ' || *pt++ == '\0'){
      nbquantity *= 100;
      sprintf(quantity, "%.2lf%s", nbquantity, liquidunity);
      free(quantite);
      return quantity;
    }
    else{
      free(quantite);
      return quantity;
    }
  }
  else if(strstr(unity, "kg") != NULL){
    nbquantity *= 1000;
    sprintf(quantity, "%.2lf%s", nbquantity, solidunity);
    free(quantite);
    return quantity;
  }
  else if (strstr(unity,"mg") != NULL){
    nbquantity /= 1000;
    sprintf(quantity, "%.2lf%s", nbquantity, solidunity);
    free(quantite);
    return quantity;
  }
  else{
    free(quantite);
    return quantity;
  }
}

char * total_quantity(char * quantity, int nb)
{
  char * quantite;
  char *unity;
  double nbquantite;

  quantite = strdup(quantity);
  nbquantite=strtod(quantite, &unity);

  if(*unity != 0){
    printf("%s\n", unity );
    nbquantite *= nb;
    sprintf(quantity, "%.2lf %s", nbquantite, unity);
  }
  else{
    nbquantite *= nb;
    sprintf(quantity, "%.2lf", nbquantite);
  }
  free(quantite);
  return quantity;
}



char * get_peremption(char * date, char * tmp)
{
  int final;
  int day, month, year;
  char dayc[3], monthc[3], yearc[5];
  char month30 []= "04,06,09,11";
  char month31 []= "01,03,05,07,08,10,12";
  sscanf(tmp, "%d", &final);

  sscanf(date,"%d-%d-%d", &day, &month, &year);
  if (final == 0){
    strcpy(date, "NULL");
    return date;
  }
  else {
  while (final != 0){
    day++;
    if(day > 28 && strcmp(monthc, "02")==0 && (year%4)!=0){
      month++;
      day = 01;
    }
    else if(day > 29 && strcmp(monthc, "02")==0 && (year%4) == 0){
      month++;
      day = 01;
    }
    if ((day > 30) && (strstr(month30, monthc) != NULL)){
      month++;
      day = 01;
    }
    if(day > 31 && (strstr(month31, monthc)!= NULL)){
      month++;
      day = 01;
    }
    if( month > 12){
      month = 01;
      year ++;
    }
    if (day < 10)
      sprintf(dayc, "0%d", day);
    else
      sprintf(dayc, "%d", day);
    if (month < 10)
      sprintf(monthc, "0%d", month);
    else
      sprintf(monthc, "%d", month);
    sprintf(yearc, "%d", year);
    final--;
  }
  sprintf(date, "%s-%s-%s", dayc, monthc, yearc);
  return date;
  }
}

char * final_quantity(char * quantity, char * quantity_bdd)
{
  double quantite;
  double quantite_bdd;
  char unit [10];

  sscanf(quantity, "%lf%s", &quantite, unit);
  sscanf(quantity_bdd, "%lf", &quantite_bdd);
  quantite += quantite_bdd;
  printf(" QUANTITE : %.2lf\n UNITE : %s\n",quantite, unit );
  sprintf(quantity, "%.2lf%s", quantite, unit);


  uniform_unit(quantity);

  return quantity;

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
  write(1, "OK1\n", 4);
  sprintf(request, "SELECT id, quantite FROM stock WHERE nom = '%s' AND marque = '%s' AND date_ajout = '%s'", tmp->name, tmp->brand, date );
  printf("%s\n", request);
  if (mysql_query(con, request)){
      finish_with_error(con);
      return ;
    }
  if (!(result = mysql_store_result(con))){
    finish_with_error(con);
    return ;
  }

  if ((row = mysql_fetch_row(result)) == NULL){
    sprintf(request, "INSERT INTO stock (nom, marque, quantite, date_ajout, date_expire) VALUES ('%s', '%s', '%s', '%s', '%s');", tmp->name, tmp->brand, tmp->quantity, date, res_per);
    if(mysql_query(con, request))
    {
      finish_with_error(con);
    }
    request_contenant(tmp, date, id_ing, con);
    return ;
  }
  else{
    final_quantity(tmp->quantity, row[1]);
    sprintf(request, "UPDATE stock SET quantite = '%s' WHERE id = '%s'", tmp->quantity,row[0]);
    if(mysql_query(con, request))
    {
      finish_with_error(con);
    }
    return ;
  }

  //free(date);
  //free(res_per);
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
      printf("PRODUIT TROUVE\n");
      request_stock(tmp, res_split[0], res_split[2], con);
    }
    i++;
  }

//  free_res(res);
  //free_res(res_split);
  return 0;
}
