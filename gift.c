/*
ID: Saitor Phrasa [saitorl1]
LANG: C
TASK: gift1
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct player{
	char name[14];
	int  initial_money_value;
	int  final_money_value;
}player_t;

int np;
player_t* givers;

void set_player_initial_money(char* name, int money)
{
	int i;
	
	for(i=0; i<np; ++i)
	{
		if(strcmp(name, givers[i].name) == 0)
			givers[i].initial_money_value = money;
	}
}

void give_player_money(char* name, int money)
{
	int i;
	
	for(i=0; i<np; ++i)
	{
		if(strcmp(name, givers[i].name) == 0)
			givers[i].final_money_value += money;
	}
}

int main()
{
	FILE* fin   = fopen("gift1.in", "r");
	FILE* fout  = fopen("gift1.out", "w");
	
	int i;
	char giver_name[14];
	
	fscanf(fin, "%d", &np);
	
	givers = (player_t*) malloc(sizeof(player_t)*np);
	
	// initialize
	for(i=0 ; i<np ; ++i)
	{
		fscanf(fin, "%s", givers[i].name);
		givers[i].initial_money_value = 0;
		givers[i].final_money_value = 0;
	}
	
	// the person who will be giving gifts
	while(fscanf(fin, "%s", giver_name) != EOF)
	{
		int initial_money;
		int remain_money;
		int divide_money;
		int divider;
		char receiver_name[14];
		
		fscanf(fin, "%d %d", &initial_money, &divider);
		if(divider != 0) 
		{
		
			divide_money = initial_money/divider;
			remain_money = initial_money%divider;
			
			// Giver set initial money
			set_player_initial_money(giver_name, initial_money);
			
			// Give other player money as gift
			for(i=0 ; i<divider ; ++i)
			{
				fscanf(fin, "%s", receiver_name);
				give_player_money(receiver_name, divide_money);
			}
			
			// Giver get remain money
			give_player_money(giver_name, remain_money);
		}
	}
	
	// Output solution
	for(i=0; i<np; ++i)
	{	
		fprintf(fout, "%s %d\n", givers[i].name, givers[i].final_money_value - givers[i].initial_money_value);
	}
	
	return 0;
}
