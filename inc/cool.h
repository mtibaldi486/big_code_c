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
#include <mysql.h>

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
  char            *id_product;
  char            *name;
  char            *brand;
  char            *quantity;
  int             *id_category;
  int             nb;
  int             index;
  struct s_prod   *next;
}              t_prod;

// GLOBAL Variables
t_page          *page;
GtkBuilder      *builder;

/****************************************************************************/
/*                     GUI_DEPLACEMENT_C                                    */
/****************************************************************************/
void          go_to_menu(void);
void          goto_generate(void);
void          goto_ressource(void);
void          goto_cocktail(void);
void          goto_scanner(void);
void          goto_form(void);
void          generate_to_menu(void);
void          ressource_to_menu(void);
void          cocktail_to_menu(void);
void          scanner_to_ressource(void);

/****************************************************************************/
/*                             SCANNER_C                                    */
/****************************************************************************/
int           get_id_product();
t_prod       *check_product(t_prod **product);
void          free_product(t_prod *product);

/****************************************************************************/
/*                       SCANNER_DISPLAY_C                                  */
/****************************************************************************/
int           add_box_product();
void          display_inc_prod(t_prod *lst_prod);
void          display_error(GtkEntry *entry);
void          display_ok(GtkEntry *entry);

/****************************************************************************/
/*                             CALL_API_C                                   */
/****************************************************************************/
void          read_file(FILE *pf, char **str);
char          *parse_str(char *str, const char *handle);
int           call_api(FILE *pf, char *path);
t_prod        *get_product_info(char *id, t_prod *product);
char          *make_path(char *id);

/****************************************************************************/
/*                             LST_PROD_C                                   */
/****************************************************************************/
void	        ft_lstadd_back(t_prod **alst, t_prod *new);
t_prod      	*ft_lstnew_prod(char *id);
void          display_lst_prod(t_prod *lst);
void	        lst_inc_index(t_prod *lst);
void	        lst_dec_index(t_prod *lst);
void          lst_del(t_prod **begin, t_prod **product);

/****************************************************************************/
/*                             UTILS_C                                      */
/****************************************************************************/
char          *strjoin(char *s1, char *s2);
char          *ft_strnstr(const char *s1, const char *s2, size_t len);
//const char    *get_input_text(char*str);
char	        *ft_itoa(int nb);

/****************************************************************************/
/*                            COCKTAILS_C                                   */
/****************************************************************************/
int load_lst_cocktails();
void finish_with_error(MYSQL *con);


#endif
