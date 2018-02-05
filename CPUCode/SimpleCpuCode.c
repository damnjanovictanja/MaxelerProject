#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "Maxfiles.h"
#include <MaxSLiCInterface.h>


void generateInputData(float *dataIn, int size_k, int size_n)
{
    int i=0;
	for (i = 0; i < size_k; i++) 
		dataIn[i] = size_n - i;
}

long long BKCPU(int k,int n) {
    long long ans=1;
    k=k>n-k?n-k:k;
    int j=1;
    for(;j<=k;j++,n--)
    {
        if(n%j==0)
        {
            ans*=n/j;
        }else
        if(ans%j==0)
        {
            ans=ans/j*n;
        }else
        {
            ans=(ans*n)/j;
        }
    }
    return ans;
}

int main()
{
    struct timespec start, stop;
    clock_t begin;
    clock_t end;
    double result;
    float timeInMillis;
	const int size_k = 10032;
	const int size_n = 60000;
	float res = 1;
	long long rezultat;
	float *dataIn = malloc(size_k * sizeof(float));
    float *dataOut = malloc(size_k*sizeof(float));
    
	generateInputData(dataIn, size_k, size_n);
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	begin = clock();
	rezultat = BKCPU(size_k, size_n);
	end = clock();
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);

	timeInMillis = (float)(end-begin)/(CLOCKS_PER_SEC/1000000);
	result = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec);
	printf("CPU REZULTAT: %lli\n", rezultat);
    printf("time(nanosec): %lf\n", result);
    printf("CPU time: %f\n\n", timeInMillis);
	
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	begin = clock();
	Simple(size_k, dataIn, dataOut);
	end = clock();
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &stop);
    
	for(int i = 0; i < size_k; i++)
	    res = res*dataOut[i];
	timeInMillis = (float)(end-begin)/(CLOCKS_PER_SEC/1000000);
    result = (stop.tv_sec - start.tv_sec) * 1e6 + (stop.tv_nsec - start.tv_nsec);
	printf("MAX REZULTAT: %d\n", (int)round(res));
	printf("time(nanosec): %lf\n", result);
	printf("MAX time: %f\n\n", timeInMillis);

 return 0;   
}

