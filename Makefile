NAME = AperoCool
CC  = gcc
RM = rm -f
PTHREAD=-pthread
CFLAGS = -Wall -Wextra -c -g
#GTKLIB
GTKLIB=`pkg-config --cflags --libs gtk+-3.0`
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic
#JSON LIBS
CFLAGS += $(shell pkg-config --cflags json-c)
LDFLAGS += $(shell pkg-config --libs json-c)
#CURL LIB
LDFLAGS += $(-L/home/dast/lib -L/usr/local/ssl/lib)
LIBS = -lcurl -lnsl -ljson-c
SRCS = test.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) -o $(NAME) $(OBJS) $(LDFLAGS) $(LIBS)

$(OBJS): $(SRCS)
	$(CC) $(CFLAGS) $(GTKLIB) $(SRCS)

clean:
		$(RM) $(OBJS)

fclean: clean
		$(RM) $(NAME)

re: fclean all

	#$(addprefix src/,)
