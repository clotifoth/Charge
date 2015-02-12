OBJS = src/main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)

Charge : $(OBJS)
	$(CC) $(LFLAGS) -o $@ $^ -lncurses

src/main.o : src/main.h src/main.cpp

clean:
	\rm *.o *~ p1
