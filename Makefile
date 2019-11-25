#change application name here (executable output name)
TARGET=AperoCool
INC=inc/cool.h
# compiler
CC=gcc
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall -Werror -Wall
PTHREAD=-pthread
CCFLAGS=$(DEBUG) $(OPT) $(WARN) $(PTHREAD) -pipe

GTKLIB=`pkg-config --cflags --libs gtk+-3.0`

# linker
LD=gcc
LDFLAGS=$(PTHREAD) $(GTKLIB) -export-dynamic

OBJS=main.o

all:$(OBJS)	$(INC)
		$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

main.o:src/main.c
	$(CC) -c $(CCFLAGS) src/main.c $(GTKLIB) -o main.o

clean:
	rm -f *.o $(TARGET)

fclean:	clean
	rm -f $(TARGET)

re: fclean
	make
