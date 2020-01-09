#include "../inc/cool.h"

int confirm_form()
{
  GtkEntry      *input_name;
  GtkEntry      *input_brand;
  GtkEntry      *input_quantity;
  t_prod        product;
  int           i = 0;

  input_name = GTK_ENTRY(gtk_builder_get_object(builder, "product_name"));
  input_brand = GTK_ENTRY(gtk_builder_get_object(builder, "product_brand"));
  input_quantity = GTK_ENTRY(gtk_builder_get_object(builder, "product_quantity"));
  product.name = (char *)gtk_entry_get_text(GTK_ENTRY(input_name));
  product.brand = (char *)gtk_entry_get_text(GTK_ENTRY(input_brand));
  product.quantity = (char *)gtk_entry_get_text(GTK_ENTRY(input_quantity));
  product.nb = 1;




  if(!(check_necessary(product.name)))
  {
    display_reset(input_name, input_brand, input_quantity);
    return 0;
  }

  while( product.quantity[i])
  {
    if ( product.quantity[i] >= '0' && product.quantity[i] <= '9'){
      insert_bdd(&product);
      display_confirm(input_name, input_brand, input_quantity);
      return 1;
    }
    i++;
  }

  display_reset(input_name, input_brand, input_quantity);
  return 0;
}

void display_reset(GtkEntry *entry, GtkEntry *entry2, GtkEntry *entry3)
{
  GtkWidget *lab_ok;

  page->form_page = GTK_WIDGET(gtk_builder_get_object(builder, "form_page"));
  lab_ok = GTK_WIDGET(gtk_builder_get_object(builder, "lab_possible"));
  gtk_widget_show_all(page->form_page);
  gtk_widget_set_visible(lab_ok, FALSE);
  gtk_entry_set_text(GTK_ENTRY(entry), "");
  gtk_entry_set_text(GTK_ENTRY(entry2), "");
  gtk_entry_set_text(GTK_ENTRY(entry3), "");
}

void display_confirm(GtkEntry *entry, GtkEntry *entry2, GtkEntry *entry3)
{
  GtkWidget *lab_ko;


  page->form_page = GTK_WIDGET(gtk_builder_get_object(builder, "form_page"));
  lab_ko = GTK_WIDGET(gtk_builder_get_object(builder, "lab_impossible"));
  gtk_widget_show_all(page->form_page);
  gtk_widget_set_visible(lab_ko, FALSE);
  gtk_entry_set_text(GTK_ENTRY(entry), "");
  gtk_entry_set_text(GTK_ENTRY(entry2), "");
  gtk_entry_set_text(GTK_ENTRY(entry3), "");
}
