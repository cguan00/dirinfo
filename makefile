all: dirinfo.o
	gcc -o dirTest dirinfo.o

main.o: dirinfo.c
	gcc -c dirinfo.c

run:
		./dirTest

clean:
	rm *.o
	rm *~
