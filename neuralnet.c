#include <stdio.h>
#include "utility.h"

int nnLayers_array[]={4,20,20,3};
int nnLayers_arrsize=4;

struct Layer
{
  double** nodes;
  double* bias_list;
};typedef struct Layer Layer;

struct NeuralNet
{
   Layer* layers;
}; typedef struct NeuralNet NeuralNet;

NeuralNet nn;
double** nnoutlayers=NULL;

void nnInit()
{
  int i;
  nn.layers=(Layer*)malloc(sizeof(Layer)*nnLayers_arrsize);
  nnoutlayers=(double**)malloc(sizeof(double*)*nnLayers_arrsize);
  for(i=0; i<nnLayers_arrsize; i++)
  {
    nn.layers[i].nodes=(double**)malloc(sizeof(double*)*nnLayers_array[i]);
    nnoutlayers[i]=(double*)malloc(sizeof(double)*nnLayers_array[i]);
  }
}

void nnSet(double* genes,int p,int n)
{
  int i,j,k;
  double* weights=extract(genes,'l',0,p);
  double* bias=extract(genes,'l',p,n);

  int stind=0,endind;
  for(i=1; i<nnLayers_arrsize; i++)
  {
    for(j=0; j<nnLayers_array[i]; j++)
    {
      endind=stind+nnLayers_array[i-1];
      nn.layers[i].nodes[j]=extract(weights,'l',stind,endind);
      stind=endind;
    }
  }

  stind=0;
  for(i=0; i<nnLayers_arrsize; i++)
  {
    endind=stind+nnLayers_array[i];
    nn.layers[i].bias_list=extract(bias,'l',stind,endind);
    stind=endind;
  }
}

void nnCalc(double* input)  //prone to memory leak
{
  int i,j,k;
  for(j=0; j<nnLayers_array[0]; j++)
  {
    nn.layers[0].nodes[j]=(double*)malloc(sizeof(double));
    nn.layers[0].nodes[j][0]=input[j];

  }

  for(i=1; i<nnLayers_arrsize; i++)
  {
    for(j=0; j<nnLayers_array[i]; j++)
    {
      printf("i=%d j=%d\n",i,j);
      fflush(stdout);
      arrayMul(input,nn.layers[i].nodes[j],nnLayers_array[i-1]);
      nnoutlayers[i][j]=arrayElementsAdd(nn.layers[i].nodes[j],nnLayers_array[i-1]);
      nnoutlayers[i][j]+=nn.layers[i].bias_list[j];
      nnoutlayers[i][j]=activationFunc(nnoutlayers[i][j]);
      printf("%f\n",nnoutlayers[i][j]);
    }

    input=nnoutlayers[i];

  }
}

double* getOutput(double* input)
{
  nnCalc(input);
  return nnoutlayers[nnLayers_arrsize-1];
}

void displayArr(double* x,int n)
{
  int i;
  for(i=0;i<n; i++)
    printf("%f ",x[i]);
  printf("\n\n\n\n");
}

int main()
{
  int i,j,k;
  nnInit();
  double *a;
  a=getRandomfdv(-2,2,1727);
  nnSet(a,1680,1727);
  /*for(i=0; i<2;i++)
  {
    printf("ith layer=%i:\n",i);
    for(j=0;j<nnLayers_array[i]; j++)
    {
      printf("    %dth row:\n",j);
      printf("     ");
      displayArr(nn.layers[i].nodes[j],nnLayers_array[i-1]);
    }
   }*/
   double inp[4]={23.4,46.2,65.44,2.0};
   displayArr(getOutput(inp),3);

}
