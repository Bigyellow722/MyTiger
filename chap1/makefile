a.out: main.o prog1.o slp.o util.o interpreter.o
	cc -g main.o prog1.o slp.o util.o interpreter.o

main.o: main.c slp.h util.h
	cc -g -c main.c

prog1.o: prog1.c slp.h util.h
	cc -g -c prog1.c

slp.o: slp.c slp.h util.h
	cc -g -c slp.c

util.o: util.c util.h
	cc -g -c util.c

interpreter.o: interpreter.c interpreter.h
	cc -g -c interpreter.c

clean: 
	rm -f a.out util.o prog1.o slp.o main.o interpreter.o
