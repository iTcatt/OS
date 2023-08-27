CC = gcc

all: main

main: main.o
	$(CC) $^ -lpthread -o $@

main.o: main.c 
	$(CC) -c $^ -o $@

clean:
	rm main *.o 