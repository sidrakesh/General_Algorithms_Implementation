#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

int GCD(int a,int b) 
{
    while (b > 0) 
    {
       a = a % b;
       a ^= b; b ^= a; a ^= b; 
    } 
    
    return a;
}

int LCM(int a, int b)
{
    return (a*b)/GCD(a,b);
}

int main()
{}
