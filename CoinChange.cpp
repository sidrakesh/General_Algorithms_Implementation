#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<cstdio>

#define MAXTOTAL 10000

using namespace std;

long long nway[MAXTOTAL+1];


int main()
{
   int i,t,j,n,v,c;
	long long coin[60];
	
	scanf("%d",&t);
	
	while(t--)
	{
	scanf("%d%d%d",&C,&s,&k)
	coin[0] = 1;
	for(i=1;coin[i-1]*C<=10e18;i++)   
   		coin[i] = coin[i-1]*C;
   v = 5;
   nway[0] = 1;
   
   for (i=0; i<v; i++) 
   {
      c = coin[i];
      
      for (j=c; j<=n; j++)
         nway[j] += nway[j-c];
   }
   
   printf("%lld\n",nway[n]);
}
