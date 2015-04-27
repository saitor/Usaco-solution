/*
ID: saitorl1
LANG: C
TASK: milk
*/

#include <stdio.h>
#include <stdlib.h>

//#define DEBUG

/*---Farmer data structure---*/
typedef struct{
	int price;
	int num;
}farmer_t;

/*---milk maker data structure---*/
typedef struct{
	int numMilk;	// the amount of milk they need, 
	int numFarm;	// and amount of their farmers
	
	farmer_t* farmer;	// their farmers
}milkMaker_t;

/*-----------------------
 * Swap farmer procedure
 * */
void swap(farmer_t* a, farmer_t* b)
{
	farmer_t temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

/*--------------------------------------------------
 * Bubble sort procedure
 * Sort farmer from cheap to expensive
 * */
 void bubble_sort(farmer_t* farmers, int num)
 {
	int i, j;
	
	for(i=num; i>1; i--) // every time check n-1 farmers
		for(j=0; j<i-1; j++) {
			if(farmers[j].price > farmers[j+1].price)
				swap(&farmers[j], &farmers[j+1]);
		}
 }
 
 /*------------------------------------
 * Procedure to read milk data
 * If sucessful return a milkMaker pointer
 * else return null
 */
milkMaker_t* read_milk(FILE* fp)
{
	milkMaker_t* mMaker;
	int i;
	
	if(!fp) {
		fprintf(stderr, "No milk file here!\n");
		return (0);
	}
	
	// Alloc milker space
	mMaker = (milkMaker_t*) malloc(sizeof(milkMaker_t));
	
	fscanf(fp, "%d%d", &(mMaker->numMilk), &(mMaker->numFarm));
	
	// Alloc farmer splace
	mMaker->farmer = (farmer_t*) malloc(sizeof(farmer_t)*(mMaker->numFarm));
	
	for(i=0; i<(mMaker->numFarm); i++)
		fscanf(fp, "%d%d", &(mMaker->farmer[i].price), &(mMaker->farmer[i].num));

#ifdef DEBUG
	fprintf(stderr, "%d\t%d\n", mMaker->numMilk, mMaker->numFarm);
	bubble_sort(mMaker->farmer, mMaker->numFarm);
	for(i=0; i<(mMaker->numFarm); i++)
		fprintf(stderr, "%d\t%d\n", (mMaker->farmer[i].price), (mMaker->farmer[i].num));
#endif
	return mMaker;
}

/*-----------------------------------------------------------------
 * Procedure to compute cheapest total cost
 * By Greedy Algo.
 * First, sort farmers for cheaper to expensive
 * Then, buy all cheap milk as we can, otherwise go to next farmer
 * btw if need milk < farmer's unit, didn't buy all of them!
 * just buy what we need :)
 * 
 * input:  milkMaker_t* maker
 * output: int totalCost;
 * */
 int cheapest_cost(milkMaker_t* maker)
 {
	int cost, numBuy, needMilk;
	int i;
	
	cost = numBuy = i = 0;	// initial
	
	// Sort farmers
	bubble_sort(maker->farmer, maker->numFarm);
	
	while(numBuy < (maker->numMilk)) {	// while not enough milk
		needMilk = (maker->numMilk) - numBuy;
		
		if(needMilk > maker->farmer[i].num) {
			numBuy += maker->farmer[i].num; // Buy all of them!
			cost += maker->farmer[i].num * maker->farmer[i].price;
		}
		else {
			numBuy += needMilk; // just buy what we need :)
			cost += needMilk * maker->farmer[i].price;
		}
		// go to the next farmer
		i++;
	}
	
	return cost;
 }

int main()
{
	FILE* fin 	= fopen("milk.in", "r");
	FILE* fout	= fopen("milk.out", "w");
	
	milkMaker_t* milkMaker;
	
	milkMaker = read_milk(fin);
	
	// write milk file
	fprintf(fout, "%d\n", cheapest_cost(milkMaker));
	
	return 0;
}
