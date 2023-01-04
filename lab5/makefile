all: compilation

object:
	gcc -fPIC -c realization1.c
	gcc -fPIC -c realization2.c

libraries: object
	gcc -shared -o libdynamic1.so realization1.o -lm
	gcc -shared -o libdynamic2.so realization2.o -lm

compilation: libraries
	gcc static.c -L. -ldynamic1 -lm -o static 
	gcc dynamic.c -o dynamic -lm -ldl 

clean:
	rm *.o *.so dynamic static