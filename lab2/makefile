all: build

build: parent child

parent: parent.o
	gcc $^ -o $@

child: child.o
	gcc $^ -o $@

%.o: %.c 
	gcc -c $^ -o $@

clean: 
	rm parent child *.o