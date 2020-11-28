all : conway.c board.c board.h
	gcc -Wall -o conway.out conway.c board.c board.h

clean :
	rm conway.out
