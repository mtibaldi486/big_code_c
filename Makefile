NAME = AperoCool
CC  = gcc
RM = rm -f
PTHREAD = -pthread
INC = inc/cool.h
CFLAGS = -Wall -Wextra -c -g
##GTKLIB
GTKLIB = `pkg-config --cflags --libs gtk+-3.0`
LDFLAGS = $(PTHREAD) $(GTKLIB) -export-dynamic
##MYSQL
LDFLAGS += `mysql_config --cflags --libs`
CFLAGS += `mysql_config --cflags --libs`
##CURL LIB
LDFLAGS += $(-L/home/dast/lib -L/usr/local/ssl/lib)
LIBS = -lcurl -lnsl
SRCS = main.c gui_deplacement.c utils.c mysql.c\
scanner.c scanner_display.c scanner_lst.c call_api.c \
select.c cocktail.c\
add_product.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS) $(INC)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJS): $(addprefix src/,$(SRCS))
	$(CC) $(CFLAGS) $(GTKLIB) $(addprefix src/,$(SRCS))

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
