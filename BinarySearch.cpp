#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<map>
#include<cmath>

using namespace std;

int binarySearch(int arr[], int value, int left, int right)
{
    int mid;
          
    if (right < left)
       return -1;

    mid = floor((left+right)/2);
    
    if (arr[mid]==value)
       return mid;
       
    if (value < arr[mid])
       binarySearch(arr, value, left, mid-1);
    else
       binarySearch(arr, value, mid+1, right);
}

int main()
{
	int arr[10] = {3,2,5,4,6,7,8,1,9,10};
	
	cout<<binarySearch(arr,6,0,9);
}
