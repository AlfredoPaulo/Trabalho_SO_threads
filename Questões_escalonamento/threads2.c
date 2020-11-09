#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//modo de compilar Linux gcc q2.c -o q2 -lpthread

#define L 3 //numero de linhas 
#define C 3  //numero de colunas

void organizar();

void mostra(int M[L][C]){
    int i,j;
    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            printf("%3.d",M[i][j]);
        }
        printf("\n");
    }
}

void *preecheS(){
   
    int M[L][C];
    int i,j,x,aux;

    //preenche a matriz
    for(i=0;i<L;i++){
        for(j=0;j<C;j++){
            M[i][j] = 1 + rand() % 10;
        }
    }
    organizar();
    //mostra a matriz normal
    printf("Normal: \n");
    mostra(M);
        organizar();

    //realiza a troca
       for(i=0;i<L;i++){
             aux = M[i][0]; 
            for(j=0;j<C;j++){
               
                 M[i][j] = M[i][C -1 -j];
                 if(j==2){
                     M[i][j] = aux;
                 }
               
        }
    }
        //mostra a modificada 
        printf("Modificada: \n");
        mostra(M);
        organizar();
}


int main(){
    pthread_t t1;
    
    pthread_create(&t1,NULL,preecheS,NULL);
    pthread_join(t1,NULL); //espera até a thread acabar




    return 0;
}

void organizar(){
    printf("=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
}