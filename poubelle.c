
const char *get_input_text(char*str)
{
  GtkEntry      *input_id;
  const char    *res;

  input_id = GTK_ENTRY(gtk_builder_get_object(builder, str));
  res = gtk_entry_get_text(GTK_ENTRY(input_id));

  return (res);
}

void print_save_product(const char *array[200], int nb)
{
  int   i;

  i = 0;
  while (i < nb)
  {
    printf("id = %s\n", array[i]);
    i++;
  }
  return ;
}

/* GObject *g_object_clone(GObject *src)
{
    GObject *dst;
    GParameter *params;
    GParamSpec **specs;
    guint n, n_specs, n_params;

    specs = g_object_class_list_properties(G_OBJECT_GET_CLASS(src), &n_specs);
    params = g_new0(GParameter, n_specs);
    n_params = 0;

    for (n = 0; n < n_specs; ++n)
        if (strcmp(specs[n]->name, "parent") &&
            (specs[n]->flags & G_PARAM_READWRITE) == G_PARAM_READWRITE) {
            params[n_params].name = g_intern_string(specs[n]->name);
            g_value_init(&params[n_params].value, specs[n]->value_type);
            g_object_get_property(src, specs[n]->name, &params[n_params].value);
            ++ n_params;
        }

    dst = g_object_newv(G_TYPE_FROM_INSTANCE(src), n_params, params);
    g_free(specs);
    g_free(params);

    return dst;
}*/

void lst_del(t_prod **product, t_prod **begin)
{
  t_prod *tmp;
  t_prod *tmp2 = NULL;

  tmp = begin;
  while (tmp)
  {
    if (!strcmp(tmp->id_product, product->id_product))
    {
      if (tmp->next)
      {
        tmp2 = product->next;
        free_product(product);
        free(product);
      }
      else
      {
        free_product(product);
        free(product);
      }
      return ;
    }
    tmp2 = tmp;
    tmp = tmp->next;
  }
  return ;
}

//recuperation de nom de cocktail
strcpy(name, strchr(info, ' ') + 1);
tmp = name;
while (!(isdigit(*(strchr(tmp, ' ') + 1))))
{
  tmp = strchr(tmp, ' ') + 1;
}
tmp = strchr(tmp, ' ');
name[tmp - name] = '\0';
//Formatage de la note pour affichage
strcpy(mark, "Note :");
strcat(mark, strchr((strrchr(info, ' ') - 4), ' '));
strcat(mark, "/5");
printf("mark = %s\nname = '%s'\n", mark, name);

////MAXIME


strcpy(id_ing, row[0]);
strcpy(res_per, row[1]);

if (res_per == NULL){
  peremption = NULL;
  get_date(date);
}
else{
  get_date(date);
  get_peremption(strcpy(peremption, date), res_per);

}
uniform_quantity(tmp->quantity);

total_quantity(tmp->quantity, tmp->nb);

sprintf(request, "INSERT INTO stock (nom, marque, quantite, date_ajout, date_expire) VALUES ('%s', '%s', '%s', '%s', '%s');", tmp->name, tmp->brand, tmp->quantity, date, peremption);

mysql_query(con, request);

sprintf(request, "SELECT id FROM stock WHERE nom = %s AND marque = %s AND date_ajout = %s ;", tmp->name, tmp->brand, date);
if(mysql_query(con, request))
{
  finish_with_error(con);
}
result = mysql_store_result(con);

if(result == NULL){
  finish_with_error(con);
}
row = mysql_fetch_row(result);

strcpy(id_stock, row[0]);

sprintf(request, "INSERT INTO contenant ( id_stock, id_ingredient) VALUES ('%s', '%s');", id_stock, id_ing);
