/*
ID: saitorl1
LANG: C
TASK: beads
*/
#include <stdio.h>
#include <stdlib.h>

char* necklace;
char* leftHalf;
char* rightHalf;
int num;

// Reverse right
void setLeft()
{
	int i;
	for(i=0; i<num; i++)
		leftHalf[i] = rightHalf[num-1-i];
}

// r = [cPnt ~ num-1] + [0 ~ cPnt-1]
void setRight(int cPnt)
{
	int i, j;
	if(cPnt>num || cPnt<0){
		printf("cPnt out of range!\n");
		return;
	}
	
	for(i=cPnt, j=0; i<num; i++, j++) 
		rightHalf[j] = necklace[i];
	
	for(i=0, j; i<cPnt; i++, j++) 
		rightHalf[j] = necklace[i];
}

int cout_beads(char* lace, int lim)
{
	/* Check right */
	char currentColor = 'w';
	int count = 0;
	
	// Find first color
	int i;
	for(i=0; i<num-lim ; ++i) {
		if(lace[i] != 'w') {
			currentColor = lace[i]; break;
		}
	}
	//printf("color = %c\n", currentColor);
	for(i=0; i<num-lim ; ++i) {
		if(lace[i]==currentColor || lace[i]=='w')
			++count;
		else
			break;
	}
	return count;
}

int analyze()
{
	int cutPnt;
	/* Check right and left*/
	int rCount = 0;
	int lCount = 0;
	
	
	// Check all cut point
	for(cutPnt=0; cutPnt<num; cutPnt++) {
		setRight(cutPnt);
		setLeft();
		
		/* Check right and left*/
		int r_temp = cout_beads(rightHalf, 0);
		int l_temp = cout_beads(leftHalf, r_temp);
		
		//printf("lc=%d, rc=%d\n", r_temp, l_temp);
		if( (r_temp+l_temp) > (rCount+lCount) ) {
			rCount = r_temp;
			lCount = l_temp;
		}
	}
	
	if( (rCount+lCount) > num )
		return (rCount>lCount)? rCount : lCount;	// Return max
	else
		return rCount+lCount;						// Return sum
}

int main()
{
	FILE* fin  = fopen("beads.in", "r");
	FILE* fout = fopen("beads.out", "w");
	
	while( fscanf(fin, "%d", &num) != EOF ) {
		necklace = (char*) malloc(num*sizeof(char));
		leftHalf = (char*) malloc(num*sizeof(char));
		rightHalf = (char*) malloc(num*sizeof(char));
		
		fscanf(fin, "%s", necklace);
		int ans = analyze();
		fprintf(fout, "%d\n", ans);
		
		free(necklace);
		free(leftHalf);
		free(rightHalf);
	}
	return 0;
}
