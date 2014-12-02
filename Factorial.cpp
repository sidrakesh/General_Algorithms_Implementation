#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<cstdio>

using namespace std;

long long arr[20] = {0,2,8,192,645120,271729297,141149223,410729434,630603818,394218803,489659160,727701672,879270951,232996018,377274195,598017340,529365327,283153707,462357401,842252297};

long long Factorial(long long n,long long mod) 
{
    long long int i,result = 1;
    
	for (i=1; i<=n; i++)
	result = (result*i)%mod;
    
    return result;
}

int main()
{
	long long n,k,i,m;
	long long ans;
	for(i=1;i<20;i++)
	{
		n = 1<<i;
		m = 1<<(i-1);
		
		ans = Factorial(m-1,1000000009);
		ans = (n*ans)%1000000009;
		printf("%lld,",ans);
	}
}
