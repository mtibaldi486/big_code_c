#ifndef COOL_H
# define COOL_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <gtk/gtkx.h>
#include "gtk/gtk.h"
#include <curl/curl.h>
#include <mysql.h>
#include <ctype.h>

typedef struct s_page
{
  GtkWidget    *window;
  GtkWidget    *home_page;
  GtkWidget    *menu_page;
  GtkWidget    *generate_page;
  GtkWidget    *ressource_page;
  GtkWidget    *scanner_page;
  GtkWidget    *select_page;
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
}                 t_prod;

typedef struct s_data
{
  GtkWidget    *fixed;
  GtkWidget    *entry;
}              t_data;
// GLOBAL Variables
t_page             *page;
GtkBuilder         *builder;
t_prod             *begin;

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
void          cocktail_to_select(void);

/****************************************************************************/
/*                             SCANNER_C                                    */
/****************************************************************************/
int           get_id_product();
t_prod       *check_product(t_prod **product);
t_prod        *get_product_info(char *id, t_prod *product);
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
char          *mt_strccpy(char *s1, char *s2, char c);
//const char    *get_input_text(char*str);
const char    *ft_itoa(int nb);
char		    	**ft_split(char const *s, char c);

/****************************************************************************/
/*                               SELECT_C                                   */
/****************************************************************************/
int           load_lst_cocktails();
void          finish_with_error(MYSQL *con);
int           add_cocktail_box(gchar  info[255]);
void          del_lst_cocktail();

//COKTAIL_C
void          load_cocktail_page(GtkButton *button);
char          **format_ingredient(const gchar *info, int nb);
char          *ajust_ingredient(char *array_necessaire, int nb, char *ref);
char          **get_necessaire(char **array_cocktail);
char          **get_ingredient(char **array_necessaire);
void          free_res(char **res, int len);

//MYSQL_C
MYSQL         *connection_bdd(MYSQL *con);
gchar         *join_row(MYSQL_ROW row, int num_fields);
char          **format_res(MYSQL_RES *result_query);

//COCKTAIL_DISPLAY_C
void          display_picture(const gchar *info);
void          display_name(const gchar *info);
int           display_elem(const gchar *info, int nb);
GtkWidget     *display_ingredient(char **str_display);
void          display_counter(const gchar *info, t_data *data, int indice);
void          inc_entry(GtkWidget *button, gpointer *data_receive);
void          dec_entry(GtkWidget *button, gpointer *data_receive);

/****************************************************************************/
/*                               ADD_PRODUCT.C                              */
/****************************************************************************/
int           add_product();
int           insert_bdd(t_prod *tmp);
void          request_stock(t_prod *tmp, char * id_ing, char * peremption, MYSQL * con);
void          request_contenant(t_prod *tmp, char * date, char * id_ing, MYSQL * con);
void          free_add_product(MYSQL_RES *result, char *res_per, char *date);

//COCKTAIL_MARK_C
void          display_mark(const gchar *mark, char *id);
void          mark_up(GtkButton *button, gpointer *data);
void          mark_down(GtkButton *button, gpointer *data);
void          update_mark(char *mark, char *id);

/****************************************************************************/
/*                               FORM.C                                 */
/****************************************************************************/
char          *lowercase(char * string);
char          *delete_space(char * string);
char          *put_backslash(char * string);
char          *get_date(char * date);
char          *get_peremption(char * date, char * tmp);
int           verify_peremption(char * date, char * peremption);
void          delete_stock(char * id, MYSQL * con);
void          adjust_stock();

/****************************************************************************/
/*                               QUANTITY.C                               */
/****************************************************************************/
char          *total_quantity(char * quantity, int nb);
char          *final_quantity(char * quantity, char * quantity_bdd);
char          *uniform_unit(char * quantity);

/****************************************************************************/
/*                               GENERATE.C                                 */
/****************************************************************************/

void           generate_cocktail();
char          *get_id_ing(char * id_cocktail, MYSQL * con);
char          *check_stock(char * id_ingredient, MYSQL * con);
int           get_coktail(MYSQL *con, char * res);

/****************************************************************************/
/*                               INVENTORY_PAGE.C                          */
/****************************************************************************/

int           select_ingredient();
char          *verify_nature(MYSQL * con);
int           add_inventory_box(char **result, int type);
void          del_inventory_page();

#endif
