#include <stdio.h>
#include <stdlib.h>
#include "board.h"


//prototypes
Board* update_board(Board *);
char checkNorth(char *, int, int, int, int);
char checkSouth(char *, int, int, int, int);
char checkEast(char *, int, int, int, int);
char checkWest(char *, int, int, int, int);
char checkNorthW(char *, int, int, int, int);
char checkNorthE(char *, int, int, int, int);
char checkSouthW(char *, int, int, int, int);
char checkSouthE(char *, int, int, int, int);
int countWhite(char, char, char, char, char, char, char, char);
int countBlue(char, char, char, char, char, char, char, char);


//A function that takes the current board state and returns a pointer to the new Board after 1 timestep.
Board * update_board(Board *b) {
	//initializing the board pointer, instance variables
	Board *board = (Board *) malloc(sizeof(Board));
	board->grid = (char *) malloc(sizeof(char)*(b->gridSize));
	board->nrows = b->nrows;
	board->ncols = b->ncols;
	board->gridSize = (board->nrows)*(board->ncols);
	
	//neighbor categories
	int liveNbrs = 0; 
	int blueNbrs = 0;
	int whiteNbrs = 0;

	//chars for each neighbor's content
	char north, south, east, west, nw, ne, sw, se;


	//check the neighbors
	for(int r = 0; r < board->nrows; r++){
		for(int c = 0; c < board->ncols; c++){
			//set current square's neighbor letters
			north = checkNorth(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			south = checkSouth(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			east = checkEast(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			west = checkWest(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			nw = checkNorthW(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			ne = checkNorthE(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			sw = checkSouthW(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			se = checkSouthE(b->grid+(r*(board->ncols)+c), r, c, board->nrows, board->ncols);
			
			//use neighbors to calculate how many white, blue, alive total
			whiteNbrs = countWhite(north, south, east, west, nw, ne, sw, se);
			blueNbrs = countBlue(north, south, east, west, nw, ne, sw, se);
			liveNbrs = whiteNbrs + blueNbrs;

			//birth
			if(liveNbrs == 3 && *(b->grid+r*(board->ncols)+c) == 'x'){
				if(blueNbrs > whiteNbrs){
					*(board->grid + r*(board->ncols) + c) = 'b';
				}else if(blueNbrs < whiteNbrs){
					*(board->grid + r*(board->ncols) + c) = 'w';
				}
			//no change
			}else if(liveNbrs == 3 || liveNbrs == 2){
				*(board->grid + r*(board->ncols) + c) = *(b->grid + r*(board->ncols) + c);
			//death
			}else if(liveNbrs <= 1 || liveNbrs > 3){
				*(board->grid + r*(board->ncols) + c) = 'x';
			}
		}
	}
	//freeing old board
	free(b->grid);
	free(b);
	return board;
}

//methods to check neighboring squares
char checkNorth(char *startSquare, int r, int c, int nr, int nc){
	char np;
	if(r == 0){
		np = *(startSquare+(nr-1)*nc);
	}
	else{
		np = *(startSquare - nc);
	}
	return np;
}

char checkSouth(char *startSquare, int r, int c, int nr, int nc){
	char np;
	if(r == (nr-1)){
		np = *(startSquare-(nc)*(nr-1));
	}
	else{
		np = *(startSquare + nc);
	}
	return np;
}

char checkEast(char *startSquare, int r, int c, int nr, int nc){
	char np;
	if(c == (nc-1)){
	       np = *(startSquare - (nc-1));
	}
	else{
		np = *(startSquare + 1);
	}
	return np;
}	

char checkWest(char *startSquare, int r, int c, int nr, int nc){
	char np;
	if(c == 0){
		np = *(startSquare + (nc-1));
	}
	else{
		np= *(startSquare - 1);
	}
	return np;
}

char checkNorthW(char *startSquare, int r, int c, int nr, int nc){
	char np;
	if(r == 0 && c == 0){
		np = *(startSquare+nr*nc - 1);
	}
	else if(r != 0 && c == 0){
		np = *(startSquare-1);
	}
	else if(r == 0 && c!=0){
		np = *(startSquare - 1 + (nr-1)*nc);
	}
	else{
		np = *(startSquare - nc-1);
	}
	return np;
}

char checkNorthE(char *startSquare, int r, int c, int nr, int nc){
	char np;
	if(r == 0 && c == (nc-1)){
		np = *(startSquare-(nc-1)+(nr-1)*nc);
	}
	else if(r != 0 && c == (nc-1)){
		np = *(startSquare -(nc-1)-nc);
		
	}
	else if(r == 0 && c != (nc-1)){
		np = *(startSquare + 1+ nc*(nr-1));
	}
	else{
		np = *(startSquare - nc+1);
	}
	return np;
}

char checkSouthW(char *startSquare, int r, int c, int nr, int nc){
	char np; 
	if(r == (nr-1) && c == 0){
		np = *(startSquare + (nc-1) - (nc*(nr-1)));
	}
	else if(r != (nr-1) && c == 0){
		np = *(startSquare + nc+ (nc -1));
	}
	else if(r == (nr-1) && c != 0){
		np = *(startSquare -(nr-1)*nc -1);
	}
	else{
		np = *(startSquare + nc-1);
	}
	return np;
}

char checkSouthE(char *startSquare, int r, int c, int nr, int nc){
	char np;
	if(r == (nr-1) && c == (nc-1)){
		np = *(startSquare - (nc-1) - (nr-1)*nc);
	}
	else if(r != (nr-1) && c == (nc-1)){
		np = *(startSquare + 1);
	}
	else if(r == (nr-1) && c != (nc-1)){
		np = *(startSquare + 1 - (nr-1)*nc);
	}
	else{
		np = *(startSquare + nc +1);
	}
	return np;
}

//methods to total the color of neighboring tiles
int countWhite(char n, char s, char e, char w, char ne, char nw, char se, char sw) {
	int tot = 0;
	if(n == 'w'){
		tot++;
	}
	if(s == 'w'){
		tot++;
	}
	if(e == 'w'){
		tot++;
	}
	if(w == 'w'){
		tot++;
	}
	if(ne == 'w'){
		tot++;
	}
	if(nw == 'w'){
		tot++;
	}
	if(se == 'w'){
		tot++;
	}
	if(sw == 'w'){
		tot++;
	}
	return tot;
}

int countBlue(char n, char s, char e, char w, char ne, char nw, char se, char sw) {
	int tot = 0;
	if(n == 'b'){
		tot++;
	}
	if(s == 'b'){
		tot++;
	}
	if(e == 'b'){
		tot++;
	}
	if(w == 'b'){
		tot++;
	}
	if(ne == 'b'){
		tot++;
	}
	if(nw == 'b'){
		tot++;
	}
	if(se == 'b'){
		tot++;
	}
	if(sw == 'b'){
		tot++;
	}
	return tot;
}
