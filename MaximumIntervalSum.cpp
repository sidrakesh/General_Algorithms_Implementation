#include <iostream>

using namespace std;

const int INF = (-(1<<30));  // negative infinity

int MIS(int A[],int N) {
    int sum = 0,i; // initially sum is 0
    int Max = -INF; // Maximum is less than 0
    
    for( i=0; i<N; i++ ) {
       sum += A[i]; // "A[]" array of intejars
        if( sum > Max ) Max = sum;
        if( sum < 0 ) sum = 0;  // sum below 0 is not useful, right?
    }
    return Max;
}

int main()
{}
