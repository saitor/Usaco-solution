/*
ID: saitorl1
LANG: C
TASK: milk2
*/

#include <stdio.h>
#include <stdlib.h>

int num;

typedef struct timeBlock{
	int start;
	int end;
}tB_t;

tB_t*  current;

int combinLen = 0;


int max(int a, int b)
{
	return (a>b)? a:b;
}

int min(int a, int b)
{
	return (a<b)? a:b;
}

void swap(int* a, int* b)
{
	int temp;
	
	temp = *a;
	*a = *b;
	*b = temp;
}

void bsort()
{
	int i, j;
	
	for(i=num; i>1; i--)
	for(j=0; j<i-1; j++)
	{
		if(current[j].start>current[j+1].start) {
			swap(&current[j].start, &current[j+1].start);
			swap(&current[j].end, &current[j+1].end);
		}
	}
}

int isIntersect(int minS, int maxE, int cur)
{
	return (minS<=cur && cur<= maxE);
}

int continue_compute()
{
	int maxEnd = current[0].end;
	int minStart = current[0].start;
	int contin = 0;
	int i;
	
	for(i=0; i<num; i++) {
		if( isIntersect(minStart ,maxEnd, current[i].start) ) {
			maxEnd = max(maxEnd, current[i].end);
			minStart = min(minStart, current[i].start);
		} else {
			minStart = current[i].start;
			maxEnd = current[i].end;
		}
		int tempCon = maxEnd - minStart;
		contin = max(contin, tempCon);
	}
	return contin;
}

int idle_compute()
{
	int maxEnd = current[0].end;
	int idle = 0;
	int i;
	int tempIdle = 0;
	
	for(i=1; i<num; i++) {
		if( maxEnd < current[i].start )	// have a gap
			tempIdle = current[i].start - maxEnd;
		maxEnd = max(maxEnd, current[i].end);
		idle = max(idle, tempIdle);
	}
	return idle;
}

int main()
{
	FILE* fin = fopen("milk2.in", "r");
	FILE* fout = fopen("milk2.out", "w");
	
	if(fin==NULL) {
		printf("No file!\n");
		return -1;
	}
	
	while( fscanf(fin, "%d", &num) != EOF ) {
		current = (tB_t*) malloc(num*sizeof(tB_t));
		
		int i;
		for(i=0; i<num; i++)
			fscanf(fin, "%d%d", &current[i].start, &current[i].end);
			
		bsort();
		fprintf(fout, "%d %d\n", continue_compute(), idle_compute());
		
		free(current);
	}
	return 0;
}
