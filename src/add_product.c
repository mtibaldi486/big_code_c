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


char * get_date(char * date)
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

char * get_peremption(char * date, int final){
  int day, month, year;
  char dayc[3], monthc[3], yearc[5];
  char month30 []= "04,06,09,11";
  char month31 []= "01,03,05,07,08,10,12";
  sscanf(date,"%d-%d-%d", &day, &month, &year);

  if (final == 0){
    return NULL;
  }

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
  printf("%d\n", final );
  return date;
}

int insert_bdd(t_prod *tmp){
//////////////////////Convertion des données////////////////////////////
  char * date;
  char * peremption;
  int res_per = 0;
  int id_ing;
  int id_stock;
  char query_check[255];
  MYSQL * con;

  connection_bdd(con);
  date = malloc(sizeof(char) * 255);
  peremption = malloc(sizeof(char) * 255);

  get_date (date);
  strcat(strcpy(query_check, "SELECT id,peremption FROM ingredient WHERE nom = "), tmp->name);
  if(mysql_query(con, query_check))
  {
    finish_with_error(con);
  }

  result = mysql_store_result(con);

  if (result == NULL)
  {
    finish_with_error(con);
  }

  row = mysql_fetch_row(result);

  id_ing = row[0];
  res_per = row[1];

  get_peremption(strcpy(peremption, date), res_per );


  /*get_date(date);
  strcpy(peremption, date);
  if(get_peremption(peremption, res_per) == NULL){
    peremption = NULL;
  }
  printf("date : %s\nperemption le : %s\n", date, peremption);*/







  return 0;
}
