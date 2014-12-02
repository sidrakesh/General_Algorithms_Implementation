#include <cstdio>

int main()
{
	int n,m,k,i,j,t;
	int arr[11][11];
	
	scanf("%d",&t);
	
	while(t--) {
		scanf("%d%d%d",&n,&m,&k);
		
		arr[n][m] = 0;
		for(i=n-1;i>=0;i--)
			arr[i][m] = arr[i+1][m]+1;
		
		for(i=m-1;i>=0;i--)
			arr[n][i] = arr[n][i+1]+1;
			
		for(i=n-1;i>=0;i--)
			for(j=m-1;j>=0;j--)
				arr[i][j] = max(arr[i+1][j],arr[i][j+1])+1;
				
		
	}
}
