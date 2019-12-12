#include "../inc/cool.h"

/****************************************************************************/
/*                  LIST FUNCTION FOR COCKTAIL                              */
/****************************************************************************/

void	lstadd_back_cocktail(t_cocktail **alst, t_cocktail *new)
{
	t_cocktail		*lst;

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

void display_lst_cocktail(t_cocktail *lst)
{
  printf("\n/////AFFICHAGE LST COCKTAILS ////////\n\n");
  while (lst)
  {
    printf("info = '%s'\n", lst->info);
    lst = lst->next;
  }
  printf("\n/////FIN ////////\n\n");
  return ;
}

t_cocktail	*lstnew_cocktail()
{
	t_cocktail	*new;

  if (!(new = (t_cocktail *)malloc(sizeof(t_cocktail))))
    return (0);
	new->next = NULL;
	return (new);
}
