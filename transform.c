/*
ID: saitorl1
LANG: C
TASK: transform
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

// Function pointer
typedef void (*transFunc_t) (char* output, char* input, int n);

int is_equal(char* output, char* input, int n)
{
	int i, j;
	
	for(j=0; j<n; j++)
	for(i=0; i<n; i++)
		if(output[j*n+i] != input[j*n+i]) return 0;
	return 1;
}


// origin = j*n+i
// 90 = i*n+(n-1-j)
void rotate90(char* output, char* input, int n)
{
	int i, j;
	
	for(j=0; j<n; j++)
	for(i=0; i<n; i++)
		output[i*n+(n-1-j)] = input[j*n+i];
}

// origin = j*n+i
// 180 = (n-1-j)*n+(n-1-i)
void rotate180(char* output, char* input, int n)
{
	int i, j;
	
	for(j=0; j<n; j++)
	for(i=0; i<n; i++)
		output[(n-1-j)*n+(n-1-i)] = input[j*n+i];
}

// origin = j*n+i
// 270 = (n-1-i)*n+j
void rotate270(char* output, char* input, int n)
{
	int i, j;
	
	for(j=0; j<n; j++)
	for(i=0; i<n; i++)
		output[(n-1-i)*n+j] = input[j*n+i];
}

// origin = j*n+i
// reflect = j*n+(n-1-i)
void reflect(char* output, char* input, int n)
{
	int i, j;
	
	for(j=0; j<n; j++)
	for(i=0; i<n; i++)
		output[j*n+(n-1-i)] = input[j*n+i];
}

// Do method1 and then do mehtod2
void combin(char* output,char* input, int n, transFunc_t method1, transFunc_t method2)
{
	char* temp;
	int size = n*n;
	
	temp = (char*) malloc(sizeof(char)*size);
	
	method1(temp, input, n);
	method2(output, temp, n);
	
	free(temp);
}

void loadPattern(FILE* fin, char* buf, int n)
{
	char tC;
	int	count = 0;
	int size = n*n;
	while((tC=fgetc(fin)) && count<size) 
		if(tC!='\n') buf[count++] = tC;
}

void showPattern(char* buf,  int n)
{
	int i;
	puts("==========");
	for(i=0; i<n*n; ++i) {
		if(i%n==0 && i!=0) putchar('\n');
		printf("%c", buf[i]);
	}
	puts("\n==========\n");
}

int min(int a, int b)
{
	return (a<b) ? a:b;
}

int analyze(char* origin, char* transferred, int n)
{
	int result = 7;
	char* temp;
	int size = n*n;
	
	temp = (char*) malloc(sizeof(char)*size);
	
	
//	showPattern(origin, n);
//	showPattern(transferred, n);
	
	// #1: Rotate 90
	rotate90(temp, origin, n);
	if(is_equal(temp, transferred, n)) result = min(result, 1);
	
	rotate180(temp, origin, n);
	if(is_equal(temp, transferred, n)) result = min(result, 2);
	
	rotate270(temp, origin, n);
	if(is_equal(temp, transferred, n)) result = min(result, 3);
	
	reflect(temp, origin, n);
	if(is_equal(temp, transferred, n)) result = min(result, 4);
	
	combin(temp, origin, n, reflect,rotate90);
	if(is_equal(temp, transferred, n)) result = min(result, 5);
	
	combin(temp, origin, n, reflect,rotate180);
	if(is_equal(temp, transferred, n)) result = min(result, 5);
	
	combin(temp, origin, n, reflect, rotate270);
	if(is_equal(temp, transferred, n)) result = min(result, 5);
	
	// No change
	if(is_equal(origin, transferred, n)) result = min(result, 6);

	free(temp);
	return result;
}

int main()
{
	FILE* fin  = fopen("transform.in", "r");
	FILE* fout = fopen("transform.out", "w");
	
	int n;	// Matrix dimension
	int size;
	char* origin;
	char* transferred;
	
	assert(fin!=NULL && fout!=NULL);
	
	while(fscanf(fin, "%d", &n) != EOF) {
		size = n*n;
		origin = (char*) malloc(sizeof(char)*size);
		transferred = (char*) malloc(sizeof(char)*size);
		
		// Read transferred pattern
		loadPattern(fin, origin, n);
		
		// Read origin pattern
		loadPattern(fin, transferred, n);
		
//		printf("%d\n", analyze(origin, transferred, n) );
		fprintf(fout, "%d\n", analyze(origin, transferred, n) );
		
		free(origin);
		free(transferred);
	}
	fclose(fin);
	fclose(fout);
	return 0;
}
