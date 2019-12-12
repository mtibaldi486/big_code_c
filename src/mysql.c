#include "../inc/cool.h"

MYSQL * connection_bdd(MYSQL * con){
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
  }

  return *con;
}
