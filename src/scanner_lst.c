#include "../inc/cool.h"

/****************************************************************************/
/*                  LIST FUNCTION FOR SCANNER                               */
/****************************************************************************/
void	ft_lstadd_back(t_prod **alst, t_prod *new)
{
	t_prod		*lst;

	lst = *alst;
	if (!lst)
		*alst = new;
	else
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
  return ;
}

t_prod	*ft_lstnew_prod(char *id)
{
	t_prod	*new;

  if (!(new = (t_prod *)malloc(sizeof(t_prod))))
    return (0);
  new->id_product = strdup(id);
  new->name = NULL;
  new->brand = NULL;
  new->quantity = NULL;
  new->nb = 1;
	new->next = NULL;
	return (new);
}

void	lst_inc_index(t_prod *lst)
{
		while (lst)
		{
      lst->index++;
			lst = lst->next;
		}
    return ;
}

void	lst_dec_index(t_prod *lst)
{
		while (lst)
		{
      lst->index--;
			lst = lst->next;
		}
    return ;
}

void lst_del(t_prod **lst, t_prod **product)
{
  t_prod *prec;
  t_prod *current;

  current = *lst;
  prec = NULL;
  while (current)
  {
    if (*product == current)
    {
      if (!prec && !current->next)
      {
        *lst = NULL;
        free_product(current);
        free(current);
      }
      else if (!current->next)
      {
        prec->next = NULL;
        free_product(current);
        free(current);
      }
      else
      {
        prec->next = current->next;
        free_product(current);
        free(current);
      }
    }
    prec = current;
    current = current->next;
  }
  lst_dec_index(*lst);
  return ;
}

void lst_clear()
{
	t_prod *tmp;

	if (!begin)
		return ;
  while (begin)
  {
    tmp = begin->next;
		free_product(begin);
		free(begin);
		begin = tmp;
  }
	begin = NULL;
}

//////FONCTION DE VERIFICATION /////////////
void display_lst_prod(t_prod *lst)
{
  printf("\n\n       /////Fonction Afficheg ////////\n\n");
  while (lst)
  {
    printf("id = %s\n", lst->id_product);
    printf("name = %s\n", lst->name);
    printf("brand = %s\n", lst->brand);
    printf("quantity = %s\n", lst->quantity);
    printf("nb product = %d\n\n", lst->nb);
    lst = lst->next;
  }
  printf("\n\n       /////FIN ////////\n\n");
  return ;
}
//////////////////////////////////////////////
