#include "../inc/cool.h"

/****************************************************************************/
/*                 Function of :BUTTON "VALIDER" SCANNER PAGE               */
/****************************************************************************/

int    get_id_product()
{
  GtkEntry      *input_idproduct;
  char          *id;
  t_prod        *product;
  t_prod        *lstprod;

  //////////recuperation su scan ///////////////
  input_idproduct = GTK_ENTRY(gtk_builder_get_object(builder, "input_idproduct"));
  id = (char *)gtk_entry_get_text(GTK_ENTRY(input_idproduct));
  if (!(product = ft_lstnew_prod(id)))
    return (0);
  if ((lstprod = check_product(&product)))
  {
    free(product->id_product);
    free(product);
    gtk_entry_set_text(GTK_ENTRY(input_idproduct), "");
    display_inc_prod(lstprod);
    display_ok(input_idproduct);
    return (0);
  }
  else if (!(get_product_info(product->id_product, product)))
  {
    lst_del(&begin, &product);
    display_error(input_idproduct);
    return (0);
  }
  else if(!(check_necessary(product->name)))
  {
    free_product(product);
    free(product);
    display_error(input_idproduct);
    return (0);
  }

  add_box_product(product);
  display_ok(input_idproduct);
  return (0);
}

t_prod  *check_product(t_prod **product)
{
  t_prod  *tmp;
  int     i;

  i = 0;
  if (!begin)
  {
    (*product)->index = 0;
    ft_lstadd_back(&begin, *product);
    return (NULL);
  }
  else
  {
    tmp = begin;
    while (tmp)
    {
      if (!strcmp(tmp->id_product, (*product)->id_product))
      {
        tmp->nb++;
        return (tmp);
      }
      i++;
      tmp = tmp->next;
    }
    lst_inc_index(begin);
    (*product)->index = 0;
    ft_lstadd_back(&begin, *product);
  }
  return (NULL);
}

t_prod *get_product_info(char *id, t_prod *product)
{
  char    *str;
  FILE    *pf;
  char    *path;

  if (!(pf = fopen("text.json", "w+")))
    return (0);

  path = make_path(id);
  call_api(pf, path);
  read_file(pf, &str);
  if (!(product->name = parse_str(str, "\"product_name_fr\":")))
  {
    free(str);
    fclose(pf);
    return (NULL);
  }
  if (!(product->brand = parse_str(str, "\"brands\":")))
  {
    free(str);
    fclose(pf);
    return (NULL);
  }
  if (!(product->quantity = parse_str(str, "\"quantity\":")))
  {
    free(str);
    fclose(pf);
    return (NULL);
  }
  free(str);
  fclose(pf);
  return (product);
}

int check_necessary(char * name)
{
  int i = 0;
  char **res = NULL;
  char **res_split = NULL;
  char tmp[255];
  MYSQL * con;
  MYSQL_RES * result = NULL;

  strcpy(tmp,name);
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
    res_split= ft_split(res[i], ';');
    if((strstr(lowercase(tmp), lowercase(res_split[1])))){
      free_res(res, 2000);
      free_res(res_split, 2000);
      mysql_free_result(result);
      mysql_close(con);
      return 1;
    }
    i++;
  }
  free_res(res, 2000);
  free_res(res_split, 2000);
  mysql_free_result(result);
  mysql_close(con);
  return 0;
}

void vider_list()
{
  lst_clear();
}

void   free_product(t_prod *product)
{
  if (product->id_product)
  {
    free(product->id_product);
    product->id_product = NULL;
  }
  if (product->name)
  {
    free(product->name);
    product->name = NULL;
  }
  if (product->brand)
  {
    free(product->brand);
    product->brand = NULL;
  }
  if (product->quantity)
  {
    free(product->quantity);
    product->quantity = NULL;
  }
}
