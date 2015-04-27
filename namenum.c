/*
ID: saitorl1
LANG: C
TASK: namenum
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LEN 12

char* dictBuf;
long  dictSize;

char alpha2Num(char alpha)
{
	switch(alpha){
		case 'A':
		case 'B':
		case 'C':
			return '2';
		case 'D':
		case 'E':
		case 'F':
			return '3';
		case 'G':
		case 'H':
		case 'I':
			return '4';
		case 'J':
		case 'K':
		case 'L':
			return '5';
		case 'M':
		case 'N':
		case 'O':
			return '6';
		case 'P':
		case 'R':
		case 'S':
			return '7';
		case 'T':
		case 'U':
		case 'V':
			return '8';
		case 'W':
		case 'X':
		case 'Y':
			return '9';
		default:
			return '0';
	}
}

void analyze(FILE* fout, char* num)
{
	char name[LEN];
	int nameLen=0;
	int nLen = strlen(num);
	
	
	int i, j;
	int isValid = 0;
	int isNone = 1;
	for(i=0; i<dictSize; i+=(nameLen+1)) {	// Read all name in dict
		sscanf(&dictBuf[i], "%s", name);
		nameLen = strlen(name);
		
		 // First check: must have same length
		isValid = (nLen==nameLen);
		
		// Check all char is valid
		for(j=0; j<nameLen && isValid; j++)
			if( num[j] != alpha2Num(dictBuf[i+j]) ) isValid = 0;
		
		// Out valid name
		if(isValid) {
			fprintf(fout, "%s\n", name);
			isNone=0;
		}
	}
	
	// None name out, print NONE
	if(isNone)
		fprintf(fout, "NONE\n");
}

int main()
{
	FILE* fin 	= fopen("namenum.in", "r");
	FILE* fdict = fopen("dict.txt", "r");
	FILE* fout	= fopen("namenum.out", "w");
	unsigned int readSize;
	char num[LEN];
	
	assert(fin!=NULL && fdict!=NULL && fout != NULL);
	
	// Obtain file size
	fseek(fdict, 0, SEEK_END);
	dictSize = ftell(fdict);
	rewind(fdict);
	
	// Allocate memory to contain the whole file
	dictBuf = (char*) malloc(sizeof(char)*dictSize);
	assert(dictBuf != NULL);
	
	// Copy the file into the buffer
	readSize = fread(dictBuf, 1, dictSize, fdict);
	assert(readSize == dictSize);
	
	while(fscanf(fin,"%s", num)!=EOF) {
		analyze(fout, num);
	}
	
	free(dictBuf);
	
	fclose(fin);
	fclose(fdict);
	fclose(fout);
	return 0;
}
