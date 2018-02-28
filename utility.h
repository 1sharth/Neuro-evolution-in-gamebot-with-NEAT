#pragma once
#include "headerfiles.h"

int rand2()
{
  time_t t=clock();
  srand((unsigned)t);
  return rand();
}

//returns random double data type between low and high inclusive
double getRandomfd(int low,int high)
{
  time_t t=clock();
  srand(t);
  double ri=rand()%(high-low)+low;
  ri+=((double)(rand()%10000000))/10000000;
  return ri;
}

//returns array of random double data type between low and high inclusive
double* getRandomfdv(int low,int high,int size)
{
  int i;
  double* v=(double*)malloc(size*sizeof(double));
  for(i=0; i<size; i++)
    v[i]=getRandomfd(low,high);
  return v;
}

/*every ith element of target array gets multiplied by that of source
array and hence target array gets modified
*/
void arrayMul(double* source,double *target, int size)
{
  int i;
  for(i=0; i<size; i++)
  {
    target[i]*=source[i];
  }
}

/*every ith element of source array is added to that of target
array and hence target array gets modified
*/
void arrayAdd(double* source,double *target, int size)
{
  int i;
  for(i=0; i<size; i++)
  {
    target[i]+=source[i];
  }
}

/*returns addition of all elements inside an array */
double arrayElementsAdd(double* source,int size)
{
  int i,sum=0;
  for(i=0; i<size; i++)
    sum+=source[i];
  return sum;
}

/*returns multiplication of all elements inside an array */
double arrayElementsMul(double* source,int size)
{
  int i,prod=1;
  for(i=0; i<size; i++)
    prod*=source[i];
  return prod;
}

double max(double x,double y)
{
  return x>y?x:y;
}

/*returns the value of 1/(1+e^-x)*/
double activationFunc(double x)
{
  return max(0.0,x);
}

/*returns array containing values between indexes l(inclusive)
and r(exclusive) with given dir.
dir='l' means from left and dir='r' means from right
*/
double* extract(double* source,char dir,int l,int r)
{
  int k=0,i;
  double* x=(double*)malloc(sizeof(double)*(r-l));
  if(dir=='l')
  {
    for(i=l; i<r; i++)
      x[k++]=source[i];
  }
  else if(dir=='r')
  {
    for(i=r; i>l; i--)
      x[k++]=source[i];
  }
  return x;
}

void swap(int* x, int* y)
{
  int temp=*x;
  *x=*y;
  *y=temp;
}

void quicksort(int* A,int l,int r)
{
  int j,i=l+1;
  if(l<r)
  {
    for(j=l+1; j<=r; j++)
      if(A[j]<A[l])
        swap(&A[j],&A[i++]);
    swap(&A[i-1],&A[l]);
    quicksort(A,l,i-2);
    quicksort(A,i,r);
  }
}
