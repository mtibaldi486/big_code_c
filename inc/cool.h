#ifndef COOL_H
# define COOL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <gtk/gtkx.h>
#include "gtk/gtk.h"
#include <curl/curl.h>

typedef struct s_page
{
  GtkWidget    *window;
  GtkWidget    *home_page;
  GtkWidget    *menu_page;
  GtkWidget    *generate_page;
  GtkWidget    *ressource_page;
  GtkWidget    *scanner_page;
  GtkWidget    *cocktail_page;
}              t_page;

typedef struct s_prod
{
  const char   *id_product;
  char         *name;
  char         *brand;
  char         *quantity;
  int          *id_category;
}              t_prod;

// GLOBAL Variables
t_page       *page;

GtkBuilder   *builder;
GtkListBox    *box;

/****************************************************************************/
/*                     GUI_DEPLACEMENT_C                                    */
/****************************************************************************/
void    go_to_menu(void);
void    goto_generate(void);
void    goto_ressource(void);
void    goto_cocktail(void);
void    goto_scanner(void);
void    goto_form(void);
void    generate_to_menu(void);
void    ressource_to_menu(void);
void    cocktail_to_menu(void);
void    scanner_to_ressource(void);

/****************************************************************************/
/*                             SCANNER_C                                    */
/****************************************************************************/
int     add_box_product();
int     get_id_product();
void    read_file(FILE *pf, char **str);
char    *parse_str(char *str, const char *handle);
t_prod  *get_product_name(const char *id, t_prod *product);
int     call_api(FILE *pf);

/****************************************************************************/
/*                             UTILS_C                                      */
/****************************************************************************/
char          *strjoin(char *s1, char *s2);
char          *ft_strnstr(const char *s1, const char *s2, size_t len);
const char    *get_input_text(char*str);

/****************************************************************************/
/*                             CALL_API_C                                   */
/****************************************************************************/
void read_file(FILE *pf, char **str);
char *parse_str(char *str, const char *handle);
int call_api(FILE *pf);


#endif
