#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include <cstdio>

using namespace std;

long long arr[100000000] = {0};

long long bigMod(long long b,long long p,long long m) 
{
     if (p == 0)
     {  
        return 1;
     }
     else if (p%2 == 0)
     {
     	if(p/2<50000000&&arr[p/2]!=0)
     	{
     		arr[p] = (arr[p/2]*arr[p/2])%m;
        	return arr[p];
        }
        else if(p/2<100000000&&arr[p/2!=0])
        {
			return (arr[p/2]*arr[p/2])%m;
		}
		else
		{
			arr[p] = (bigMod(b,p/2,m)*bigMod(b,p/2,m)) % m;
			return arr[p];
		}
     }
     else
     {
     	if(p>=100000000)
        	return ((b % m) * bigMod(b,p-1,m)) % m;
        else
        {
			arr[p] = ((b % m) * bigMod(b,p-1,m)) % m;
			return ((b % m) * bigMod(b,p-1,m)) % m;
		}
     }
}

int main()
{
	arr[0] = 1;
	cout<<bigMod(2,3,1000000007)<<"\n";
    cout<<bigMod(100,2,1000000007)<<"\n";
    cout<<bigMod(100,3,1000000007);

    getchar();
}
