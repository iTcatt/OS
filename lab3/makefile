CC = gcc

main: main.o
	$(CC) main.o -lpthread -o main

main.o: main.c 
	$(CC) -c main.c

clean:
	rm main *.o 