/*
ID: saitorl1
LANG: C
TASK:friday
*/

#include <stdio.h>
#include <stdlib.h>


#define SUNDAY		0
#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THRISDAY	4
#define FRIDAY		5
#define SATURDAY	6


int main()
{
	FILE* fin  = fopen("friday.in", "r");
	FILE* fout = fopen("friday.out", "w");
	int n, i, year;
	int day_counter[7];
	
	fscanf(fin, "%d", &n);
	
	// Initialize
	for(i=0; i<7 ;++i)
		day_counter[i] = 0;
	
	/*****/
	int thirteenth_day = SATURDAY;
	day_counter[SATURDAY]++;
	
	int fab_day;
	for(year=1900; year<1900+n; ++year)
	{
		// Test leap
		fab_day = 28;
		if( (year%100)==0 )
		{
			if( (year%400)==0 )
				fab_day = 29;
		}
		else
		{
			if( (year%4)==0 )
				fab_day = 29;
		}
			
		// Calculate firday in every month
		thirteenth_day = (thirteenth_day+31)%7;		//1
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+fab_day)%7;//2
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+31)%7;		//3
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+30)%7;		//4
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+31)%7;		//5
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+30)%7;		//6
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+31)%7; 	//7
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+31)%7; 	//8
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+30)%7; 	//9
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+31)%7; 	//10
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+30)%7;		//11
		day_counter[thirteenth_day]++;
		
		thirteenth_day = (thirteenth_day+31)%7;		//12
		if(year != 1900+n-1)
			day_counter[thirteenth_day]++;
		
		
	}
	

	/*****/
	
	
	// Output
	//printf("%d ", day_counter[SATURDAY]);
	//printf("%d ", day_counter[SUNDAY]);
	//printf("%d ", day_counter[MONDAY]);
	//printf("%d ", day_counter[TUESDAY]);
	//printf("%d ", day_counter[WEDNESDAY]);
	//printf("%d ", day_counter[THRISDAY]);
	//printf("%d ", day_counter[FRIDAY]);
	
	fprintf(fout, "%d ", day_counter[SATURDAY]);
	fprintf(fout, "%d ", day_counter[SUNDAY]);
	fprintf(fout, "%d ", day_counter[MONDAY]);
	fprintf(fout, "%d ", day_counter[TUESDAY]);
	fprintf(fout, "%d ", day_counter[WEDNESDAY]);
	fprintf(fout, "%d ", day_counter[THRISDAY]);
	fprintf(fout, "%d\n", day_counter[FRIDAY]);
	
	return 0;
}

