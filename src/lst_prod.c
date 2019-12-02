#include "../inc/cool.h"
#include <unistd.h>

/****************************************************************************/
/*                  LIST FUNCTION FOR SCANNER                               */
/****************************************************************************/
void	ft_lstadd_back(t_prod **alst, t_prod *new)
{
	t_prod		*begin;

	begin = *alst;
	if (!begin)
		*alst = new;
	else
	{
		while (begin->next)
			begin = begin->next;
		begin->next = new;
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
  new->nb = 0;
	new->next = NULL;
	return (new);
}

void display_lst_prod(t_prod *begin)
{
  printf("\n\n       /////Fonction Afficheg ////////\n\n");
  while (begin)
  {
    printf("id = %s\n", begin->id_product);
    printf("name = %s\n", begin->name);
    printf("brand = %s\n", begin->brand);
    printf("quantity = %s\n", begin->quantity);
    printf("nb product = %d\n\n", begin->nb);
    begin = begin->next;
  }
  printf("\n\n       /////FIN ////////\n\n");
  return ;
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

void lst_del(t_prod **begin, t_prod **product)
{
  t_prod *prec;
  t_prod *current;

  current = *begin;
  prec = NULL;
  while (current)
  {
    if (*product == current)
    {
      if (!prec && !current->next)
      {
        *begin = NULL;
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
  lst_dec_index(*begin);
  return ;
}

void lst_clear(t_prod **begin)
{
  while (begin)
  {

    *begin = (*begin)->next;
  }
}
