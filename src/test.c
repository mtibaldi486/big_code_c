#include "../inc/cool.h"

int main()
{
  MYSQL *con = mysql_init(NULL);

 if (con == NULL)
 {
     fprintf(stderr, "%s\n", mysql_error(con));
     exit(1);
 }

 if (mysql_real_connect(con, "localhost", "root", "root",
         NULL, 0, NULL, 0) == NULL)
 {
     fprintf(stderr, "%s\n", mysql_error(con));
     mysql_close(con);
     exit(1);
 }

 if (mysql_query(con, "CREATE DATABASE testdb"))
 {
     fprintf(stderr, "%s\n", mysql_error(con));
     mysql_close(con);
     exit(1);
 }

 mysql_close(con);
 printf("OKKKK");
 exit(0);
}
