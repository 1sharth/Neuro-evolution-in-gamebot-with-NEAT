#include "headerfiles.h"
int i=0;
void onMouseHandling2(int button,int state, int x, int y)
{
  /*Genome* g;
  if(state==GLUT_DOWN && button==0)
  {
    g=breed(glist[0],glist[1]);
    makeNetwork(g);
    printf("breeding done\n");fflush(stdout);
  }
  else if(state==GLUT_DOWN && button==1)
  {
    mutate(g);
    makeNetwork(g);
    printf("all mutations done\n");fflush(stdout);
  }
  glutPostRedisplay();
  /*if(state==GLUT_DOWN && button==0)
  {
    int t=10;
    while(t--)
    {nodeMutate(glist[0]);}
    Genome* g=breed(glist[0],glist[1]);
    makeNetwork(g);

    displayGenomeInfo(g);
    displayGenomeInfo(glist[0]);
    displayGenomeInfo(glist[5]);
    printf("comparing genome 0 and 10:%c\n",speciesComp(glist[0],glist[5]));
    nodeMutate(glist[0]);
    linkMutate(glist[0]);
    enabledisMutate(glist[0]);
    nodeMutate(glist[5]);
    linkMutate(glist[5]);
    enabledisMutate(glist[5]);
    genomeLinksort(glist[0],0,glist[0]->llistsize-1);
    genomeLinksort(glist[5],0,glist[5]->llistsize-1);

    for(i=0;i<glistsize; i++)
    {
      speciate(glist[i]);
    }
    displayAllSpeciesInfo();
    for(i=0;i<global.population; i++)
    {
      nodeMutate(glist[i]);
      linkMutate(glist[i]);
      enabledisMutate(glist[i]);
      genomeLinksort(glist[i],0,glist[i]->llistsize-1);
    }
    //Genome* g=breed(glist[0],glist[1]);
    //makeNetwork(g);
    //nodeMutate(g);
    glutPostRedisplay();
    i=0;
  }*/
}

void onMouseHandling(int button,int state, int x, int y)
{

}

void shapeInit()
{
  drawable_arr[0]=drawAllRectangles;
  drawable_arr[1]=drawAllCircles;
  drawable_arr[2]=drawAllLines;
}

void testCycle()
{
  Genome* g=newGenome();
  int i,j;
  for(j=0; j<global.totalinputs+global.totaloutputs+2; j++)
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
  genomeAddLink(g,newLink(0,3,0.5));
  genomeAddLink(g,newLink(1,3,0.1));
  genomeAddLink(g,newLink(3,4,-0.4));
  genomeAddLink(g,newLink(4,2,0.8));
  /*genomeAddLink(g,newLink(0,6,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(6,7,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(7,8,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(9,7,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(9,8,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(6,9,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(1,6,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(2,9,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(3,9,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(7,5,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(7,4,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(8,5,getRandomfd(-1,1)));
  genomeAddLink(g,newLink(8,4,getRandomfd(-1,1)));*/
  double* inp=(double*)malloc(sizeof(double)*global.totalinputs);
  inp[0]=0.1;
  inp[1]=-0.2;

  double* out=evalNetwork(g,inp);
  printf("%f %f\n",out[0],out[1]);
  fflush(stdout);
  /*Link* l=newLink(8,6,getRandomfd(-1,1));
  genomeAddLink(g,l);
  if(genomeDetectCycle(g))
  {
    printf("cycle detected\n");fflush(stdout);
    genomeRemoveLastLink(g);
  }*/
  makeNetwork(g);

  displayGenomeInfo(g);
}

int main(int argc,char** argv)
{
  Initialize(argc,argv);
  shapeInit();
  globalize();
  gameInit();
  neuronPositionsInit();
  int i,j;
  int t=10;
  if(FIXED_NEURAL_NET)
    createInitGenomes(80);
  else
    createInitGenomes(0);
  speciation();
  //testCycle();

  /*while(t--)
  {
    printf("t=%d\n",t);fflush(stdout);
    removeDissapointingSpecies();
    calculateBreedingRate();
    speciesMakeParents();

    //displayAllSpeciesInfo();
    printf("--------------------------------------------\n");
    generateOffspringsAndSpeciate();
  }*/
  //displayAllSpeciesInfo();
  //testCycle();

  glutPostRedisplay();
  glutMainLoop();
}
