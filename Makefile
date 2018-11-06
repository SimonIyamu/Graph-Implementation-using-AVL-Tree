mygraph : main.o BankImplementation.o menu.o
	gcc main.o BankImplementation.o menu.o -o mygraph -g

main.o : main.c menu.h BankInterface.h BankTypes.h
	gcc -c main.c

menu.o : menu.c menu.h BankInterface.h BankTypes.h
	gcc -c menu.c

BankImplementation.o : BankImplementation.c BankInterface.h BankTypes.h
	gcc -c BankImplementation.c -g

clean:
	rm mygraph main.o BankImplementation.o menu.o

