#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#define nEX 4
#define n1  2
#define n2 2
#define n3 1

double getRandomDouble()
{
  return (double)rand()/(RAND_MAX);
}

void initialize_weight(int numberUnitsFirst,int numberUnitsSecond,double weight[][numberUnitsSecond],double deltaWeight[][numberUnitsSecond])
{
  for (int j = 1; j <= numberUnitsSecond; j++) {
     for (int i = 0; i <= numberUnitsFirst; i++) {
        deltaWeight[i][j]=0.0;
        weight[i][j]=2.0 * ( getRandomDouble() - 0.5 ) * 0.5;
     }
  }
}

int main()
{
  srand(time(NULL));
  int NUM1= n1, NUM2=n2,NUM3=n3,NUMEX=nEX;
  int nbappels=0;
  double Layer2In[nEX+1][n2+1], Layer2InBackProp[n2+1], Layer2Out[nEX][n2+1];
  double Layer3In[nEX+1][n3+1], Layer3Out[nEX+1][n3+1], weight12[n1+1][n2+1];
  double weight23[n2+1][n3+1], deltaWeight12[n1+1][n2+1]; 
  double deltaWeight23[n2+1][n3+1], deltaLayer3[n3+1], deltaLayer2[n2+1];
  double layer1Out[nEX+1][n1+1] = {{0,0,0},{0,0,0},{0,1,0},{0,0,1},{0,1,1}};
  double target[nEX+1][n3+1] = {{0,0},{0,0},{0,1},{0,1},{0,0}};

  initialize_weight(NUM1,NUM2,weight12,deltaWeight12);
  initialize_weight(NUM2,NUM3,weight23,deltaWeight23);


  for (int l = 0; l < 5000; l++) 
  {
    for (int e = 1; e <= NUMEX; e++) 
    {
      nbappels++;
      for( int i = 1 ; i <= NUM1 ; i++ ) 
      {
        printf("Layer2in: %f\n",layer1Out[e][i]);
      }
      for( int j = 1 ; j <= NUM2 ; j++ ) 
      {
        Layer2In[e][j] = weight12[0][j] ;
        for( int i = 1 ; i <= NUM1 ; i++ ) 
        {
          Layer2In[e][j] += layer1Out[e][i] * weight12[i][j] ;
        }
        Layer2Out[e][j] = 1.0/(1.0 + exp(-Layer2In[e][j])) ;
      }

      for( int j = 1 ; j <= NUM3 ; j++ ) 
      {
        Layer3In[e][j] = weight23[0][j] ;
        for( int i = 1 ; i <= NUM2 ; i++ ) 
        {
          Layer3In[e][j] += Layer2Out[e][i] * weight23[i][j] ;
        }
        Layer3Out[e][j] = 1.0/(1.0 + exp(-Layer3In[e][j])) ;
        deltaLayer3[j]=target[e][1]-Layer3Out[e][j];
        printf(" * Layer3 out: %f\n\n",Layer3Out[e][j]);
      }
      for( int j = 1 ; j <= NUM2 ; j++ ) 
      {
        Layer2InBackProp[j] = 0.0 ;
        for( int k = 1 ; k <= NUM3 ; k++ ) 
        {
          Layer2InBackProp[j] += weight23[j][k] * deltaLayer3[k] ;
        }
        deltaLayer2[j] = Layer2InBackProp[j] *Layer2Out[e][j] * (1.0 - Layer2Out[e][j]) ;
      }
      for (int j = 1; j <= NUM2; j++) 
      {
        deltaWeight12[0][j] = 0.1*deltaLayer2[j] + 0.5* deltaWeight12[0][j] ;
        weight12[0][j]+=deltaWeight12[0][j];
        for (int i = 1; i <= NUM1; i++) 
        {
          deltaWeight12[i][j]=0.1*layer1Out[e][i]*deltaLayer2[j]+0.5*deltaWeight12[i][j];
          weight12[i][j]+=deltaWeight12[i][j];
        }
      }
      for (int j = 1; j <= NUM3; j++) 
      {
        deltaWeight23[0][j] = 0.1*deltaLayer3[j] + 0.5* deltaWeight23[0][j] ;
        weight23[0][j]+=deltaWeight23[0][j];
        for (int i = 1; i <= NUM2; i++) 
        {
          deltaWeight23[i][j]=0.1*Layer2Out[e][i]*deltaLayer3[j]+0.5*deltaWeight23[i][j];
          weight23[i][j]+=deltaWeight23[i][j];
        }
      }
    }
  }
  printf("      * Results *\n\n");
  printf("%f   |   %f\n", target[1][1], Layer3Out[1][1]) ;           
  printf("%f   |   %f\n", target[2][1], Layer3Out[2][1]) ;           
  printf("%f   |   %f\n", target[3][1], Layer3Out[3][1]) ;           
  printf("%f   |   %f\n\n", target[4][1], Layer3Out[4][1]) ;           
  printf("Number of calls : %d\n\n",nbappels);
  return 0;
}

