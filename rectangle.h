#pragma once

struct Rectangle
{
  int x,y,w,h;
  char isalive;
  Color color;
  int windowId;
};typedef struct Rectangle Rectangle;

int bulletind;
int playerind;

int rect_count=0;
Rectangle *rect_arr;

int addRectangle(int cx,int cy,int w,int h)
{
  rect_count++;
  if(rect_count==0)
  {
    rect_arr=(Rectangle*)malloc(1*sizeof(Rectangle));
  }
  else
  {
    rect_arr=(Rectangle*)realloc(rect_arr,rect_count*sizeof(Rectangle));
  }
  rect_arr[rect_count-1].x=cx;
  rect_arr[rect_count-1].y=cy;
  rect_arr[rect_count-1].w=w;
  rect_arr[rect_count-1].h=h;
  rect_arr[rect_count-1].isalive='1';
  rect_arr[rect_count-1].windowId=1;
  return rect_count-1;
}

void gameInit()
{
  playerind=addRectangle((int)(windowleft),1,40,40);
  //printf("y:%d h/2:%d\n",rect_arr[playerind].y,(rect_arr[playerind].h)/2);
  bulletind=addRectangle((int)(windowright),0,8,5);
}

void bulletPlayerReset()
{
  Rectangle* player=&rect_arr[playerind];
  Rectangle* bullet=&rect_arr[bulletind];
  player->y=0;
  bullet->x=windowright;
  bullet->x=(int)(CurrentWidth*0.8/2);
  int ymin=player->y - (player->h)/2-5;
  int ymax=player->y + (player->h)/2+5;
  double y=getRandomfd(ymin,ymax);
  bullet->y=(int)y;
}

void drawRectangle(Rectangle* rect)
{
  int dw=rect->w/2;
  int dh=rect->h/2;
  int x=rect->x;
  int y=rect->y;
  //printf("%d %d %d\n",rect->color.r,rect->color.g,rect->color.b);
  //fflush(stdout);
  rect->color.r=0;
  rect->color.g=0;
  rect->color.b=0;
  glColor3ub(rect->color.r,rect->color.g,rect->color.b);
  glBegin(GL_LINE_LOOP);
  glVertex2d(x-dw,y+dh);
  glVertex2d(x+dw,y+dh);
  glVertex2d(x+dw,y-dh);
  glVertex2d(x-dw,y-dh);
  glEnd();
}

void moveRect(Rectangle* rect, double xx,double yy)
{
  rect->x+=xx;
  rect->y+=yy;
}

short collided(Rectangle* rect1, Rectangle* rect2)
{
  if((rect1->x+rect1->w/2 > rect2->x-rect2->w/2) && (rect1->x-rect1->w/2 < rect2->x+rect2->w/2))
  {
    if((rect1->y+rect1->h/2 > rect2->y-rect2->h/2) && (rect1->y-rect1->h/2 < rect2->y+rect2->h/2))
    {
      return 1;
    }
  }
  return 0;
}

void drawAllRectangles(int id)
{
  int i;
  //printf("draw rect y:%d h/2:%d\n",player->y,(player->h)/2);
  for(i=0; i<rect_count; i++)
  {
    //printf("%d\n",rect_arr[i].windowId);
    if(rect_arr[i].isalive=='1' && rect_arr[i].windowId==id)
      drawRectangle(&rect_arr[i]);
  }
}

void playerDynamics(int xx,int yy)
{
  if(rect_arr[playerind].y+yy>windowdown && rect_arr[playerind].y+yy<windowup)
  {
    //printf("lol:playery:%d yy:%d\n",rect_arr[playerind].y,yy);
    moveRect(&rect_arr[playerind],xx,yy);
  }
}

short bulletDynamicsAndCollision()             //TODO:Remove hardcoded
{
  Rectangle* player=&rect_arr[playerind];
  Rectangle* bullet=&rect_arr[bulletind];
  if((bullet->x < (int)(windowleft)))
  {
    bullet->x=(int)(windowright);
    int ymin=player->y - (player->h)/2-5;
    int ymax=player->y + (player->h)/2+5;
    double y=getRandomfd(ymin,ymax);
    bullet->y=(int)y;
    return 0;
  }
  else
  {
    moveRect(bullet,-10,0);
    if(collided(bullet,player))
    {
      bullet->x=(int)(windowright);
      int ymin=player->y - (player->h)/2-50;
      int ymax=player->y + (player->h)/2+50;
      double y=getRandomfd(ymin,ymax);
      bullet->y=(int)y;
      return 1;
    }
    return 0;

  }
}






