#include "resize.h"

void addlistmat(struct listmat *listmat, struct doublearray2D mat)
{
	while(listmat->next!=NULL)
		listmat=listmat->next;
	struct listmat *aux=malloc(sizeof(struct listmat));
	aux->mat=mat;
	aux->next=NULL;
	listmat->next=aux;
}

struct doublearray new_doublearray(unsigned i)
{
	double *x=malloc(i*sizeof(double));
	for(unsigned k =0; k<i; k++)
		x[k]=0;
	struct doublearray array;
	array.sizeX=i;
	array.elm=x;
	return array;
}

struct doublearray2D new_doublearray2D(unsigned i,unsigned j)
{
	struct doublearray *x = malloc(i*sizeof(struct doublearray));
	for(unsigned k = 0;k<i;k++)
	{
		x[k]=new_doublearray(j);
	}
	struct doublearray2D array;
	array.sizeX=i;
	array.sizeY=j;
	array.elm=x;
	return array;
}
void printmat(struct doublearray2D mat)
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			printf("%d ",mat.elm[i].elm[j]);
		}
		printf("\n");
	}
	printf("\n");
}
void printlistmat(struct listmat *listmat)
{
   while (listmat!=NULL)
		 printmat(listmat->mat);
}
struct doublearray2D Norm(struct doublearray2D matend, SDL_Surface *s,int x,int y, int xend, int yend)
{
	int t1=xend-x;
	int t2=yend-y;
	Uint8 r,g,b;
	struct doublearray2D mat1 = new_doublearray2D(t1,t2);
	
	for(int i=0;i<t1;i++)
	{
		for(int j=0;j<t2;j++)
		{	
			Uint32 pixel = getpixel(s,i,j);
			SDL_GetRGB(pixel,s->format,&r,&g,&b);
			if (g==0)
			{
				mat1.elm[i].elm[j]=1;
				printf("On passe par là ?");
			}
			else
				mat1.elm[i].elm[j]=0;
				printf("enculé\n");
		}
	}
  /*for (int i=0;i<20;i++)
	{
		for(int j = 0; j<20;j++)
		{	
			//matend.elm[i].elm[j] = mat1.elm[(i*t1)/20].elm[(j*t2)/20];
			matend.elm[i].elm[j] = 1;
		}
	}*/
  return matend;
}

void Norm_full(struct charlist *list,SDL_Surface *s)
{
	list=list->next;
	list=list->next;
	int x,xend,y,yend;
	printf("chatte\n");
	struct listmat *listmat = malloc(sizeof(struct listmat));
	struct doublearray2D mat = new_doublearray2D(20,20);
	while(list->next!=NULL)
	{
		printf("rayan kikine\n");
		x=list->x;
		printf("rayan pete\n");

		xend = list->xend;
		printf("rayan fume %d\n",x);

		y=list->y;
		printf("rayan boit %d\n",y);

		yend=list->yend;
		printf("rayan prend du café %d\n",xend);

		
		printf("rayan mange du jambon %d\n",yend);
		addlistmat(listmat,Norm(mat,s,x,y,xend,yend));
	  printf("faker\n");
    printlistmat(listmat);
		//reseau de neuronne sur mat;
		list=list->next;
		printf("rayan oublie son tapis de priere\n");

	}
}
