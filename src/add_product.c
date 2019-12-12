#include "../inc/cool.h"

char * get_date(char * date)
{
  int day;
  int month;
  int year;

  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  day = tm.tm_mday;
  month = tm.tm_mon + 1;
  year = tm.tm_year + 1900;
  sprintf(date,"%d-%d-%d", day, month, year);
  return date;
}

char * get_peremption(char *date, int final){
  int day, month, year;
  char dayc[3], monthc[3], yearc[3];
  char month31 []= "01,03,05,07,08,10,12,";
  char month30 []= "04,06,09,11";
  sscanf(date,"%d-%d-%d", &day, &month, &year);

  while (final != 0){
    day++;
    if(day > 28 && strcmp(monthc, "02")==0 && (year%4)!=0){
      month++;
      day = 01;
    }
    if(day > 29 && strcmp(monthc, "02")==0 && (year%4) ==0){
      month++;
      day = 01;
    }
    if (day > 30 && strstr(month30, monthc)!=0){
      month++;
      day = 01;
    }
    if(day > 31 && strstr(month31, monthc)!=0){
      month++;
      day = 01;
    }

    if( month > 12){
      month = 01;
      year ++;
    }
    final--;
    if (day < 10)
      sprintf(dayc, "0%d", day);
    else
      sprintf(dayc, "%d", day);
    if (month < 10)
      sprintf(monthc, "0%d", month);
    else
      sprintf(monthc, "%d", month);
    sprintf(yearc, "%d", year);
  }
  sprintf(date, "%s-%s-%s", dayc, monthc, yearc);
  printf("%d\n", final );
  return date;
}

int insert_bdd(){//int insert_bdd(t_prod *tmp)
/////////////////////////CONNECTION A LA BDD///////////////////////
  /*MYSQL           *con;
  MYSQL_RES       *result = NULL;
  int num_fields;
  MYSQL_ROW       row;
  con = mysql_init(NULL);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      return 1;
  }
  if (mysql_real_connect(con, "localhost", "root", "root",
          "aperocool", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }*/

//////////////////////Convertion des données////////////////////////////
  char * date;
  char * peremption;
  int res_per = 216;

  date = malloc(sizeof(char) * 255);
  peremption = malloc(sizeof(char) * 255);

  get_date(date);
  strcpy(peremption, date);
  get_peremption(peremption, res_per);

  printf("date : %s\nperemption le : %s\n", date, peremption);

  /*char query_check[255];
  if (get_date (date)){
    strcat(strcpy(query_check, "SELECT peremption FROM ingredient WHERE name = "), name);
    if(mysql_query(con, query_check))
    {
      finish_with_error(con);
    }

    result = mysql_store_result(con);




  }*/

  return 0;
}
