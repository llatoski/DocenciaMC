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
#define L           3     //Lado da Rede
#define N          (L*L)  //Número de Sítios
#define MCS         100 //MCS para as medidas
/***************************************************************
 *                            FUNCTIONS                       
 **************************************************************/
void inicializacao(void); //Inicializa o sistema
void sweep(void); //Evolui
/***************************************************************
 *                         GLOBAL VARIABLES                   
 **************************************************************/
double s[N][N],pi[N],pi2[N];
/***************************************************************
 *                          MAIN PROGRAM  
 **************************************************************/
int main(void){
 
  inicializacao();

  for (int i=0;i<MCS;i++)  {
      if (i%10==0) {
        printf("Passo %d: ",i);
        for (int j=0; j<N; j++){
          printf("%.16f, ",pi[j]);
        } 
      printf("\n");
    }
    sweep();
  }

}
/***************************************************************
 *                        INICIALIZAÇÃO  
 **************************************************************/
void inicializacao(void) {

  for (int i=0; i<N; i++){ //Zero tudo que preciso zerar aqui
    pi[i]=0;
    pi2[i]=0;
    for (int j=0; j<N; j++){
      s[i][j]=0.;
    }
  }
  
  pi[0]=1; //Condições iniciais podem mexer a vontade aqui
  pi2[0]=1;

  //Faço checagem de vizinhança para gerar a matriz de transição independente do tamanho. Caso seja um sítio das extremidades, para cada extremidade ele soma a si próprio uma probabilidade 1/4.
  for (int sitio = 0; sitio < N; sitio++) {   
      if (sitio + 1 > N - 1) //Caso esteja na extremidade da direita
        s[sitio][sitio]+=0.25;
      else
        s[sitio][sitio+1]+=0.25;
      if (sitio - 1 < 0) //Caso esteja na extremidade esquerda
        s[sitio][sitio]+=0.25;
      else
        s[sitio][sitio-1]+=0.25;
      if (sitio - L < 0) //Caso esteja na extremidade superior
        s[sitio][sitio]+=0.25;
      else
        s[sitio][sitio-L]+=0.25;
      if (sitio + L > N - 1) //Caso esteja na extremidade inferior
        s[sitio][sitio]+=0.25;
      else
        s[sitio][sitio+L]+=0.25;
  }
}
/****************************************************************
 *               MCS routine
 ***************************************************************/
void sweep() { //Função que realiza a evolução do sistema de acordo com o Algoritmo 1.7 do livro
  for (int i=0; i<N; i++){
    pi2[i]=0; 
    for (int j=0; j<N; j++){ 
      pi2[i]+=s[j][i]*pi[j];
    }
  }
  for (int i=0; i<N; i++){
    pi[i]=pi2[i];
  }
}