all: main run

se_fichier.o : se_fichier.c
	gcc -c -fPIC se_fichier.c
	
build: se_fichier.o
	ar rcs libsef.a se_fichier.o
	
main: build
	gcc test.c -L. -lsef -o td2

run:
	./td2

clean:
	rm *.o
