#include "../inc/cool.h"

/****************************************************************************/
/*                 Function of :BUTTON "VALIDER" SCANNER PAGE               */
/****************************************************************************/

<<<<<<< HEAD


=======
>>>>>>> f808c3e640ffd12ceccbc15749ef1e3c19eef24b
int    get_id_product()
{
  GtkEntry      *input_idproduct;
  char          *id;
  t_prod        *product;
  t_prod        *lst_prod;

  //////////recuperation su scan ///////////////
  input_idproduct = GTK_ENTRY(gtk_builder_get_object(builder, "input_idproduct"));
  id = (char *)gtk_entry_get_text(GTK_ENTRY(input_idproduct));
  if (!(product = ft_lstnew_prod(id)))
    return (0);
  if ((lst_prod = check_product(&product)))
  {
    gtk_entry_set_text(GTK_ENTRY(input_idproduct), "");
    display_inc_prod(lst_prod);
    display_lst_prod(begin);
    display_ok(input_idproduct);
    return (0);
  }
  if (!( get_product_info(product->id_product, product)))
  {
    lst_del(&begin, &product);
    display_lst_prod(begin);
    display_error(input_idproduct);
    return (0);
  }

  add_box_product(product);
  display_ok(input_idproduct);
  display_lst_prod(begin);
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
