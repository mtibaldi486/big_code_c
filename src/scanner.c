#include "../inc/cool.h"

/****************************************************************************/
/*                 Function of :BUTTON "VALIDER" SCANNER PAGE               */
/****************************************************************************/
static t_prod   *begin = NULL;

t_prod   *check_product(t_prod **product)
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

int get_id_product()
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
  if (!(  get_product_name(product->id_product, product)))
  {
    lst_del(&begin, &product);
    display_lst_prod(begin);
    display_error(input_idproduct);
    return (0);
  }

  add_box_product(product);
  display_ok(input_idproduct);
  //free_product(product);
  display_lst_prod(begin);
  return (0);
}

/****************************************************************************/
/*                       FUNCTION DISPLAY GTK                               */
/****************************************************************************/

void display_inc_prod(t_prod *lst_prod)
{
  GtkWidget     *current_box;
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  GtkListBox    *box;
  char          new_name[200];
  char          new_nb[100];
  GtkWidget     *lab_nb;
  GtkWidget     *lab_name;
  GtkWidget     *lab_quantity;

  new_box = gtk_list_box_row_new();
  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_product_box"));
  if (!(current_box = GTK_WIDGET(gtk_list_box_get_row_at_index (box, lst_prod->index))))
  {
    return ;
  }
  gtk_widget_destroy(current_box);  fixed = gtk_fixed_new();

  strcpy(new_name, lst_prod->brand);
  strcat(strcat(new_name, " : "  ), lst_prod->name);
  strcpy(new_nb, "x ");
  strcat(new_nb, ft_itoa(lst_prod->nb));
  lab_nb = gtk_label_new(new_nb);
  lab_name = gtk_label_new(new_name);
  lab_quantity = gtk_label_new(lst_prod->quantity);

  gtk_fixed_put(GTK_FIXED(fixed), lab_nb, 450, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_quantity, 10, 50);

  gtk_container_add(GTK_CONTAINER(new_box), fixed);

  gtk_list_box_insert(box, new_box, lst_prod->index);

  return ;
}

int add_box_product(t_prod *product)
{
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  GtkListBox    *box;
  char          new_name[200];
  GtkWidget     *lab_nb;
  GtkWidget     *lab_name;
  GtkWidget     *lab_quantity;


  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_product_box"));
  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  strcpy(new_name, product->brand);
  strcat(strcat(new_name, " : "  ), product->name);
  lab_nb = gtk_label_new("x 0");
  lab_name = gtk_label_new(new_name);
  lab_quantity = gtk_label_new(product->quantity);

  gtk_fixed_put(GTK_FIXED(fixed), lab_nb, 450, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_quantity, 10, 50);

  gtk_container_add(GTK_CONTAINER(new_box), fixed);

  gtk_list_box_insert(box, new_box, 0);
  return (0);
}

void free_product(t_prod *product) {
  if (product->id_product)
    free(product->id_product);
  if (product->name)
    free(product->name);
  if (product->brand)
    free(product->brand);
  if (product->quantity)
    free(product->quantity);
}

void display_error(GtkEntry *entry)
{
  GtkWidget *lab_ok;

  page->scanner_page = GTK_WIDGET(gtk_builder_get_object(builder, "scanner_page"));
  lab_ok = GTK_WIDGET(gtk_builder_get_object(builder, "lab_add_ok"));
  gtk_widget_show_all(page->scanner_page);
  gtk_widget_hide(lab_ok);
  gtk_entry_set_text(GTK_ENTRY(entry), "");
  printf("IMPOSSIBLE D'AJOUTER LE PRODUIT !\n");
}

void display_ok(GtkEntry *entry)
{
  GtkWidget *lab_ko;

  page->scanner_page = GTK_WIDGET(gtk_builder_get_object(builder, "scanner_page"));
  lab_ko = GTK_WIDGET(gtk_builder_get_object(builder, "lab_add_ko"));
  gtk_widget_show_all(page->scanner_page);
  gtk_widget_hide(lab_ko);
  gtk_entry_set_text(GTK_ENTRY(entry), "");
  printf("AJOUT REUSSIT !\n");
}
