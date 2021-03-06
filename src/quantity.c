#include "../inc/cool.h"

char * total_quantity(char *quantity, int nb)
{
  char    *quantite;
  char    *unity;
  double  nbquantite;

  quantite = strdup(quantity);
  nbquantite=strtod(quantite, &unity);
  if(*unity != 0){
    nbquantite *= nb;
    sprintf(quantity, "%.2lf%s", nbquantite, unity);
  }
  else{
    nbquantite *= nb;
    sprintf(quantity, "%.2lf", nbquantite);
  }
  free(quantite);
  return quantity;
}

char *final_quantity(t_prod *tmp, char *quantity_bdd)
{
  double quantite;
  double quantite_bdd;
  char   unit[10];

  sscanf(tmp->quantity, "%lf%s", &quantite, unit);
  sscanf(quantity_bdd, "%lf", &quantite_bdd);
  quantite += quantite_bdd;
  sprintf(tmp->quantity, "%.2lf%s", quantite, unit);
  uniform_unit(tmp->quantity);
  return tmp->quantity;
}

char * uniform_unit(char * quantity)
{
  char   *unity;
  char   *pt;
  double nbquantity;
  char   liquidunity[] = "cl";
  char   solidunity[] = "g";

  lowercase(quantity);
  nbquantity=strtod(quantity, &unity);

  if(strstr(unity, "ml") != NULL){
    nbquantity /= 10;
    sprintf(quantity, "%.2lf%s", nbquantity, liquidunity);
  }
  else if(strstr(unity, "cl") != NULL){
    ;
  }
  else if( (pt = strstr(unity, "l"))){
    if(*(pt+1) == ' ' || *(pt+1) == '\0' || !(*(pt+1) <=122 && *(pt+1) >= 97)){
      nbquantity *= 100;
      sprintf(quantity, "%.2lf%s", nbquantity, liquidunity);
    }
  }
  else if(strstr(unity, "kg") != NULL){
    nbquantity *= 1000;
    sprintf(quantity, "%.2lf%s", nbquantity, solidunity);
  }
  else if (strstr(unity,"mg") != NULL){
    nbquantity /= 1000;
    sprintf(quantity, "%.2lf%s", nbquantity, solidunity);
  }
  return quantity;
}
