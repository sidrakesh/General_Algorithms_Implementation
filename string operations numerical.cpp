#include<iostream>
#include<vector>
#include<cstring>
#include<algorithm>
#include<map>
#include<cstdlib>
using namespace std;

string reverse(string a)
{
    int i,size;
    size = a.size();
    char t;
    
    for(i=0;i<(size/2);i++)
    {
       t = a[i];
       a[i] = a[size-i-1];
       a[size-i-1] = t;
    }
    
    return a;
}

string Add(string a,string b)
{
    string Ans;
    
    a = reverse(a);
    b = reverse(b); 
    
    int aDig,bDig;
    int i,smallLen,bigLen,carry,sum;
    string smallString,bigString;
    
    smallString = (a.size()<b.size())?a:b;
    bigString = (a.size()>b.size())?a:b;

    carry = 0;
    
    for(i=0;i<smallString.size();i++)
    {
       aDig = (int)a[i]-48;
       bDig = (int)b[i]-48;
       
       sum = aDig+bDig+carry;
       Ans.push_back((char)(sum%10+48));
       carry = sum/10;
    }
    
    for(;i<bigString.size();i++)
    {
       sum = carry+(int)(bigString[i])-48;
       
       Ans.push_back((char)(sum%10+48));
       carry = sum/10;
    }
    
    if(carry!=0)
       Ans.push_back((char)(carry+48));
    
    return reverse(Ans);
}

string Subtract(string a,string b)
{
    string Ans;
    
    int sign=0,i;
    
    if(a.size()<b.size())
       sign = -1;
    else if(a.size()>b.size())
       sign = 1;
        
    if(sign==0)
    {
       for(i=0;i<a.size();i++)
       {
          if((int)a[i]>(int)b[i])
          {
            sign = 1;
            break;
          }
          else if((int)a[i]<(int)b[i])
          {
            sign = -1;
            break;
          }
       }
    }
    
    if(sign==0)
    {
       return "0";
    }
    
    a = reverse(a);
    b = reverse(b); 
    
    int smallDig,bigDig;
    int smallLen,bigLen,diff;
    string smallString,bigString;
    
    if(sign==1)
    {
       bigString = a;
       smallString = b;
    }
    else 
    {
       bigString = b;
       smallString = a;
    }
    
    for(i=0;i<smallString.size();i++)
    {
       smallDig = (int)smallString[i]-48;
       bigDig = (int)bigString[i]-48;
       
       if(bigDig<smallDig)
       {
          bigDig+=10;
          bigString[i+1]--;
       }
       diff = bigDig - smallDig;
       Ans.push_back((char)(diff+48));
    }
    
    for(;i<bigString.size();i++)
    {
       Ans.push_back(bigString[i]);
    }
    
    for(i=Ans.size()-1;Ans[i]=='0';i--)
       Ans.erase(Ans.size()-1);
       
    if(sign==-1)
    Ans.push_back('-');
    
    return reverse(Ans);
}

int main()
{
    string a,b;
    cin>>a>>b;
    
    cout<<Subtract(a,b);
}
