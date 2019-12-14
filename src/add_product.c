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

char * uniform_quantity(char * quantity){
  char quantite[10];
  double nbquantite;
  char unity[] = "cl";
  char unity2[] ="g";
  int pt;
  int i = 0;

  while (quantity[i] != '\0'){
    if (quantity[i] >= 65 && quantity[i] <= 90){
      quantity[i] += 32;
    }
    i++;
  }
  while (strchr(quantity, ' ') != NULL){
    strcpy(strchr(quantity, ' '), strchr(quantity, ' ') + 1);
  }
  if( strstr(quantity, "ml") != NULL){
    pt = strstr(quantity, "ml") - quantity;
    strncpy(quantite, quantity, pt);
    quantite[pt] = '\0';
    sscanf(quantite, "%lf", &nbquantite);
    nbquantite /= 10;
    sprintf(quantity, "%.2lf %s", nbquantite, unity);
    return quantity;
  }
  else if( strstr(quantity, "cl") != NULL){
    return quantity;
  }
  else if( strstr(quantity, "l") != NULL){
    pt = strstr(quantity, "l") - quantity;
    strncpy(quantite, quantity, pt);
    quantite[pt] = '\0';
    sscanf(quantite, "%lf", &nbquantite);
    nbquantite *= 100;
    sprintf(quantity, "%.2lf %s", nbquantite, unity);
    return quantity;
  }
  else if(strstr(quantity, "kg") != NULL){
    pt = strstr(quantity, "kg") - quantity;
    strncpy(quantite, quantity, pt);
    quantite[pt] = '\0';
    sscanf(quantite, "%lf", &nbquantite);
    nbquantite *= 1000;
    sprintf(quantity, "%.2lf %s", nbquantite, unity2);
    return quantity;
  }
  else if(strstr(quantity, "mg") != NULL){
    pt = strstr(quantity, "mg") - quantity;
    strncpy(quantite, quantity, pt);
    quantite[pt] = '\0';
    sscanf(quantite, "%lf", &nbquantite);
    nbquantite /= 1000;
    sprintf(quantity, "%.2lf %s", nbquantite, unity2);
    return quantity;
  }
  else
    return quantity;
}

char * total_quantity(char * quantity, int nb){
  char quantite[10];
  char unity[5];
  double nbquantite;
  int pt;

  if(strstr(quantity, "cl") != NULL){
    pt = strstr(quantity, "cl") - quantity;
    strncpy(quantite, quantity, pt);
    quantite[pt] = '\0';
    strcpy(unity, strstr(quantity, "cl"));
    sscanf(quantite, "%lf", &nbquantite);
    nbquantite *= nb;
    sprintf(quantity, "%.2lf %s", nbquantite, unity);
    return quantity;
  }
  else if(strstr(quantity, "g") != NULL){
    pt = strstr(quantity, "g") - quantity;
    strncpy(quantite, quantity, pt);
    quantite[pt] = '\0';
    strcpy(unity, strstr(quantity, "g"));
    sscanf(quantite, "%lf", &nbquantite);
    nbquantite *= nb;
    sprintf(quantity, "%.2lf %s", nbquantite, unity);
    return quantity;

  }
  else{
    sscanf(quantity, "%lf", &nbquantite);
    nbquantite *= nb;
    sprintf(quantity, "%.2lf", nbquantite);
    return quantity;
  }
}

char *get_date(char * date)
{
  int day;
  int month;
  int year;
  struct tm tm;

  time_t t = time(NULL);
  tm = *localtime(&t);

  day = tm.tm_mday;
  month = tm.tm_mon + 1;
  year = tm.tm_year + 1900;
  sprintf(date,"%d-%d-%d", day, month, year);
  return date;
}

char * get_peremption(char * date, char * tmp){
  int final;
  int day, month, year;
  char dayc[3], monthc[3], yearc[5];
  char month30 []= "04,06,09,11";
  char month31 []= "01,03,05,07,08,10,12";
  sscanf(tmp, "%d", &final);

  sscanf(date,"%d-%d-%d", &day, &month, &year);
  while (final != 0){
    day++;
    if(day > 28 && strcmp(monthc, "02")==0 && (year%4)!=0){
      month++;
      day = 01;
    }
    else if(day > 29 && strcmp(monthc, "02")==0 && (year%4) ==0){
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

int insert_bdd(t_prod *tmp){
//////////////////////Convertion des données////////////////////////////
  char * date;
  char * peremption;
  char res_per[15];
  char id_ing[5];
  char id_stock[5];
  char request[255];
  MYSQL * con;
  MYSQL_RES * result;
  MYSQL_ROW  row;

  con = NULL;

  connection_bdd(con);
  date = malloc(sizeof(char) * 255);
  peremption = malloc(sizeof(char) * 255);

  get_date (date);

  sprintf(request, "SELECT id, peremption FROM ingredient WHERE nom = %s;", tmp->name);
  if(mysql_query(con, request))
  {
    finish_with_error(con);
  }

  result = mysql_store_result(con);

  if (result == NULL)
  {
    finish_with_error(con);
  }

  row = mysql_fetch_row(result);

  strcpy(id_ing, row[0]);
  strcpy(res_per, row[1]);

  if (res_per == NULL){
    peremption = NULL;
    get_date(date);
  }
  else{
    get_date(date);
    get_peremption(strcpy(peremption, date), res_per);

  }
  uniform_quantity(tmp->quantity);

  total_quantity(tmp->quantity, tmp->nb);

  sprintf(request, "INSERT INTO stock (nom, marque, quantite, date_ajout, date_expire) VALUES ('%s', '%s', '%s', '%s', '%s');", tmp->name, tmp->brand, tmp->quantity, date, peremption);

  mysql_query(con, request);

  sprintf(request, "SELECT id FROM stock WHERE nom = %s AND marque = %s AND date_ajout = %s ;", tmp->name, tmp->brand, date);
  if(mysql_query(con, request))
  {
    finish_with_error(con);
  }
  result = mysql_store_result(con);

  if(result == NULL){
    finish_with_error(con);
  }
  row = mysql_fetch_row(result);

  strcpy(id_stock, row[0]);

  sprintf(request, "INSERT INTO contenant ( id_stock, id_ingredient) VALUES ('%s', '%s');", id_stock, id_ing);







  return 0;
}
