/*
ID: saitorl1
LANG: C
TASK: crypt1
*/

/*=====================================================
 * Write a program that will find all solutions to 
 * the cryptarithm above for any subset of supplied 
 * non-zero single-digits.
 * 
 * 		a b c 
 * X	  d e
 * ------------
 *    * * * * 
 *  * * * * 
 * ------------
 *  @ @ @ @ @
 * 
 * */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int n;

// The number data
int* num; // storage

/*-------------------------------
 * Procedure to read crypt1 file
 * 
 * input: file point 
 * */
 void read_crypt(FILE* fp)
 {
	 int i;
	 
	 assert(fp != NULL);
	 
	 // Check data size is 5 or not
	 fscanf(fp, "%d", &n);
	 
	 num = (int*) malloc(sizeof(int)*n);
	 assert(num!=NULL);
	 
	 // Read in a, b, c, d, e
	 for(i=0; i<n; i++) {
		fscanf(fp, "%d", &num[i]);
		//printf("num[%d] == %d\n", i, num[i]);
	}
 }
 
 /*--------------------------------
  * Procedure to write crypt1 file
  * 
  * input: file point, int ans
  * */
  void write_crypt(FILE* fp, int answer)
  {
	fprintf(fp, "%d\n", answer);
  }

/*----------------------------------------
 * Procedure to check a num valid or not
 * 
 * if valid return 1, otherwise return 0
 * Check every digit is member or num[]
 * */
 int is_num_valid(int un)
 {
	 int digit, i;
	 int flag;
	 
	 assert( un != 0 );
	 
	 // Check every digit is member of num[]
	 while(un != 0) {
		digit = un % 10;
	
		flag = 0;	// init flag
		// Check digit is member or not
		for(i=0; i<n; i++) {
			if(digit == num[i]) {
				flag = 1;
				break;
			}
			//printf("digit == %d, num[%d] = %d, flag == %d\n", digit, i,  num[i], flag);
		}
		// this digit invalid
		if(flag == 0) break;
		
		// go to next digit
		un /= 10;
	}
	
	return flag;
 }

/*------------------------------------------------
 * Procedure to solve this problem
 * return how many valid answers
 * 
 * 1. set up numbers: abc, de
 * here are 5 loops to compute
 * 
 * 2. Check partProduct valid or not
 * all digits must be the member of num[]
 * 
 * 3. Check sum vaild or not
 * head digit cant be 0
 * 
 * The partial products must be three digits long!!
 * */
int comp_crypt()
{
	int abc, de;
	int i, j, k, l, m;
	int partProduct1;	// e*abc
	int partProduct2;	// d*abc
	int sum;			// p1 + 10*p2
	int ans = 0;
	
	//n=1;
	// Set up numbers
	for(i=0; i<n; i++)
	for(j=0; j<n; j++)
	for(k=0; k<n; k++)
	for(l=0; l<n; l++)
	for(m=0; m<n; m++) {
		
		// Set numbers
		abc = num[i]*100 + num[j]*10 + num[k];
		de  = num[l]*10 + num[m];
		
		partProduct1 = num[m]*abc;
		partProduct2 = num[l]*abc;
		sum = partProduct1 + partProduct2*10;
		
		// The partial products must be three digits long
		if( partProduct1 > 999 || partProduct2 > 999 )
			continue;
		
		if( is_num_valid(partProduct1) &&
			is_num_valid(partProduct2) &&
			is_num_valid(sum) )
			ans++;
	}

	return ans;
}


// Main procedure
int main(int argc, char* argv[])
{
	FILE* fin 	= fopen("crypt1.in", "r");
	FILE* fout	= fopen("crypt1.out", "w");
	
	// Check the file exist or not
	assert( fin != NULL && fout != NULL );
	
	read_crypt(fin);
	write_crypt(fout, comp_crypt());
	
	return 0;
}
