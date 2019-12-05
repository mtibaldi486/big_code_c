NAME = AperoCool
CC  = gcc
RM = rm -f
PTHREAD=-pthread
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
SRCS = test.c

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
