#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

int MaxWeight(int Values[],int Weights[],int n,int MW)  //Values is array of Values, Weights is array of weights, n is number
                                                        //of weights, MW is max weight
{
    int C[n+1][MW+1];
    int i,w;
    
    for (i=0;i<=n ;i++) C[i][0] = 0;
    for (w=0;w<=MW;w++) C[0][w] = 0;
    
    for (i=1;i<=n;i++)
    for (w=1;w<=MW;w++) 
    {
        if (Weights[i] > w)
           C[i][w] = C[i-1][w];
        else
           C[i][w] = max(C[i-1][w] , C[i-1][w-Weights[i]]+Values[i]);
    }
    
    return C[n][MW];
}

int main()
{}
