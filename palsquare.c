/*
ID: saitorl1
LANG: C
TASK: palsquare
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void swap(char* a, char* b)
{
	char temp = *a;
	*a = *b;
	*b = temp;
}

void reverse(char str[], int length)
{
	int start = 0;
	int end   = length - 1;
	
	while(start < end) {
		swap(&str[start], &str[end]);
		start++;
		end--;
	}
}

// Implementation of itoa()
char* itoa(int num, char* str, int base)
{
	int i = 0;
	int isNegative = 0;
	
	// Handle 0 explicitely
	if(num==0) {
		str[i++] = '0';
		str[i] 	 = '\0';
		return str;
	}
	
	// Native numbers only handled with base 10
	if(num<0 && base==10) {
		isNegative = 1;
		num = -num;
	}
	// Process individual digits
	while(num!=0) {
		int rem = num % base;
		str[i++] = (rem > 9)? (rem-10) + 'A' : rem + '0';
		num /= base;
	}
	
	// If number is negative, append '-'
	if(isNegative) 
		str[i++] = '-';
		
	// Append string terminator
	str[i] = '\0';
	
	// Reverse the string
	reverse(str, i);
	
	return str;
}

int isPalin(char* str)
{
	int len = strlen(str);
	
	char* start= str;
	char* end  = str+len-1;
	
	for( ; start<end; start++, end--)
		if(*start != *end)	return 0;
		
	return 1;
}

int main()
{
	FILE* fin  = fopen("palsquare.in", "r");
	FILE* fout = fopen("palsquare.out", "w");
	int i, base;
	
	assert(fin!=NULL && fout!=NULL);
	
	while(fscanf(fin, "%d", &base)!=EOF) {
		for(i=1 ; i<= 300; ++i) {
			
			char num[101];
			char square[201];
			
			itoa(i, num, base);
			itoa(i*i, square, base);
			
			if(isPalin(square))
				fprintf(fout, "%s %s\n", num, square);
			
		}

	}
	fclose(fin);
	fclose(fout);
	return 0;
}
