#gan ten bien thay the
CFLAGS = -c -Wall		
CC = gcc
#GNU debug
GNU = -g

all: main
main: main.o str_dgraph.o libfdr/libfdr.a
	${CC} -g -o main main.o str_dgraph.o libfdr/libfdr.a
main.o: main.c str_dgraph.h
	${CC} ${CFLAGS} main.c
jrb_graph.o: str_dgraph.c str_dgraph.h
	${CC} ${CFLAGS} jrb_dgraph.c
clean:
	rm -f *.o *_
