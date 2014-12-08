#include "resize.h"
void Resizechar(SDL_Surface *s, struct charlist *list) {
  list=list->next;
  
  while (list->next!=NULL)
  {
		int x = list->x;
		//printf("%d ",x);
		int y = list->y;
	//printf("%d ",y);
		int xend = list->xend;
	//printf("%d ",xend);
		int yend = list->yend;
		int width = yend-y;
		int height = xend-x;
		//printf("%d %d %d\n",yend,width,height);
		int widthDesired = 16;
		int heightDesired = 16;
		Uint8 r,g,b;

		int **charArray = malloc((height)*sizeof(int*));
		for (size_t i=0; i<height;i++)
			charArray[i] = malloc((width)*sizeof(int));

		struct doublearray2D *lastChar = malloc(sizeof(struct doublearray2D));
					lastChar->sizeX=yend-y;
		lastChar->sizeY=xend-x;
		lastChar->elements=charArray;
		for(int i=0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{	
				Uint32 pixel = getpixel(s,j+y-1,i+x-1);
				SDL_GetRGB(pixel,s->format,&r,&g,&b);
				if (r==0&&g==0&&b==0)
				{
					charArray[i][j]=1;
				}
				else
				{
					charArray[i][j]=0;
				}
				
			}
		}
		
		int **pixArray = calloc((16), sizeof (int *));
		for (size_t i = 0; i < 16; i++)
			pixArray[i] = calloc((16), sizeof (int));

		struct doublearray2D *charByChar = malloc(sizeof (struct doublearray2D));
		charByChar->sizeX = 16;
		charByChar->sizeY = 16;
		charByChar->elements = pixArray;

		float ratioWidth = (float) widthDesired / (float) (width);
					float ratioHeight = (float) heightDesired / (float) (height);
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				for (int extraY = 0; extraY < ratioHeight; ++extraY) {
					for (int extraX = 0; extraX < ratioWidth; ++extraX) {
						charByChar->elements[(int) 
						  ((float) i * ratioWidth) + extraX][(int)((float) 
						    j * ratioHeight) + extraY] = lastChar->elements[j][i];
					}
				}
			}
		}
		for (int i = 0; i<16; i++)
		{
			for (int j=0; j<16;j++)
			{
				printf("%d ",charByChar->elements[j][i]);
			}
			printf("\n");
		}
		list=list->next;
	}	
}





