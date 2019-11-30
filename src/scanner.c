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

void read_file(FILE *pf, char **str)
{
	char  buff[1024];

  *str = calloc(1, 1);
  if (ftell(pf))
    fseek(pf, 0, SEEK_SET);
  while (fread(buff, 1023, 1, pf), !feof(pf))
  {
    buff[1023] = 0;
    *str = strjoin(*str, buff);
  }
}

char *parse_str(char *str, const char *handle)
{
  char *new = NULL;
  char *add_del;
  long  del;
  int  i;

  i = 0;
  while (str[i])
  {
    if (str[i] == ',')
    {
      if (ft_strnstr(&str[i], handle, 18))
      {
        str = strchr(str + i, ':');
        add_del = strchr(str + 2, '"');
        del = (add_del - str) - 2;
        new = calloc(1, del);
        strncpy(new, str + 2, del);
        *(new + del) = 0;
      }
    }
    i++;
  }
  return new;
}

t_prod *get_product_name(const char *id, t_prod *product)
{
  char    *str;
  FILE    *pf;

  if (!(pf = fopen("text.json", "w+")))
    return (0);

  (void)id;
  call_api(pf);
  read_file(pf, &str);
  if (!(product->name = parse_str(str, "\"product_name_fr\"")))
    return (NULL);

  free(str);
  fclose(pf);
  return (product);
}

int call_api(FILE *pf)
{
  CURL        *curl;
  CURLcode    res;

  curl = curl_easy_init();
  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "http://fr.openfoodfacts.org/api/v0/product/5010677850100.json");
    /* example.com is redirected, so we tell libcurl to follow redirection */
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)pf);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);

    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);
  }
  return 0;
}
