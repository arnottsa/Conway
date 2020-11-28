#include <stdio.h>
#include <stdlib.h>
#include "board.h"

//prototype
int countColors(Board *b, char x);

int main(void) {
	int row, col, timesteps;
	char placeholder = 'p';

	//scanning from stdin
	scanf("%d %d\n", &row, &col);
	scanf("%d\n", &timesteps);

	//initializing the board from stdin (will be used even after it's updated, and still called "first")
	Board *first;
    first = (Board *) malloc(sizeof(Board));
	first->nrows = row;
	first->ncols = col;
	first->gridSize = row * col;
	first->grid = (char *) malloc(sizeof(char)*(first->gridSize));

	//assigning the proper letters
	for(int i = 0; i < first->gridSize; i++) {
		//scans in each char of the input board and a character after it, either a newline or space depending on row location of current char
		scanf("%c%c", first->grid+i, &placeholder);
		
	}
	
	//printing board
	//printf("\n");
	//for(int k = 0; k < first->gridSize; k++){
	//	printf("%c ", *(first->grid + k));
	//	if(k % first->ncols == 0 && k != 0){
	//		printf("\n");
	//	}
	//}


	//evolve board condition
	for(int j = 0; j < timesteps; j++) {
		first = update_board(first);
	}

	
	
	//variables to store counts of live tiles
	int white;
	int blue;

	white = countColors(first, 'w');
	blue = countColors(first, 'b');


	//printing the counts of white and blue squares
	printf("white: %d, blue: %d\n", white, blue); 

	//freeing malloced memory
	free(first->grid);
	free(first);
	return 0;
}


//count the number of (color) squares
int countColors(Board *b, char x) {
	int count = 0;
	char *curr = b->grid;
	for(int i = 0; i < b->gridSize; i++) {
		if(*(curr + i) == x) {
			count++;
		}
	}

	return count;
}
