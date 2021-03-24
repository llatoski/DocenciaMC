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
#define L           20
#define J           1.
#define L2          (L*L)
#define K           1
#define MCS_EQ      100000
#define MCSTEPS     1000000
#define SAMPLES     1
#define PRODUCTION  1
#define Q           2
/***************************************************************
 *                            FUNCTIONS                       
 **************************************************************/
void initizalize(void);
void sweep(double);
void states(void);
void openfiles(void);
void visualize(void);
void metropolis(int,double);
/***************************************************************
 *                         GLOBAL VARIABLES                   
 **************************************************************/
FILE *fp1;
int M, Et, s[L2],viz[L2][4],seed;
double MM,EEt;
/***************************************************************
 *                          MAIN PROGRAM  
 **************************************************************/
int main(void){
  double T=1.;
  openfiles();
  while (T<=3.0) {
    EEt=0;
    MM=0;
    seed = time(0);
    initizalize();
    for(int i = 0; i < MCS_EQ; i++) {
      sweep(T);
    }
    for(int i = 0; i < MCSTEPS; i++) {
      sweep(T);
      states();
      EEt+=(double)Et/L2;
      MM+=(double)M/L2;
      //visualize();
    }
    fprintf(fp1,"%.2f %.2f %.2f", T,EEt,MM);
    T+=0.1;
  }
  fclose(fp1);
}

/***************************************************************
 *                        Initialization
 **************************************************************/
 void initizalize(void) {
   srand(seed);
   for (int i = 0; i < L2; i++) {
     s[i]=(int)rand()%Q;
   }
   for (int i = 0; i < L2; i++) {
     if (i + 1 > L2 - 1)
       viz[i][0] = (i + 1) - L2;
     else
       viz[i][0] = i + 1;
     if (i - 1 < 0)
       viz[i][1] = L2 + (i - 1);
     else
       viz[i][1] = i - 1;
     if (i - L < 0)
       viz[i][2] = L2 + (i - L);
     else
       viz[i][2] = i - L;
     if (i + L > L2 - 1)
       viz[i][3] = (i + L) - L2;
     else
       viz[i][3] = i + L;
   }
   states();
   return;
 }
/****************************************************************
 *                         MCS routine                                    
 ***************************************************************/
void sweep(double _T) {
  for (int i = 0; i<L2; i++) {
    int site = rand()%L2;
    metropolis(site,_T);
  }
  return;
}

/****************************************************************
 *                           Observables                                   
 ***************************************************************/

void states(void){
  Et=0;
  M=0;
  if(Q!=2){
    for (int i = 0; i < L2; i++) {
      if(s[i]==s[viz[i][0]])Et-=J;
      if(s[i]==s[viz[i][1]])Et-=J;
      if(s[i]==s[viz[i][2]])Et-=J;
      if(s[i]==s[viz[i][3]])Et-=J;
      M+=s[i];  
    }
  }
  else{
    for (int i = 0; i < L2; i++) {

      if(s[i]==s[viz[i][0]])Et-=J;
      if(s[i]==s[viz[i][1]])Et-=J;
      if(s[i]==s[viz[i][2]])Et-=J;
      if(s[i]==s[viz[i][3]])Et-=J;

      if(s[i]==0)M-=1;  
      if(s[i]==1)M+=1;  

    }
  }
}
/****************************************************************
 *                         Metropolis                                    
 ***************************************************************/
void metropolis(int _site, double _T) {
  int E1=0,E2=0;
  int k = rand()%Q;
  while(k==s[_site])k = rand()%Q;
  for (int i = 0; i < 4; i++){
    if(s[_site]==s[viz[_site][i]]){
      E1-=J;
    }
  }
  for (int i = 0; i < 4; i++){
    if(k==s[viz[_site][i]]){
      E2-=J;
    }
  }
  double dE = E2 - E1;
  if(dE <= 0){
    s[_site] = k;
  }
  else {
    double r = (double)rand()/RAND_MAX;
    double ALPHA = exp(-dE/(K*_T));
    if(r<=ALPHA) {
      s[_site] = k;
    }
    else return;
  }
}

/**************************************************************
 *               Open output files routine                   
 *************************************************************/
void openfiles(void) {
  char output_file1[100];
  int identifier;

  identifier = seed;

  sprintf(output_file1,"evolutionT-lg-%d-seed-%d.dsf",L,identifier);
  fp1 = fopen(output_file1,"w");
  fflush(fp1);

  return;
}
/**************************************************************
 *                       Vizualization                  
 *************************************************************/
void visualize(void) {
  int l;
  printf("pl '-' matrix w image\n");
  for(l = L2-1; l >= 0; l--) {
    printf("%d ", s[l]);
    if( l%L == 0 ) printf("\n");
  }
  printf("e\ne\n");
}
