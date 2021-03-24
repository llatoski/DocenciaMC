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
#define T           1.1
#define MCS_EQ      100000
#define MCSTEPS     1000000
#define SAMPLES     1
#define PRODUCTION  1
#define Q           2
/***************************************************************
 *                            FUNCTIONS                       
 **************************************************************/
void inicializacao(void);
void sweep(void);
void states(int);
void openfiles(void);
void vizualizacao(void);
void metropolis(int);
/***************************************************************
 *                         GLOBAL VARIABLES                   
 **************************************************************/
FILE *fp1,*fp2,*fp3;
int M, Et, s[L2],viz[L2][4],hist[L2*L2],hist2[Q*L2], seed;
/***************************************************************
 *                          MAIN PROGRAM  
 **************************************************************/
int main(void){
  for(int s = 0; s < SAMPLES; s++) {
    seed = time(0);
    inicializacao();
    openfiles();
    for(int i = 0; i < MCS_EQ; i++) {
      sweep();
    }
    for(int i = 0; i < MCSTEPS; i++) {
      sweep();
      states(Q);
      fprintf(fp3,"%d %.6f %.6f\n", i,(double)Et/L2,(double)M/L2);
      hist[Et+L2*L2]++;
      hist2[M+L2]++;
    }
    for(int i = 0; i < L2*L2; i++){
      if(hist[i]!=0)fprintf(fp1,"%d %d\n",i-L2*L2,hist[i]);
    } 
    for(int i = 0; i < Q*L2; i++){
      if(hist2[i]!=0)fprintf(fp2,"%d %d\n",i-L2,hist2[i]);
    } 
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
  }
}

/***************************************************************
 *                        INICIALIZAÇÃO  
 **************************************************************/
 void inicializacao(void) {
   srand(seed);
   for (int i = 0; i < L2*L2; i++) {
     hist[i]=0;
   }
   for (int i = 0; i < Q*L2; i++) {
     hist2[i]=0;
   }
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
   states(Q);
   return;
 }
/****************************************************************
 *                         MCS routine                                    
 ***************************************************************/
void sweep(void) {
  for (int i = 0; i<L2; i++) {
    int site = rand()%L2;
    metropolis(site);
  }
  return;
}

void states(int _Q){
  Et=0;
  M=0;
  if(_Q!=2){
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
void metropolis(int _site) {
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
    double ALPHA = exp(-dE/(K*T));
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

  sprintf(output_file1,"Ehist-lg-%d-T-%.1f-seed-%d.dsf",L,T,identifier);
  fp1 = fopen(output_file1,"w");
  fflush(fp1);

  sprintf(output_file1,"Mhist-lg-%d-T-%.1f-seed-%d.dsf",L,T,identifier);
  fp2 = fopen(output_file1,"w");
  fflush(fp2);

  sprintf(output_file1,"serie-lg-%d-T-%.1f-seed-%d.dsf",L,T,identifier);
  fp3 = fopen(output_file1,"w");
  fflush(fp3);

  return;
}
/**************************************************************
 *                       Vizualização                   
 *************************************************************/
void vizualizacao(void) {
  int l;
  printf("pl '-' matrix w image\n");
  for(l = L2-1; l >= 0; l--) {
    printf("%d ", s[l]);
    if( l%L == 0 ) printf("\n");
  }
  printf("e\ne\n");
}
