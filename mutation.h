#pragma once
#include "headerfiles.h"

double LINKMUTATE=0.3;
double NODEMUTATE=0.3;
double PERTURBANCE=0.5;
double POINTMUTATE=0.1;
double ENABDISMUTATE=0.01;

void pointMutate(Genome* g)              //always invoked
{
  int i;
  for(i=0; i<g->llistsize; i++)
  {
    if(getRandomfd(0,1)<=POINTMUTATE)
      g->llist[i]->weight=getRandomfd(-1,1);
  }
}

void neuronSwap(Neuron** N1,Neuron** N2)
{
  Neuron* temp=*N1;
  *N1=*N2;
  *N2=temp;
}

void linkMutate(Genome* g)
{
  int i;
  int n1=rand2()%g->nlistsize;
  int n2;
  while((n2=rand2()%g->nlistsize)==n1)
    ;
  Neuron* N1=g->nlist[n1];
  Neuron* N2=g->nlist[n2];

  if(N2->type=='I')
  {
    if(N1->type=='O' || N1->type=='H')
    {
      swap(&n1,&n2);
    }
    else
      return;
  }
  else if(N2->type=='H')
  {
    if(N1->type=='O')
    {
      swap(&n1,&n2);
    }
    else if(N1->type=='H')
      return;

  }
  else if(N2->type=='O' && N1->type=='O')
    return;

  //printf("n1 and n2: %d %d\n",n1,n2);fflush(stdout);
  if(genomeCheckLink(g,n1,n2)=='0')
  {
    Link* l=newLink(n1,n2,getRandomfd(-INITIALWEIGHT,INITIALWEIGHT));
    genomeAddLink(g,l);
    if(genomeDetectCycle(g))
    {
      genomeRemoveLastLink(g);
    }
  }
}

void nodeMutate(Genome* g)
{
  int i;
  int n1=rand2()%g->nlistsize;
  int n2;
  double w;
  while((n2=rand2()%g->nlistsize)==n1)
    ;
  Neuron* N1=g->nlist[n1];
  Neuron* N2=g->nlist[n2];

  if(N2->type=='I')
  {
    if(N1->type=='O' || N1->type=='H')
    {
      swap(&n1,&n2);
    }
    else
      return;
  }
  else if(N2->type=='H')
  {
    if(N1->type=='O')
    {
      swap(&n1,&n2);
    }
  }
  else if(N2->type=='O' && N1->type=='O')
    return;

  N1=g->nlist[n1];
  N2=g->nlist[n2];
  for(i=0; i<N1->linksoutsize; i++)
  {
    if(N1->linksout[i]->in==n2)
    {
      if(N1->linksout[i]->enable)
      {
        N1->linksout[i]->enable=0;
        w=N1->linksout[i]->weight;
        Neuron* neuron=newNeuron('H',0);
        if(checkInnovation('N',n1,n2)==-1)
          newInnovation('N',n1,n2);
        genomeAddNeuron(g,neuron);
        Link* ll=newLink(n1,neuron->id,w);
        genomeAddLink(g,ll);
        Link* ll2=newLink(neuron->id,n2,1);
        genomeAddLink(g,ll2);
        break;
      }
      else
        return;
    }

  }
}

void enabledisMutate(Genome* g)                             //always invoked
{
  int i;
  for(i=0; i<g->llistsize; i++)
  {
    /*if(g->llist[i]->enable)
    {
      if(getRandomfd(0,1)<ENABDISMUTATE)
      {
        g->llist[i]->enable=0;
      }
    }
    else*/

      if(getRandomfd(0,1)<ENABDISMUTATE)
      {
        g->llist[i]->enable=1;
      }

  }
}

void mutate(Genome* g)
{
  pointMutate(g);
  if(FIXED_NEURAL_NET!=1)
  {
    if (getRandomfd(0, 1) <= LINKMUTATE) {
      printf("Link Mutated!!\n");
      fflush(stdout);
      linkMutate(g);
    }
    if (getRandomfd(0, 1) <= NODEMUTATE) {
      printf("node Mutated!!\n");
      fflush(stdout);
      nodeMutate(g);
    }
    enabledisMutate(g);
  }
}

double FULLPARENT_CHILD_CHANCE=0.15;

Genome* breed(Genome* G1,Genome* G2)
{
  int i=0,j=0,m=G1->llistsize,n=G2->llistsize,fit,k=0,z=0;
  Link** A=G1->llist;
  Link** B=G2->llist;
  Link** Z=NULL;

  if(G1->fitness > G2->fitness)
    fit=0;
  else if(G1->fitness<G2->fitness)
    fit=1;
  else
    fit=-1;
  if(getRandomfd(0,1)<=FULLPARENT_CHILD_CHANCE)
  {
    if(fit==0)
    {
      for(z=0; z<m; z++)
      {
        addToLinkArr(&Z,A[z],k++);
      }
    }
    else
    {
      for(z=0; z<n; z++)
      {
        addToLinkArr(&Z,B[z],k++);
      }
    }
  }
  else
  {
    while (i < m && j < n)
    {

      if (A[i]->innovation == B[j]->innovation)
      {
        if (rand2() % 2 == 0)
          addToLinkArr(&Z, A[i], k++);
        else
          addToLinkArr(&Z, B[j], k++);
        i++;
        j++;
      }
      else if (A[i]->innovation < B[j]->innovation)
      {
        if (fit == -1 || fit == 0)
        {
          addToLinkArr(&Z, A[i], k++);
        }
        i++;
      }
      else
      {
        if (fit == -1 || fit == 1)
        {
          addToLinkArr(&Z, B[j], k++);

        }
        j++;
      }
    }
    while (i < m)
    {
      if (fit == -1 || fit == 0)
      {
        addToLinkArr(&Z, A[i], k++);
      }
      i++;
    }
    while (j < n)
    {
      if (fit == -1 || fit == 1)
      {
        addToLinkArr(&Z, B[j], k++);
      }
      j++;
    }
  }
  Genome* g=genomeGenFromLinkarr(Z,k);
  mutate(g);
  return g;

}





