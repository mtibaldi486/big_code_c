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
    sprintf(quantity, "%.2lf %s", nbquantite, unity);
  }
  else{
    nbquantite *= nb;
    sprintf(quantity, "%.2lf", nbquantite);
  }
  free(quantite);
  return quantity;
}

char *final_quantity(char * quantity, char * quantity_bdd)
{
  double quantite;
  double quantite_bdd;
  char unit [10];

  sscanf(quantity, "%lf%s", &quantite, unit);
  sscanf(quantity_bdd, "%lf", &quantite_bdd);
  quantite += quantite_bdd;
  sprintf(quantity, "%.2lf%s", quantite, unit);
  uniform_unit(quantity);

  return quantity;
}

char * uniform_unit(char * quantity)
{
  char   *quantite;
  char   *unity;
  char   *pt;
  double nbquantity;
  char   liquidunity[] = "cl";
  char   solidunity[] = "g";

  lowercase(quantity);
  delete_space(quantity);
  quantite = strdup(quantity);
  nbquantity=strtod(quantite, &unity);

  if(strstr(unity, "ml") != NULL){
    nbquantity /= 10;
    sprintf(quantity, "%.2lf%s", nbquantity, liquidunity);
    free(quantite);
    return quantity;
  }
  else if(strstr(unity, "cl") != NULL){
    free(quantite);
    return quantity;
  }
  else if( (pt = strstr(unity, "l"))){
    if(*pt++ == ' ' || *pt++ == '\0'){
      nbquantity *= 100;
      sprintf(quantity, "%.2lf%s", nbquantity, liquidunity);
      free(quantite);
      return quantity;
    }
    else{
      free(quantite);
      return quantity;
    }
  }
  else if(strstr(unity, "kg") != NULL){
    nbquantity *= 1000;
    sprintf(quantity, "%.2lf%s", nbquantity, solidunity);
    free(quantite);
    return quantity;
  }
  else if (strstr(unity,"mg") != NULL){
    nbquantity /= 1000;
    sprintf(quantity, "%.2lf%s", nbquantity, solidunity);
    free(quantite);
    return quantity;
  }
  else{
    free(quantite);
    return quantity;
  }
}
