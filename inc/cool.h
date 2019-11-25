#ifndef COOL_H
# define COOL_H

#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <gtk/gtkx.h>
#include "gtk/gtk.h"

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

/****************************************************************************/
/*                     GUI_DEPLACEMENT_C                                    */
/****************************************************************************/
/*void go_to_menu(void);
void goto_generate(void);
void goto_ressource(void)
void goto_cocktail(void);
void goto_scanner(void);
void goto_form(void);
void generate_to_menu(void);
void ressource_to_menu(void);
void cocktail_to_menu(void);
void scanner_to_ressource(void);
*/

#endif
