#makefile

#Autores: RODRIGO CALDEIRA 106963
#		 HENRIQUE NOGUEIRA 107561

all: flip-flop

file.o: file.c flipflop.h types.h
	gcc -g -Wall -pedantic -ansi -Werror -c file.c

init.o: init.c flipflop.h types.h
	gcc -g -Wall -pedantic -ansi -Werror -c init.c

playMaking.o: playMaking.c flipflop.h types.h
	gcc -g -Wall -pedantic -ansi -Werror -c playMaking.c

screen.o: screen.c flipflop.h types.h
	gcc -g -Wall -pedantic -ansi -Werror -c screen.c

status.o: status.c flipflop.h types.h
	gcc -g -Wall -pedantic -ansi -Werror -c status.c

main.o: main.c flipflop.h types.h
	gcc -g -Wall -pedantic -ansi -Werror -c main.c

flip-flop: file.o init.o playMaking.o screen.o status.o main.o
	gcc -g -Wall -pedantic -ansi -Werror file.o init.o playMaking.o screen.o status.o main.o -o flip-flop

clean:
	rm main.o file.o init.o playMaking.o screen.o status.o flip-flop