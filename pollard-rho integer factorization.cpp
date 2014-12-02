#include<stdio.h>
#include<math.h>
#include<stdlib.h>
int gcd(int a, int b)
{
    if(b==0)
		return a;
    else
    	return(gcd(b,a%b));
}

long long int mod(long long int a , long long int b , long long int n )
{    
     long long int x=1, y=a;
     
	 while(b>0)
     {
        if(b%2==1)
			x = ((x%n)*(y%n))%n ;
        
		y = ((y%n)*(y%n))%n ;
        b/=2 ;
     }
     
	 return x%n ;
}

int isprimes(long long int u)
{  
    if(u==3)
    	return 1 ;
    
	int a = 2 , i ;
    long long int k , t = 0 , r , p ;
    
	k = u-1 ;
    
	while(k%2==0)
    {
		k/=2;
		t++;
	}

	while(a<=3) /*there are no strong pseudoprimes common in base 2 and base 3*/
    {   
    	r = mod(a,k,u) ;
        
		for(i = 1 ; i<=t ; i++)
        {
        	p = ((r%u)*(r%u))%u ;
            
			if((p==1)&&(r!=1)&&(r!=(u-1)))
            {
				return 0;
			}
            r = p ;
        }
    	
		if(p!=1)
    		return 0 ;
        else
    		a++;
    } 

    if(a==4)
    	return 1 ;
}

long long int pol(long long int u)
{ 
	long long int x = 2 , k , i , a , y , c , s;
	int d = 1 ;
	
	k = 2 ;
	i = 1 ;
	y = x ;
	a = u ;
	if(isprimes(u)==1)
	{ 
    	return 1;
	}
	c=-1 ;
	s = 2 ;
	
	while(1)
	{
    	i++;
		x=((x%u)*(x%u)-1)% u ;
    	d = gcd(abs(y-x),u) ;

    	if(d!=1&&d!=u)
    	{
			printf("%d ",d);
    		while(a%d==0) { a=a/d;  }

        	x = 2 ;
        	k = 2 ;
        	i = 1 ;
        	y = x ;
        	
			if(a==1)
        	{
				return 0 ;
			}
        	if(isprimes(a)!=0)
        	{
				return a ;
			}
        	u=a;
    	}
    
		if(i==k)
    	{
			y = x ;
			k*=2 ;
			c = x ;
		}  /*floyd cycle detection*/
        if(c==x)                                                                 
		{
			x = ++s ;
		}
    }
}

int main()
{
	long long int t ;
    long long int i , n , j , k , a , b  , u ;
    
	while(scanf("%lld",&n)&&n!=0)
    {
		u = n;
		k = 0;
		while(u%2==0)
       	{
			u/=2 ;
			k = 1 ;
		}
		
		if(k==1)
			printf("2 ") ;
    	if(u!=1)
			t = pol(u) ;
        if(u!=1) 
		{
			if(t==1)
			{
				printf("%lld",u) ;
			}
			else if(t!=0)
			{
				printf("%lld",t) ;
			}
		}
		printf("\n");
	}
    return 0;
}
