#include <stdio.h>
#include <stdlib.h>


struct processos {
    int id;                   /* Identifição do processo*/              
 int surto;                /* Tempo de duração do processo*/
    int prioridade;           
    int execucao;             /* Tempo de execução do processo*/
    int espera;               /* Tempo de espera do processo*/
    struct processos *prox;
};

struct processos *init_processos (int id, int surto, int prioridade);
void listprocs (struct processos *proc);
void rr (struct processos *proc, int quantum, int Qprocessos,int teste);

 
int main (void) {
    
    struct processos *plist, *ptmp;
    int N =1 ;
    int i,M = 1; //M = quantum
    int X,Y,Z;
    int teste = 0;
 while (N!=0){
     printf("Digite a quantidade de processos: ");
     scanf("%d",&N);
     if(N==0){
         break;
     }

     for(i=0;i<N;i++){
         printf("Tempo de chegada de P[%d]: ",i+1);
         scanf("%d",&X); //tempo de   ingresso do processo
         printf("Tempo de duração de P[%d]: ",i+1);
         scanf("%d",&Y);

         if(i == 0){
    		plist       = init_processos(i, Y, X);	
		}
		else if(i == 1){
			plist->prox = init_processos(i,  Y, X); ptmp = plist->prox;
		}
		else {
			ptmp->prox  = init_processos(i,  Y, X); ptmp = ptmp->prox;
		}
     }

     listprocs(plist);
       teste+=1;
     rr(plist,M,N,teste);
   

     
 }
 
    
    
    
    return(0);
};

struct processos *init_processos (int id, int surto, int prioridade) {
    struct processos *proc;
 proc = (struct processos*)malloc(sizeof(struct processos)); 
  if (proc == NULL) {
        printf("Erro Fatal: Falha Alocacao de memoria.\nFinalizar.\n");
        exit(1);
    };
    proc->id = id;
    proc->surto = surto;
    proc->prioridade = prioridade;
    proc->execucao = 0;
    proc->espera = 0;
    proc->prox = NULL;
    return(proc);
};


void listprocs (struct processos *proc) {
  struct processos *tmp = proc;
  printf("\tListagem de Processos\n");
  printf("\n");
  while (tmp != NULL) {
    printf("Processo: %d\tPrioridade: %d\tSurto: %d\n", tmp->id, tmp->prioridade, tmp->surto);
    tmp = tmp->prox;
  };
  printf("\n\n");
 };


void rr (struct processos *proc, int quantum, int Qprocessos,int teste) {
  int jobsremain, passes;
  float mediaEsp, mediaExec; 
  float somaMediaExec = 0, somaMediaEsp=0;
  struct processos *copia, *tmpsrc, *tmp, *slot;
  printf("\tEscalonamento Round-Robin - Quantum: %d\n", quantum);
  printf("\n");
  tmpsrc = proc;
  copia = tmp = NULL;
  while (tmpsrc != NULL) {
    if (copia == NULL) {
    copia = init_processos(tmpsrc->id, tmpsrc->surto, tmpsrc->prioridade);
    tmp = copia;
    } else {
    tmp->prox = init_processos(tmpsrc->id, tmpsrc->surto, tmpsrc->prioridade);
    tmp = tmp->prox;
    };
    tmpsrc = tmpsrc->prox;
  };
  /* Programa rotina de análise de prioridade  */
  jobsremain = 2;
  slot = NULL;
  while (jobsremain) {
    jobsremain = 0;
    /* Seleciona o próximo processo efetuando sua alocação */
    if (slot == NULL) {
    slot = copia;
    jobsremain = 2;
    } else {
    passes = 0;
    do {
      if (slot->prox == NULL) {
        passes++;
        slot = copia;
      } else {
        slot = slot->prox;
      };
    } while (passes <= 3 && slot->surto == slot->execucao);
    if (passes <= 3) {
      jobsremain = 2;
    };
    };
    /* Executa um ciclo */
    tmp = copia;
    while (tmp != NULL) {
    if (tmp->surto > tmp->execucao) {
      if (tmp == slot) {
        tmp->execucao += quantum;
      } else {
        tmp->espera += quantum;
      };
    };
    tmp = tmp->prox;
    };
  };
  /* Exibe os resultados e elimina as replicações */
  tmp = copia;
  while (tmp != NULL) {
    printf("Processo: %d\tSurto: %d\tEspera: %d\tRetorno: %d\n", tmp->id, tmp->surto, tmp->espera, tmp->execucao + tmp->espera);
    tmpsrc = tmp;
    somaMediaEsp += tmp->espera ;
    somaMediaExec +=  tmp->execucao;
    tmp = tmp->prox;
    free(tmpsrc);
  };
  printf("\n");
  mediaEsp = somaMediaEsp/Qprocessos;
  mediaExec = somaMediaExec/Qprocessos;
  
  printf("Teste %d\n",teste);
  printf("Tempo médio de execução: %.2fs \n", somaMediaExec);
  printf("Tempo médio de espera: %.2fs\n",mediaExec);
};

