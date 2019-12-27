#include "../inc/cool.h"

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

int verify_peremption(char * date, char * peremption)
{
    int dayn, monthn, yearn;
    int daye, monthe, yeare;

    if( strstr(peremption, "NULL") || peremption[0] == '\0')
      return 0;

    sscanf(date,"%d-%d-%d", &dayn, &monthn, &yearn);
    sscanf(peremption,"%d-%d-%d", &daye, &monthe, &yeare);

    if(yearn > yeare)
      return 1;
    if(monthn > monthe)
      return 1;
    if( (dayn > daye) && (monthn == monthe) && (yearn == yeare))
      return 1;
    else
      return 0;
}

void delete_stock(char * id, MYSQL * con)
{
  char request[200];

  sprintf(request, "DELETE FROM stock WHERE id_stock = '%s'", id);
  if(mysql_query(con, request))
  {
    finish_with_error(con);
  }

  sprintf(request, "DELETE FROM stock WHERE id = '%s'", id);
  if(mysql_query(con, request))
  {
    finish_with_error(con);
  }

  return ;
}

void adjust_stock()
{
    char * date;
    char ** res = NULL;
    char ** res_split;
    MYSQL * con = NULL;
    MYSQL_RES * result = NULL;
    int i = 0;


    date = malloc(sizeof(char) * 15);
    connection_bdd(con);
    get_date(date);



    if(mysql_query(con, "SELECT * FROM stock"))
      return ;
    write(1, "OK2\n",4);
    if (!(result = mysql_store_result(con)))
      return ;
    if (!(res = format_res(result)))
      return ;

    while( res[i] ){
      res_split = ft_split(res[i], ';');
      if( verify_peremption( date , res_split[5]) == 1){
        delete_stock(res_split[0], con);
      }
      i++;
    }

    mysql_free_result(result);
    return ;
}
