#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//modo de compilar no Linux:  gcc q1.c -o q1 -lpthread

#define T 10 //Valor do contador de inicialização e final

void *contador(void *args){
    int *cont = (int *)(args);
    int i;

    if(*cont ==1){
        printf("Thread 1 executando...\n");
          for(i=1;i<T+1;i++){
            printf("%d \n",i);
    }

    }else{
        printf("Thread 2 executando...\n");
        for(i=T;i>0;i--){
            printf("%d \n",i);
        }
    }
  
}




int main(){
    pthread_t t1,t2;
    int cont = 1;
    int cont2 = 2;

    pthread_create(&t1,NULL,contador, (void *)(&cont));
    pthread_create(&t2,NULL,contador, (void *)(&cont2));

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);



    exit(0);
}