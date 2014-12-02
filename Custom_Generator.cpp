#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <stdio.h>

using namespace std;

// run command: Custom_Generator "upto num" > "output file name"
// will create the required output file with last prime being the same or just greater prime than the given input number

int main(int argc, char* argv[])
{
	FILE* fp = fopen("primes.txt","r");

	long i,n = -1;
	printf("int arr[] = {");

	int N = atoi(argv[1]);

	for(i=1;n<N;i++)
	{
		fscanf(fp,"%ld",&n);

		if(n>=N)
			printf("%ld};",n);
		else
			printf("%ld,",n);
	}

	fclose(fp);
}
