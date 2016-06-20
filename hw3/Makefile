CC = g++
CFLAGS = -g -Wall
BIN_DIR = bin

all: copytest settest pgindex 

$(BIN_DIR)/llistint.o: $(BIN_DIR)/.dirstamp llistint.cpp llistint.h 
	$(CC) $(CFLAGS) -c llistint.cpp -o $(BIN_DIR)/llistint.o

copytest: $(BIN_DIR)/.dirstamp copytest.cpp $(BIN_DIR)/llistint.o
	$(CC) $(CFLAGS) copytest.cpp $(BIN_DIR)/llistint.o -o copytest

$(BIN_DIR)/setint.o: $(BIN_DIR)/.dirstamp setint.cpp setint.h
	$(CC) $(CFLAGS) -c setint.cpp -o $(BIN_DIR)/setint.o

settest: $(BIN_DIR)/.dirstamp settest.cpp $(BIN_DIR)/setint.o $(BIN_DIR)/llistint.o
	$(CC) $(CFLAGS) settest.cpp $(BIN_DIR)/setint.o $(BIN_DIR)/llistint.o -o settest

pgindex: $(BIN_DIR)/.dirstamp pgindex.cpp $(BIN_DIR)/setint.o $(BIN_DIR)/llistint.o
	$(CC) $(CFLAGS) pgindex.cpp $(BIN_DIR)/setint.o $(BIN_DIR)/llistint.o -o pgindex

clean:
	rm -f copytest $(BIN_DIR)/*.o
	rm -f settest $(BIN_DIR)/*.o
	rm -f pgindex $(BIN_DIR)/*.o

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp