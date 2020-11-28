#ifndef BOARD_H
#define BOARD_H

typedef struct Board {
	char *grid;
	int nrows;
	int ncols;
	int gridSize; //rows * cols
} Board;

//prototype def
Board* update_board(Board *);

#endif
