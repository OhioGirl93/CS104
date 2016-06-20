CC = g++
CFLAGS = -g -Wall

all: rectangles test

test: test.cpp bst.h rbbst.h
	$(CC) $(CFLAGS) test.cpp -o test

rectangles: rectangles.cpp bst.h rbbst.h
	$(CC) $(CFLAGS) rectangles.cpp -o rectangles



clean:
	rm -f rectangles *.o
	rm -f test *.o