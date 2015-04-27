/*
ID: saitorl1
LANG: C
TASK: ride
*/
#include <stdio.h>
#include <string.h>

int main()
{
	FILE* fin   = fopen("ride.in", "r");
	FILE* fout  = fopen("ride.out", "w");
	
	char comet_name[7];
	char group_name[7];
	
	int compet_num = 1;
	int group_num  = 1;
	
	fscanf(fin, "%s", comet_name);
	fscanf(fin, "%s", group_name);
	
	int compet_len = strlen(comet_name);
	int group_len  = strlen(group_name);
	
	int i;
	for(i=0; i<compet_len; ++i)
		compet_num *= comet_name[i]-'A'+1;
	
	for(i=0; i<group_len; ++i)
		group_num *= group_name[i]-'A'+1;
		
		
	if( (compet_num%47) ==  (group_num%47) )
		fprintf(fout, "GO\n");
	else
		fprintf(fout, "STAY\n");	
	
	return 0;
}
