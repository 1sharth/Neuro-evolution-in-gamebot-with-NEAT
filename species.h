#pragma once
#include "headerfiles.h"

struct Species
{
  int id;
  int dissapointment;
  double maxfitness;
  double thisgenmaxfitness;
  double sum_adj_fitness;
  short existence;
  int noOfChildToProduce;
  Genome** glist;
  int glistsize;
};typedef struct Species Species;

Species** slist;
int slistsize=0;
int best_species_ind;
int MAX_DISSAPOINTMENT_NO=4;
double DISCARD_CHANCE=0.8;

Genome** offsprings=NULL;
int offspringssize=0;



Species* newSpecies()
{

  Species* s=(Species*)malloc(sizeof(Species));
  s->id=slistsize-1;                           //id must start with 0
  s->dissapointment=0;
  s->maxfitness=0;
  s->thisgenmaxfitness=0;
  s->sum_adj_fitness=0;
  s->existence=1;
  s->glist=NULL;
  s->glistsize=0;
  s->noOfChildToProduce=0;
}

int COMPATABILITY_THRESHOLD=15;
int DELTADISJOINT=4;
int DELTAWEIGHTS=0;

void speciesAddGenome(Species* s,Genome* g)
{
  if(s->glistsize==0)
  {
    s->glistsize++;
    s->glist=(Genome**)malloc(sizeof(Genome*));
  }
  else
  {
    s->glistsize++;
    s->glist=(Genome**)realloc(s->glist,sizeof(Genome*)*s->glistsize);
  }
  s->glist[s->glistsize-1]=g;
}

char speciesComp(Genome* G1,Genome* G2)
{
  int i=0,j=0,m=G1->llistsize,n=G2->llistsize;
  Link** A=G1->llist;
  Link** B=G2->llist;
  int count=0;
  double w1sum=0,w2sum=0;
  while(i<m && j<n)
  {
    if(A[i]->innovation==B[j]->innovation)
    {
      w1sum+=A[i]->weight;
      w2sum+=B[j]->weight;
      i++;
      j++;
    }
    else if(A[i]->innovation<B[j]->innovation)
    {
      w1sum+=A[i]->weight;
      count++;
      i++;
    }
    else
    {
      w2sum+=B[j]->weight;
      count++;
      j++;
    }
  }
  while(i<m)
  {
    w1sum+=A[i]->weight;
    count++;
    i++;
  }
  while(j<n)
  {
    w2sum+=B[j]->weight;
    count++;
    j++;
  }
  int no_disj=count;
  int weight_diff=(int)fabs(w1sum-w2sum);
  //printf("%d * no_disj:%d + w_diff:%d  COMPT:%d\n",DELTADISJOINT,no_disj,weight_diff,COMPATABILITY_THRESHOLD);
  if(no_disj*DELTADISJOINT+weight_diff*DELTAWEIGHTS<=COMPATABILITY_THRESHOLD)
    return '1';
  else
    return '0';
}

void speciesGenomeSwap(Genome** x, Genome** y)
{
  Genome* temp=*x;
  *x=*y;
  *y=temp;
}

void speciesGenomesort(Species* s,int l,int r)  //TODO:untested
{
  int j,i=l+1,k;
  if(l<r)
  {
    for(j=l+1; j<=r; j++)
      if(s->glist[j]->fitness>s->glist[l]->fitness)
        speciesGenomeSwap(&s->glist[j],&s->glist[i++]);
    speciesGenomeSwap(&s->glist[l],&s->glist[i-1]);
    speciesGenomesort(s,l,i-2);
    speciesGenomesort(s,i,r);
  }
}

void speciate(Genome* g,short lastgenome)
{
  if(slistsize==0)
  {
    slistsize++;
    slist=(Species**)malloc(sizeof(Species*));
    slist[slistsize-1]=newSpecies();
    speciesAddGenome(slist[slistsize-1],g);
    return;
  }
  else
  {
    for(int i=0; i<slistsize; i++)           //slistsize=no of species made till now
    {
      if (speciesComp(slist[i]->glist[0], g) == '1')
      {
        speciesAddGenome(slist[i], g);
        return;
      }
      else if(slist[i]->glistsize==1)
      {
        speciesAddGenome(slist[i], g);
        return;
      }
    }

    //new speceies=>
    slistsize++;
    slist = (Species **) realloc(slist, sizeof(Species *) * slistsize);
    slist[slistsize-1]=newSpecies();
    speciesAddGenome(slist[slistsize - 1], g);
  }
}

void speciation()
{
  int i;
  for(i=0; i<glistsize; i++)
  {
    if(i==glistsize-1)
      speciate(glist[i],1);
    else
    {
      speciate(glist[i],0);
    }
  }
  if(slist[slistsize-1]->glistsize==1)
  {
    speciesAddGenome(slist[slistsize-2],slist[slistsize-1]->glist[0]);
    slist[slistsize-1]=(Species*)realloc(slist[slistsize-1],0);
    slist=(Species**)realloc(slist,sizeof(Species*)*(--slistsize));
  }
}

void displaySpeciesInfo(Species* s)
{
  int i;
  printf("Species id:%d size:%d diss:%d maxfit:%f exist:%d childpro:%d\n",s->id,s->glistsize,s->dissapointment,s->maxfitness,s->existence,s->noOfChildToProduce);
  if(s->existence==0)
    return;
  for(i=0; i<s->glistsize; i++)
  {
    displayGenomeInfo(s->glist[i]);
  }
}

void displayAllSpeciesInfo()
{
  int i;
  printf("total species:%d\n",slistsize);
  for(i=0; i<slistsize; i++)
  {
    displaySpeciesInfo(slist[i]);
  }
}

short mostFitSpecie(Species* sp)
{
  int i;
  for(i=0; i<slistsize; i++)
  {
    if(sp->thisgenmaxfitness < slist[i]->thisgenmaxfitness)
    {
      return 0;
    }
  }
  return 1;
}

void removeDissapointingSpecies()
{
  int i;
  for(i=0; i<slistsize; i++)
  {
    Species* sp=slist[i];
    if(sp->dissapointment>MAX_DISSAPOINTMENT_NO)
    {
        if(!mostFitSpecie(sp))
        {
          sp->existence=0;
        }
    }
    else
    {
      if(sp->thisgenmaxfitness<=sp->maxfitness)
      {
        sp->dissapointment++;
      }
      else
      {
        sp->dissapointment=0;
        sp->maxfitness=sp->thisgenmaxfitness;
      }
    }
  }
}

void speciesMakeParents()  //dont consider non existent species
{
  printf("in speciesMakeParents\n");fflush(stdout);
  int i,n;
  for(i=0; i<slistsize; i++)
  {
    if(slist[i]->existence)
      speciesGenomesort(slist[i],0,slist[i]->glistsize-1);
  }
  for(i=0; i<slistsize; i++)
  {
    if(slist[i]->existence)
    {
      Species *sp = slist[i];
      /*printf("speciesMakeParents: sp:%d, sp_size:%d\n", i, slist[i]->glistsize);
      fflush(stdout);*/
      if (sp->glistsize >= 10)
      {
        n = (int) (0.2 * sp->glistsize);

      }
      else if (sp->glistsize >= 7)
      {
        n = 3;
      }
      else
      {
        n = 2;
      }
      printf("no of Parent selected:%d\n",n);
      int j = n;
      for (; j < sp->glistsize; j++)
      {
        if (getRandomfd(0, 1) <= DISCARD_CHANCE)
        {
          sp->glist[j]->exist = 0;
        }
      }
    }
  }
  printf("out of speciesMakeParents\n");fflush(stdout);
}

void calculateBreedingRate()  //dont consider non existent species
{
  printf("in calculateBreedingRate\n");fflush(stdout);
  if(FIXED_NEURAL_NET)
  {
    slist[0]->noOfChildToProduce=global.population;
    printf("offspring to produce:%d\n",slist[0]->noOfChildToProduce);fflush(stdout);
    return;
  }
  int i,totalspeciesfitness=0;
  for(i=0; i<slistsize; i++)
  {
    if(slist[i]->existence==1)
      totalspeciesfitness+=slist[i]->sum_adj_fitness;
  }
  int sum=0;
  for(i=0; i<slistsize; i++)
  {
    if(slist[i]->existence==1)
    {
      if(totalspeciesfitness==0)
      {
        slist[i]->noOfChildToProduce=(int)(global.population/slistsize);
        //printf("childpr %d\n",slist[i]->noOfChildToProduce);
        sum+=slist[i]->noOfChildToProduce;
      }
      else
      {
        slist[i]->noOfChildToProduce=(int)(slist[i]->sum_adj_fitness*global.population/totalspeciesfitness);
        sum+=slist[i]->noOfChildToProduce;
      }
    }
    else
      slist[i]->noOfChildToProduce=0;

    if(slist[i]->noOfChildToProduce==0)
    {
      slist[i]->existence=0;
    }

  }
  if(sum>global.population)
  {
    printf("not possible: no of children to produce > population: calculateBreedingRate: species\n");
  }
  else if(sum<global.population)
  {
    printf("sum<global.population: calculateBreedingRate %d\n",sum);
    double m=slist[0]->thisgenmaxfitness;
    int index=0;
    for(i=0; i<slistsize; i++)
    {
      if(m<slist[i]->thisgenmaxfitness)
      {
        m=slist[i]->thisgenmaxfitness;
        index=i;
      }
    }
    slist[index]->noOfChildToProduce+=(global.population-sum);
  }
  else
  {
    printf("sum==global.population: calculateBreedingRate %d\n",sum);
  }
  printf("out of calculateBreedingrate\n");fflush(stdout);
}

void deleteGarbage()
{
  printf("in deleteGarbage\n");fflush(stdout);
  int i,j;
  for(i=0; i<glistsize; i++)
  {
    Genome* g=glist[i];
    for(j=0; j<g->llistsize; j++)        //destroy all list nodes one-by-one
    {
      g->llist[j]=(Link*)realloc(g->llist[j],0);
    }
    g->llist=(Link**)realloc(g->llist,0);  //destroy list
    for(j=0; j<g->nlistsize; j++)
    {
      g->nlist[j]=(Neuron*)realloc(g->nlist[j],0);
    }
    g->nlist=(Neuron**)realloc(g->nlist,0);
    g=(Genome*)realloc(g,0);
  }
  glist=(Genome**)realloc(glist,0);

  for(i=0; i<slistsize; i++)
  {
    slist[i]=(Species*)realloc(slist[i],0);
  }
  slist=(Species**)realloc(slist,0);
  glistsize=0;
  slistsize=0;
  printf("out of deleteGarbage\n");fflush(stdout);
}

void generateOffspringsAndSpeciate()  //dont consider non-existent species
{
  printf("in generateOffspringsAndSpeciate\n");fflush(stdout);
  int i,j,k,n1,n2;
  offsprings=(Genome**)realloc(offsprings,sizeof(Genome*)*global.population);
  for(i=0; i<slistsize; i++)
  {
    if(slist[i]->existence)
    {
      /*printf("total species %d\n", slistsize);
      fflush(stdout);*/

      Species *sp = slist[i];
      //printf("specie no %d child to produce:%d\n", i,sp->noOfChildToProduce);
      //fflush(stdout);
      for (j = 0; j < sp->noOfChildToProduce; j++)
      {

        /*printf("   ->no of genomes %d\n", sp->glistsize);
        fflush(stdout);
        for (k = 0; k < sp->glistsize; k++)
        {
          displayGenomeInfo(sp->glist[k]);
        }*/

        n1 = rand2() % sp->glistsize;
        while (sp->glist[n1]->exist == 0)
        {n1 = rand2() % sp->glistsize;}

        n2 = rand2() % sp->glistsize;
        while (sp->glist[n2]->exist == 0)
        {n2 = rand2() % sp->glistsize;}

        while (n2 == n1)
        {
          n1 = rand2() % sp->glistsize;
          while (sp->glist[n1]->exist == 0)
          {n1 = rand2() % sp->glistsize;}

          n2 = rand2() % sp->glistsize;
          while (sp->glist[n2]->exist == 0)
          {n2 = rand2() % sp->glistsize;}
        }
        offsprings[offspringssize++] = breed(sp->glist[n1], sp->glist[n2]);
        //printf("offspringssize: %d\n",offspringssize);fflush(stdout);
      }
    }

  }
  deleteGarbage();                      //TODO:carefull
  glist=offsprings;
  glistsize=global.population;
  offsprings=NULL;
  offspringssize=0;
  speciation();
  printf("out of generateOffspringsAndSpeciate\n");fflush(stdout);
}

void showPrevGenInfo()
{
  int i,j;
  printf("Old gen finised\n");
  printf("Prev Gen Maxfitness:%f\n",global.maxfitness);

  for(i=0; i<slistsize; i++)
  {
    Species* sp=slist[i];
    if(sp->existence)
    {
      printf("species:%d thisGenMaxFit:%f overallMaxFit:%f\n", i, sp->thisgenmaxfitness, sp->maxfitness);
      for (j = 0; j < sp->glistsize; j++)
      {
        printf("  =>genome:%d fitness:%f exist:%d\n", j, sp->glist[j]->fitness,sp->glist[j]->exist);
      }
    }
  }
  global.curr_gen++;
  printf("New Gen:%d\n",global.curr_gen);


}

void newGeneration()
{
  if(FIXED_NEURAL_NET)
  {
    calculateBreedingRate();
    speciesMakeParents();
    showPrevGenInfo();
    generateOffspringsAndSpeciate();
  }
  else
  {
    removeDissapointingSpecies();
    calculateBreedingRate();
    speciesMakeParents();
    showPrevGenInfo();
    generateOffspringsAndSpeciate();
    printf("No of species: %d\n",slistsize);
  }

}



