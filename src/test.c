#include "../inc/cool.h"

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

int load_lst_cocktails()
{
  MYSQL         *con;
  MYSQL_RES     *result = NULL;
  int           num_fields;
  MYSQL_ROW     row;

  con = mysql_init(NULL);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }

  if (mysql_real_connect(con, "localhost", "root", "root",
          "aperocool", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
  }

  if (mysql_query(con, "SELECT * FROM cocktails"))
  {
      finish_with_error(con);
  }

  result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  num_fields = mysql_num_fields(result);

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          printf("%s ", row[i] ? row[i] : "NULL");
      }
          printf("\n");
  }

  mysql_free_result(result);
  mysql_close(con);

  exit(0);
}
