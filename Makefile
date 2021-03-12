CC=gcc
CFLAGS= -Wall -pedantic -Werror -std=gnu99 -ggdb3 $(OTHERFLAGS)
poker: cards.o  deck.o  eval.o  future.o  input.o  main.o
                gcc -o $@ $(CFLAGS) $^
clean:
                rm -rf *.o poker *~
