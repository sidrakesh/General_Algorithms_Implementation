#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>

using namespace std;

int main()
{
   string a,b;
   a = "anarchist";
   b = "arc";
   
   string::iterator it;
   
   it = search(a.begin(),a.end(),b.begin(),b.end());
   
   if(it!=a.end())
   cout<<"found";

}
