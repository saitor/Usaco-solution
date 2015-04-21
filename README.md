/*
ID: saitorl1
LANG: C
TASK: barn1
*/

/*=============================================================
 * Goal:
 * calculate the minimum number of stalls that must be blocked 
 * in order to block all the stalls that have cows in them.
 * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/*------------------------
 * Define board structure
 * it contains the start 
 * and end of board
 * */
typedef struct{
	int s, e;
}board_t;

/*-----------------------------------------------
 * Define barn structure
 * maxBoard: maximum of boards can be purchased
 * nStall: total number of stalls
 * nCow: number of cows in the stalls
 * stall[nCow]: occupied stalls
 * 
 * ps: a stall can only have one cow :)
 * */
typedef struct{
	int maxBoard, nStall, nCow;
	int *stall;
}barn_t;

/*-----------------------
 * Swap array procedure
 * */
void swap(int* a, int* b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}


/*--------------------------------------------------
 * Bubble sort procedure
 * Sort array from small to large
 * */
 void bubble_sort(int* array, int num)
 {
	int i, j;
	
	for(i=num; i>1; i--) // every time check n-1 farmers
		for(j=0; j<i-1; j++) {
			if(array[j] > array[j+1])
				swap(&array[j], &array[j+1]);
		}
 }

/*------------------------------
 * Read burn data by file
 * 
 * input:  file pointer
 * output: burn struct pointer
 * */
barn_t* read_burn(FILE* fp)
{
	barn_t* barn;
	int i;
	
	assert(fp != NULL);
	
	// Alloc barn struct
	barn = (barn_t*) malloc(sizeof(barn_t));
	
	// Read M, S, and C
	fscanf(fp, "%d %d %d", &(barn->maxBoard), 
			&(barn->nStall), &(barn->nCow));
	
	// Alloc stall struct: stall[nCow]
	barn->stall = (int*) malloc(sizeof(int)*(barn->nCow));
	for(i=0; i<(barn->nCow); i++) 
		fscanf( fp, "%d", &(barn->stall[i]) );
		
	bubble_sort(barn->stall, barn->nCow);
	
	assert(barn != NULL);
	return barn;
}

/*------------------------------
 * Write to answer to burn file
 * simply print int ans to file
 * */
void write_burn(FILE* fp, int ans)
{
	assert(fp != NULL);
	fprintf(fp, "%d\n", ans);
}

/*------------------------------------------
 * Return the max gap positon of int array
 * set the max gap = 0, after returned
 * 
 * EX: gap [8 14]
 * gap postion is 8's (index) position 
 * in array.
 * */
int find_max_gap(int* gap, int num)
{
	int max, mPos;
	int i;
	
	max = -1;
	for(i=0; i<num; i++) {
		if(max<gap[i]){
			max = gap[i];
			mPos = i;
		}
	}
	
	gap[mPos] = 0;	// To find next max gap, we set current to 0
	return mPos;
}

/*---------------------------------------------------------------------
 * compute the minimum number of stalls that must be blocked 
 * in order to block all the stalls that have cows in them.
 * 
 * test data is:
 * 4 50 18 	(maxBoard, nStall, nCow)
 * 3 4 6 8 14 15 16 17 21 25 26 27 30 31 40 41 42 43
 * 
 * By Greedy Algo.
 * ideal minimun of stall is nCow, so if we have enough boards
 * (maxBoard >= nCow), just return nCow
 * btw. if all stalls have a cow (nStall == nCow), return nCow
 * and we just use one board.
 * 
 * but if we dont have enough board, our covers must have empty stalls
 * such as [3 4 6 8], 7 is empty
 * to reduce empty stall, we have to use as much boards as we can
 * so we split them four parts(maxBoard)
 * [3-8], [14-21], [25-31], [40-43]
 * 
 * Method:
 * find all empty stalls from large to small and split them.
 * */
 int comp_min_stalls(barn_t* barn)
 {
	 int ans;
	 int *gap; // the gap between each stalls
	 board_t *boardGap;
	 int hBoard; // head of board
	 int empty;
	 int i;
	 
	 assert(barn != NULL);
	 ans = 0; // initial
	 
	 // We have enough board
	 if(barn->maxBoard >= barn->nCow)
		return barn->nCow;
	 
	 // Alloc and compute gap
	 gap = (int*) malloc(sizeof(int) * (barn->nCow -1) );
	 for(i=0; i<(barn->nCow -1); i++)
		gap[i] = barn->stall[i+1] - barn->stall[i];
		
	 // Split stalls by large gap
	 boardGap = (board_t*) malloc(sizeof(board_t) * (barn->maxBoard-1));
	 for(i=0; i< barn->maxBoard-1; i++) {
		boardGap[i].s = find_max_gap(gap, (barn->nCow -1));
		boardGap[i].e = boardGap[i].s + 1;
	 }
	 
	 empty = 0;
	 for(i=0; i< barn->maxBoard-1; i++) {
		empty += (barn->stall[boardGap[i].e] - barn->stall[boardGap[i].s])-1;
	 }

	 ans = barn->stall[barn->nCow-1]-barn->stall[0]+1 - empty;
	 
	 // Compute finish, free space
	 free(barn->stall);
	 free(barn);
	 free(gap);
	 free(boardGap);
	 
	 return ans;
 }

int main(int argc, char **argv)
{
	FILE *fin, *fout;
	
	barn_t* mBarn;
	
	fin  = fopen("barn1.in", "r");
	fout = fopen("barn1.out", "w");
	
	assert(fin != NULL && fout !=NULL);
	mBarn = read_burn(fin);
	write_burn(fout, comp_min_stalls(mBarn));
	
	return 0;
}
