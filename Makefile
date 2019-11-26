SRCS = main.c gui_deplacement.c

OBJS = $(SRCS:.c=.o)


NAME = AperoCool
CC  = gcc
RM = rm -f
PTHREAD=-pthread
CFLAGS = -Wall -Wextra -Werror -c
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS)

$(OBJS): $(addprefix src/, $(SRCS))
	$(CC) $(CFLAGS) $(GTKLIB) $(addprefix	 src/, $(SRCS))

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all
