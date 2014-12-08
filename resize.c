#include "resize.h"

void addlistmat(struct listmat *listmat, struct doublearray2D mat)
{
	printf("rayan mange du saucisson\n");
	while(listmat->next!=NULL)
	{
		printf("rayan prend des prot\n");
		listmat=listmat->next;
	}
	struct listmat *aux=malloc(sizeof(struct listmat));
	printf("rayan joue a wow\n");
	aux->mat=mat;
	aux->next=NULL;
	printf("mode medecine\n");
	listmat->next=aux;
}

struct doublearray new_doublearray(unsigned i)
{
	double *x=malloc(i*sizeof(double));
	for(unsigned k =0; k<i; k++)
		x[k]=1;
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
void printmat(int **mat)
{
	for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			printf("%d ",mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int** Norm(SDL_Surface *s, int x,int y, int xend, int yend)
{
	int t1=xend-x;
	int t2=yend-y;
	Uint8 r,g,b;
	int **mat1 = malloc(t1*(sizeof(int*)));
	for (x=0;x<t2;x++)
		mat1[x]=malloc(t2*(sizeof(int)));
	int **matend = malloc(20*(sizeof(int*)));
	for (x=0;x<20;x++)
		matend[x]=malloc(20*(sizeof(int)));
	for(int i=0;i<t1;i++)
	{
		for(int j=0;j<t2;j++)
		{	
			Uint32 pixel = getpixel(s,i,j);
			SDL_GetRGB(pixel,s->format,&r,&g,&b);
			if (g==0)
			{
				printf("bite\n");
				mat1[j][i]=1;
			}
			else
			{
				printf("bite2\n");
				mat1[j][i]=0;
			}
		}
	}
  for (int i=0;i<20;++i)
	{
		for(int j = 0; j<20;++j)
		{	
			printf("cul\n");
			matend[j][i] = mat1[(j*t1)/20][(i*t2)/20];	
		}
	}
	printf("rayan bosse dure\n");
  return matend;
}

void Norm_full(struct charlist *list,SDL_Surface *s)
{
	list=list->next;
	int x,xend,y,yend;
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
		//matend = Norm(matend,s,x,y,xend,yend);
	  printf("faker\n");
    printmat(Norm(s,x,y,xend,yend));
		//reseau de neuronne sur mat;
		list=list->next;
		printf("rayan oublie son tapis de priere\n");

	}
}


