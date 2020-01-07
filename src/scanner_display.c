#include "../inc/cool.h"

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
  char          new_name[50];
  GtkWidget     *lab_nb;
  GtkWidget     *lab_name;
  GtkWidget     *lab_quantity;


  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_product_box"));
  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  strcpy(new_name, product->brand);
  strcat(strcat(new_name, " : "), product->name);
  lab_nb = gtk_label_new("x 1");
  lab_name = gtk_label_new(new_name);
  lab_quantity = gtk_label_new(product->quantity);

  gtk_fixed_put(GTK_FIXED(fixed), lab_nb, 450, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_quantity, 10, 50);

  gtk_container_add(GTK_CONTAINER(new_box), fixed);

  gtk_list_box_insert(box, new_box, 0);
  return (0);
}

void display_error(GtkEntry *entry)
{
  GtkWidget *lab_ok;

  page->scanner_page = GTK_WIDGET(gtk_builder_get_object(builder, "scanner_page"));
  lab_ok = GTK_WIDGET(gtk_builder_get_object(builder, "lab_add_ok"));
  gtk_widget_show_all(page->scanner_page);
  gtk_widget_hide(lab_ok);
  gtk_entry_set_text(GTK_ENTRY(entry), "");
}

void display_ok(GtkEntry *entry)
{
  GtkWidget *lab_ko;

  page->scanner_page = GTK_WIDGET(gtk_builder_get_object(builder, "scanner_page"));
  lab_ko = GTK_WIDGET(gtk_builder_get_object(builder, "lab_add_ko"));
  gtk_widget_show_all(page->scanner_page);
  gtk_widget_hide(lab_ko);
  gtk_entry_set_text(GTK_ENTRY(entry), "");
}
