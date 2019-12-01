#include "../inc/cool.h"

/****************************************************************************/
/*                 Function of :BUTTON "VALIDER" SCANNER PAGE               */
/****************************************************************************/
static int     nb_product = 0;

void display_error(GtkEntry *entry)
{
  gtk_entry_set_text(GTK_ENTRY(entry), "");
  printf("IMPOSSIBLE D'AJOUTER LE PRODUIT !\n");
}

void display_ok() {
  printf("AJOUT REUSSIT !\n");
}

int add_box_product(t_prod *product)
{
  GtkWidget     *new_box;
  GtkWidget     *fixed;
  char          new_name[200];
  GtkWidget     *lab_name;
  GtkWidget     *lab_quantity;


  box = GTK_LIST_BOX(gtk_builder_get_object(builder, "list_product_box"));
  new_box = gtk_list_box_row_new();
  fixed = gtk_fixed_new();

  strcpy(new_name, product->brand);
  strcat(strcat(new_name, " : "  ), product->name);
  lab_name = gtk_label_new(new_name);
  lab_quantity = gtk_label_new(product->quantity);

  gtk_fixed_put(GTK_FIXED(fixed), lab_name, 10, 10);
  gtk_fixed_put(GTK_FIXED(fixed), lab_quantity, 10, 50);

  gtk_container_add(GTK_CONTAINER(new_box), fixed);

  printf("name = %s\n", product->name);
  printf("marque = %s\n", product->brand);
  printf("Quantité = %s\n", product->quantity);
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
  product->name = NULL;
  product->brand = NULL;
  product->quantity = NULL;
  //////////recuperation su scan ///////////////
  input_idproduct = GTK_ENTRY(gtk_builder_get_object(builder, "input_idproduct"));
  product->id_product = (char *)gtk_entry_get_text(GTK_ENTRY(input_idproduct));
  if (!(product = get_product_name(product->id_product, product)))
  {
    display_error(input_idproduct);
    return (0);
  }

  add_box_product(product);
  display_ok();
  nb_product++;
  free_product(product);
  gtk_entry_set_text(GTK_ENTRY(input_idproduct), "");
  return (0);
}

char  *make_path(char *id)
{
  char *path;

  if (!(path = malloc(1 * 200)))
    return (0);
  memcpy((void *)path, (void *)"http://fr.openfoodfacts.org/api/v0/product/", 44);
  *(path + 43) = 0;
  printf("path1 = '%s'\n", path);
  strcat(path, id);
  strcat(path, ".json");
  return (path);
}

t_prod *get_product_name(char *id, t_prod *product)
{
  char    *str;
  FILE    *pf;
  char    *path;

  if (!(pf = fopen("text.json", "w+")))
    return (0);

  path = make_path(id);
  printf("BEFORE CALL API\n");
  call_api(pf, path);
  printf("CALL API OK\n");
  read_file(pf, &str);
  printf("READ FILE OK\n");
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

void free_product(t_prod *product) {
  if (product->name)
    free(product->name);
  if (product->brand)
    free(product->brand);
  if (product->quantity)
    free(product->quantity);
}
