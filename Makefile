all: rodcut

OBJS = main.o rodcut.o vec.o
CC = gcc
CFLAGS = -Wall

rodcut: $(OBJS)
	gcc -o rodcut $(CFLAGS) $(OBJS)

main.o: main.c rodcut.h vec.h

rodcut.o: rodcut.c rodcut.h

vec.o: vec.c vec.h

clean:
	rm -f rodcut $(OBJS)