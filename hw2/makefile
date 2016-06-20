CC = g++
CFLAGS = -g -Wall

all: main main2 main3 postfix

llistdbl.o: llistdbl.cpp llistdbl.h
	$(CC) $(CFLAGS) -c llistdbl.cpp -o llistdbl.o

main: main.cpp llistdbl.o
	$(CC) $(CFLAGS) main.cpp llistdbl.o -o main

alistint.o: alistint.cpp alistint.h
	$(CC) $(CFLAGS) -c alistint.cpp -o alistint.o

main2: main2.cpp alistint.o
	$(CC) $(CFLAGS) main2.cpp alistint.o -o main2

stackdbl.o: stackdbl.cpp stackdbl.h
	$(CC) $(CFLAGS) -c stackdbl.cpp -o stackdbl.o

main3: main.cpp stackdbl.o llistdbl.o
	$(CC) $(CFLAGS) main3.cpp stackdbl.o llistdbl.o -o main3

postfix: postfix.cpp stackdbl.o llistdbl.o
	$(CC) $(CFLAGS) postfix.cpp stackdbl.o llistdbl.o -o postfix

clean:
	rm -f main *.o
	rm -f main2 *.o
	rm -f main3 *.o
	rm -f postfix *.o