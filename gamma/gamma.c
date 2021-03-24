/***************************************************************
 *                            INCLUDES                      
 **************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

/****************************************************************
 *                            DEFINITIONS                      
 ***************************************************************/
#define MCS         10000 //MCS para as medidas
/***************************************************************
 *                            FUNCTIONS                       
 **************************************************************/
void sweep(double,double); //Monte Carlo
/***************************************************************
 *                         GLOBAL VARIABLES                   
 **************************************************************/
float gama,chi,soma,soma2;
/***************************************************************
 *                          MAIN PROGRAM  
 **************************************************************/
int main(void){
  int seed = time(0);
  srand(seed);

  printf("\n\nExecutavel para encontrar integral do tipo x**gamma com amostragem por importancia:\n\n");
  printf("Escolha gama e chi de acordo com a relacao (2*gamma-chi) > -1:\n\n");
  scanf("%f", &gama);
  scanf("%f", &chi);


  soma = 0;
  for (int i=0;i<MCS;i++)  {
    sweep(gama,chi);
  }

  printf("--------------------------------------------\n");
  printf("Gamma | Chi | Soma/N\n");
  printf(" %.1f | %.1f | %.3f\n",gama,chi,(double)soma/MCS);
  printf("--------------------------------------------\n");  
}

/****************************************************************
 *               MCS routine
 ***************************************************************/
void sweep(double _gama,double _chi) {
  double r;
  double exp1 = _gama-_chi; //Simplifico os expoentes
  double exp2 = 1./(_chi + 1);
  r = pow((double)rand()/RAND_MAX,exp2); //Gero o número aleatório na potência exp2 de acordo com o algoritmo 1.30
  double x = pow(r,exp1); //Faço o número obtido elevado a potência exp1 
  soma+=x; 
}