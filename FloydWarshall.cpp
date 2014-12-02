#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;


int dist[100][100];  // For some N

int floydwarshall(int N,int s,int e)
{ 
	int i, j, k;
	// Input data into dist, where dist[i][j] is the distance from i to j.

   	for ( k = 0; k < N; k++ )
    	for ( i = 0; i < N; i++ )
        	 for ( j = 0; j < N; j++ )
           		 dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );

	return dist[s][e];
}

int main()
{
	
}
