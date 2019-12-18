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
  if ( (lstprod = check_product(&product)))
  {
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
    printf("IMPOSSIBLE DE TROUVER LE NOM \n");
    free(str);
    fclose(pf);
    return (NULL);
  }
  if (!(product->brand = parse_str(str, "\"brands\":")))
  {
    printf("IMPOSSIBLE DE TROUVER La MARQUE \n");
    free(str);
    fclose(pf);
    return (NULL);
  }
  if (!(product->quantity = parse_str(str, "\"quantity\":")))
  {
    printf("IMPOSSIBLE DE TROUVER La QUANTITE \n");
    free(str);
    fclose(pf);
    return (NULL);
  }
  free(str);
  fclose(pf);
  return (product);
}

void   free_product(t_prod *product)
{
  if (product->id_product)
    free(product->id_product);
  if (product->name)
    free(product->name);
  if (product->brand)
    free(product->brand);
  if (product->quantity)
    free(product->quantity);
}
