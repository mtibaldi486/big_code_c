#include "../inc/cool.h"

/****************************************************************************/
/*                              CONNECT TO BDD                              */
/****************************************************************************/
MYSQL   *connection_bdd(MYSQL *con)
{
  con = mysql_init(NULL);
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      return NULL;
  }
  if (mysql_real_connect(con, "localhost", "root", "root",
          "aperocool", 0, NULL, 0) == NULL)
  {
      finish_with_error(con);
      return (NULL);
  }
  return (con);
}

/****************************************************************************/
/*                              JOIN ROW                                    */
/****************************************************************************/

gchar  *join_row(MYSQL_ROW row, int num_fields)
{
  gchar  *res;
  int    i;

  i = 0;
  if (!(res = malloc(sizeof(char) * 255)))
    return (NULL);
  strcpy(res, row[0]);
  strcat(res, ";");
  i = 1;
  for(i = 1; i < num_fields; i++)
  {
      strcat(res, row[i]);
      strcat(res, ";");
  }
  res[strlen(res) - 1] = 0;
  return (res);
}
