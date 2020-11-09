#include <stdio.h>
#include <stdlib.h>
/* Estrutura */
struct processos {
    int id;                     /* Identifição do processo*/              
 int surto;                     /* Tempo de duração do processo*/
    int prioridade;           
    int execucao;               /* Tempo de execução do processo*/
    int espera;                 /* Tempo de espera do processo*/
    struct processos *prox;
};
/* Declarações de Protótipo de função */
struct processos *init_processos (int id, int surto, int prioridade);

void prioridade (struct processos *proc, int N);


int main (void) {

    struct processos *plist, *ptmp;
    int N=1;
	int teste = 1;
    int X,Y,Z;
  while (N!=0){
	printf("Digite o valor de N: ");
    scanf("%d", &N);
    
    
    for(int i = 0; i < N; i++) {
    	scanf("%d", &X);
    	scanf("%d", &Y);
    	scanf("%d", &Z);
    	
    	if(i == 0){
    		plist       = init_processos(X, Y, Z);	
		}
		else if(i == 1){
			plist->prox = init_processos(X,  Y, Z); ptmp = plist->prox;
		}
		else {
			ptmp->prox  = init_processos(X,  Y, Z); ptmp = ptmp->prox;
		}
	}
   
  	printf("\n\n\n\n");
    printf("Teste %d \n", teste);
	teste+=1;
    
    prioridade(plist, N);
    

    while (plist != NULL) {
        ptmp = plist;
        plist = plist->prox;
        free(ptmp);
    };
  }
    
   
    return(0);
};
/* Inicialização de entrada da lista de processos*/
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

void prioridade (struct processos *proc, int N) {
	float tempoExecucao;
	float tempoEspera;
	int tempo, inicio, fim, maior;
	struct processos *copia, *tmpsrc, *tmp, *maiorprimeiro;

   printf("\n");

     /* Replicando Lista de Processos */
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
  /* Programa Principal */
  tempo = 0;
  while (copia != NULL) {

          /* Localiza o proximo processo */
	    maiorprimeiro = NULL;
	    maior = copia->prioridade;
	    tmp = copia->prox;
	    tmpsrc = copia;
    while (tmp != NULL) {
    if (tmp->prioridade < maior) {
		maior = tmp->prioridade;
	    maiorprimeiro = tmpsrc;
    };
	    tmpsrc = tmp;
	    tmp = tmp->prox;
    };
     if (maiorprimeiro == NULL) {
    /* Verifica se o primeiro processo possui maior prioridade */
		    inicio = tempo;
		    tempo += copia->surto;
		    fim = tempo;
		    
		    printf("P%d\t", copia->id);
		    
		    tempoExecucao += inicio;
		    tempoEspera += fim;
		    tmpsrc = copia->prox;
		    free(copia);
		    copia = tmpsrc;
    } else {
    /* Verifica se o primeiro processo não possui maior prioridade */
		    tmp = maiorprimeiro->prox;
		    inicio = tempo;
		    tempo += tmp->surto;
		    fim = tempo;
		    printf("%d\t", tmp->id);
			tempoExecucao += inicio;
		    tempoEspera += fim;
		    maiorprimeiro->prox = tmp->prox;
		    free(tmp);
    };
  };
	printf("\n\n");
	printf("Tempo médio de execução : %.2f\n",tempoExecucao/N );
	printf("Tempo médio de  espera: %.2f\n",tempoEspera/N);
};