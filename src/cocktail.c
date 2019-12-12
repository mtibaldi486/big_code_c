#include "../inc/cool.h"

int count_len(gchar *info)
{
  int i;
  gchar *tmp;

  printf("info = %s\n", info);

  tmp = info;
  while (!(isdigit(*(strchr(tmp, ' ') + 1))))
  {
    tmp = strchr(tmp, ' ') + 1;
  }
  i = strchr(tmp, ' ') - info;
  return (i);
}

void display_elem(gchar info[255])
{
  char  name[20];
  char  quantity[4];
  char  path_pic[50];
  char  path_recipe[50];
  char  star;

  info = strchr(info, ' ') + 1;
  printf("len = %d\n", count_len(info));
}
