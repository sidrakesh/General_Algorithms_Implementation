#include <iostream>
#include <cstdio>
#include <stack>
using namespace std;

typedef unsigned int uint_t;

// this function returns next higher number with same number of set bits as x.
uint_t snoob(uint_t x)
{

	uint_t rightOne;
	uint_t nextHigherOneBit;
	uint_t rightOnesPattern;

	uint_t next = 0;

	if(x)
	{
		// right most set bit
		rightOne = x & -(signed)x;

		// reset the pattern and set next higher bit
		// left part of x will be here
		nextHigherOneBit = x + rightOne;

		// nextHigherOneBit is now part [D] of the above explanation.

		// isolate the pattern
		rightOnesPattern = x ^ nextHigherOneBit;

		// right adjust pattern
		rightOnesPattern = (rightOnesPattern)/rightOne;

		// correction factor
		rightOnesPattern >>= 2;

		// rightOnesPattern is now part [A] of the above explanation.

		// integrate new pattern (Add [D] and [A])
		next = nextHigherOneBit | rightOnesPattern;
	}

	return next;
}

int main()
{
	int n,t,i,j,m,k;

	scanf("%d",&t);

	while(t--) {
		scanf("%d%d%d",&n,&m,&k);

		int num = 0;
		if(m>=1) {
			num = 1;
		}
		if(m>1) {
			for(i=0;i<m-1;i++) {
				num+=1<<(i+1);
			}
		}

	//printf("%d\n",num);

		for(i=0;i<k;i++)
			num = snoob(num);

		//printf("%d\n",num);

		int cnt=0;
		stack<char> ans;
			
		while(num>0) {
			if(num%2==0) {
				ans.push('H');
				cnt++;
			}
			else {
				ans.push('V');
			}
			
			num = num/2;
		}
		
		for(i=0;i<n-cnt;i++) {
			printf("H");
		}
		
		while(!ans.empty()) {
			printf("%c",ans.top());
			ans.pop();
		}
		printf("\n");
	}
}
