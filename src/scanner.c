#include "../inc/cool.h"

/****************************************************************************/
/*                 Function of :BUTTON "VALIDER" SCANNER PAGE               */
/****************************************************************************/
static int     nb_product = 0;

void display_error()
{
  printf("IMPOSSIBLE D'AJOUTER LE PRODUIT !\n");
}

void display_ok() {
  printf("AJOUT REUSSIT !\n");
}

int add_box_product(t_prod *product)
{
  GtkWidget     *new_box;
  GtkWidget     *label;

  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_product_box"));
  new_box = gtk_list_box_row_new();

  label = gtk_label_new(product->name);
  gtk_container_add(GTK_CONTAINER(new_box), label);

  printf("idproduct = %s\n", product->name);
  gtk_list_box_insert(box, new_box, 0);
  gtk_widget_show_all(page->window);
  return (0);
}

int get_id_product()
{
  GtkEntry      *input_idproduct;
  t_prod        *product;

  if (!(product = malloc(sizeof(t_prod))))
    return (0);
  //////////recuperation su scan ///////////////
  input_idproduct = GTK_ENTRY(gtk_builder_get_object(builder, "input_idproduct"));
  product->id_product    = gtk_entry_get_text(GTK_ENTRY(input_idproduct));
  if (!(product = get_product_name(product->id_product, product)))
  {
    display_error();
    return (0);
  }

  add_box_product(product);
  display_ok();
  nb_product++;
  free(product);
  gtk_entry_set_text(GTK_ENTRY(input_idproduct), "");
  return (0);
}

t_prod *get_product_name(const char *id, t_prod *product)
{
  char    *str;
  FILE    *pf;

  if (!(pf = fopen("text.json", "w+")))
    return (0);

  (void)id;
  printf("BEFORE CALL API\n");
  call_api(pf);
  printf("CALL API OK\n");
  read_file(pf, &str);
  printf("READ FILE OK\n");
  if (!(product->name = parse_str(str, "\"product_name_fr\":")))
    return (NULL);

  free(str);
  fclose(pf);
  return (product);
}
