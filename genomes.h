#pragma once
#include "headerfiles.h"
int INITIAL_LINKS=1;
struct Genome
{
    int ind;
    double fitness;
    double globalRank;
    Neuron** nlist;
    Link** llist;
    int nlistsize;
    int llistsize;
    short exist;
};typedef struct Genome Genome;

Genome* newGenome()
{
  Genome* g=(Genome*)malloc(sizeof(Genome));
  g->fitness=0;
  g->globalRank=0;
  g->nlist=NULL;
  g->llist=NULL;
  g->nlistsize=0;
  g->llistsize=0;
  g->exist=1;
  return g;
}


Genome** glist=NULL;
int glistsize=0;

void genomeAddNeuron(Genome* g,Neuron* n)
{
  n->id=(g->nlistsize);
  if(g->nlistsize==0)
  {
    g->nlist=(Neuron**)malloc(sizeof(Neuron*));
    g->nlist[0]=n;
    g->nlistsize++;
  }
  else
  {
    g->nlistsize++;
    g->nlist=(Neuron**)realloc(g->nlist,sizeof(Neuron*)*(g->nlistsize));
    g->nlist[g->nlistsize-1]=n;
  }
}

void genomeAddLink(Genome* g,Link* l)
{
  int in=l->in,out=l->out;
  neuronAddLink(g->nlist[out],l,'O');
  neuronAddLink(g->nlist[in],l,'I');
  //g->nlist[in]->linksout
  if(g->llistsize==0)
  {
    g->llist=(Link**)malloc(sizeof(Link*));
    g->llist[0]=l;
    g->llistsize++;
  }
  else
  {
    g->llistsize++;
    g->llist=(Link**)realloc(g->llist,sizeof(Link*)*(g->llistsize));
    g->llist[g->llistsize-1]=l;
  }
}

void genomeRemoveLastLink(Genome* g)
{
  int in=g->llist[g->llistsize-1]->in;
  int out=g->llist[g->llistsize-1]->out;
  g->llist[g->llistsize-1]=(Link*)realloc(g->llist[g->llistsize-1],0);
  g->llist=(Link**)realloc(g->llist,sizeof(Link*)*(--(g->llistsize)));


  //g->nlist[in]->linksin[g->nlist[in]->linksinsize-1]=(Link*)realloc(g->nlist[in]->linksin[g->nlist[in]->linksinsize-1],0);
  g->nlist[in]->linksin=(Link**)realloc(g->nlist[in]->linksin,(--(g->nlist[in]->linksinsize))*sizeof(Link*));
  //g->nlist[out]->linksout[g->nlist[out]->linksoutsize-1]=(Link*)realloc(g->nlist[out]->linksout[g->nlist[out]->linksoutsize-1],0);
  g->nlist[out]->linksout=(Link**)realloc(g->nlist[out]->linksout,--(g->nlist[out]->linksoutsize)*sizeof(Link*));
}
void genomeLinkSwap(Link** x, Link** y)
{
  Link* temp=*x;
  *x=*y;
  *y=temp;
}

void genomeLinksort(Genome* g,int l,int r)
{
  int j,i=l+1,k;
  if(l<r)
  {
    for(j=l+1; j<=r; j++)
      if(g->llist[j]->innovation<g->llist[l]->innovation)
        genomeLinkSwap(&g->llist[j],&g->llist[i++]);
    genomeLinkSwap(&g->llist[l],&g->llist[i-1]);
    genomeLinksort(g,l,i-2);
    genomeLinksort(g,i,r);
  }
}

void linkMutate(Genome*);
void nodeMutate(Genome*);
void mutate(Genome* );
void createInitGenomes(int approach)
{
  int i,j,k,l;
  glist=(Genome**)malloc(sizeof(Genome*)*global.population);
  glistsize=global.population;
  if(approach==0)
  {
    for(i=0; i<global.population; i++)
    {
      glist[i] = newGenome();
      for (j = 0; j < global.totalinputs + global.totaloutputs; j++)
      {
        if (j < global.totalinputs)
        {
          genomeAddNeuron(glist[i], newNeuron('I', 0));
        }
        else
        {
          genomeAddNeuron(glist[i], newNeuron('O', 0));
        }
      }
      while (glist[i]->llistsize < INITIAL_LINKS)      //check INITIAL_LINKS must be < than total possible links
      {
        //printf("%d\n",glist[i]->llistsize);fflush(stdout);
        linkMutate(glist[i]);
      }
      int t = 3;
      while (t--)
      {
        nodeMutate(glist[i]);
      }
      genomeLinksort(glist[i], 0, glist[i]->llistsize - 1);
      neuronPositionReset();
    }
  }
  else
  {
    for(i=0; i<global.population; i++)
    {
      glist[i] = newGenome();
      for (j = 0; j < global.totalinputs + global.totaloutputs; j++)  //add input and output nodes
      {
        if (j < global.totalinputs)
        {
          genomeAddNeuron(glist[i], newNeuron('I', 0));
        }
        else
        {
          genomeAddNeuron(glist[i], newNeuron('O', 0));
        }
      }
      for(j=0;j<approach;j++)                          //add hidden nodes.. jth hidden node
      {
        int id;
        Neuron* n=newNeuron('H', 0);
        id=glist[i]->nlistsize;                                      //new neuron's id
        genomeAddNeuron(glist[i],n);

        for(k=0;k<global.totalinputs;k++)             //k stands for input nodes id
        {
          //printf("k:%d  id:%d\n",k,id);fflush(stdout);
          genomeAddLink(glist[i],newLink(k,id,getRandomfd(-INITIALWEIGHT,INITIALWEIGHT)));
        }
        for(k=global.totalinputs;k<global.totalinputs+global.totaloutputs;k++) //k stands for output nodes id
        {
          genomeAddLink(glist[i],newLink(id,k,getRandomfd(-INITIALWEIGHT,INITIALWEIGHT)));
        }

      }
      int t=0;
      while(t--)
      {
        mutate(glist[i]);
      }
      genomeLinksort(glist[i], 0, glist[i]->llistsize - 1);
      neuronPositionReset();
    }

  }

}

Genome* genomeGenFromLinkarr(Link** linkarr,int size)
{
  int maxid=0,i,j;
  for(i=0; i<size; i++)
  {
    if(maxid<linkarr[i]->in)
      maxid=linkarr[i]->in;
    if(maxid<linkarr[i]->out)
      maxid=linkarr[i]->out;
  }
  if(maxid<global.totalinputs+global.totaloutputs-1)
  {
    /*printf("error: impossible situation: genomes.h=>genomeGenFromLinkarr()\n");
    printf("maxid:%d\n",maxid);
    fflush(stdout);*/
  }
  Genome* g=newGenome();
  for(j=0; j<maxid+1; j++)
  {
    if(j<global.totalinputs)
    {
      genomeAddNeuron(g,newNeuron('I',0));
    }
    else if(j<global.totalinputs+global.totaloutputs)
    {
      genomeAddNeuron(g,newNeuron('O',0));
    }
    else
    {
      genomeAddNeuron(g,newNeuron('H',0));
    }
  }
  for(j=0; j<size; j++)
  {
    genomeAddLink(g,linkarr[j]);
  }
  neuronPositionReset();
  return g;
}

void displayGenomeInfo(Genome* genome)
{
  int i,j;
  printf("sof nlist:%d sof llist:%d fitness:%f exist=%d\n",genome->nlistsize,genome->llistsize,genome->fitness,genome->exist);fflush(stdout);
  /*for(i=0;i<genome->nlistsize; i++)
  {
    printf("id:%d type:%c\n",genome->nlist[i]->id,genome->nlist[i]->type);
    printf(" links in:\n");
    for(j=0; j<genome->nlist[i]->linksinsize; j++)
    {
      printf(" %p\n",&genome->nlist[i]->linksin[j]);
    }
    printf(" links out:\n");
    for(j=0; j<genome->nlist[i]->linksoutsize; j++)
    {
      printf(" %p\n",&genome->nlist[i]->linksout[j]);
    }
    printf("\n");
    fflush(stdout);
  }*/
  for(i=0;i<genome->llistsize; i++)
  {
    printf("out:%d in:%d inn:%d\n",genome->llist[i]->out,genome->llist[i]->in,genome->llist[i]->innovation);
  }
  printf("\n\n");
  fflush(stdout);
}

char genomeCheckLink(Genome* g,int n1,int n2)             //untested
{
  int i;
  for(i=0; i<g->llistsize; i++)
  {
    if(g->llist[i]->out==n1 && g->llist[i]->in==n2)
    {
      return '1';
    }
  }
  return '0';
}

short processNode(Genome* g,Neuron* n,int* mark)
{
  int i;
  if(mark[n->id]==1)
  {
    return 1;
  }
  else if(mark[n->id]==0)
  {
    mark[n->id]=1;
    for(i=0; i< n->linksoutsize; i++)
    {
      if(processNode(g,g->nlist[n->linksout[i]->in],mark))
      {
        return 1;
      }
    }
    mark[n->id]=2;
    return 0;
  }
  else
  {
    return 0;
  }
}

short genomeDetectCycle(Genome* g)
{
  int i;
  int* mark=(int*)malloc(sizeof(int)*g->nlistsize);
  for(i=0; i<g->nlistsize; i++)
    mark[i]=0;
  for(i=0; i<global.totalinputs; i++)
  {
    //printf("i=%d\n",i);fflush(stdout);
    if(processNode(g,g->nlist[i],mark)==1)
      return 1;
  }
  return 0;
}
