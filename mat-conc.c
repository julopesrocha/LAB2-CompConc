/*
Programa Concorrente | Efetua  a multiplicação das matrizes de entrada 
de forma sequencial e armazena o matriz_concorrente em uma variavel separada.
- Considerando matrizes quadradas
*/

// recebe int mat1 ( numero dim ) int mat 2
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include"timer.h"

float *matriz1; // 1º matriz de entrada
float *matriz2; // 2º matriz de entrada
float *matriz_concorrente; // matriz de saída
int nthreads; // numero de threads

typedef struct {
    int id; //identificador do elemento que a thread irá processar
    int dim; // dimensão das estruturas de entrada
} tArgs;

// função executada pelas threads
void * multiplica(void *arg){
    tArgs *args = (tArgs*) arg;
    printf("Thread %d\n", args->id);

    // para dar os saltos de intercalação
    float temp; // variavel temporaria para multiplicação das matrizes

    for(int i=args->id; i<args->dim; i+=nthreads){
        for(int j=0; j<args->dim; j++){
            temp=0.0;
            for(int k=0; k<args->dim; k++){
                temp = temp + matriz1[args->dim*i+k] * matriz2[args->dim*k+j]; 
            }
            matriz_concorrente[i*args->dim+j]=temp;
        }
    }
    pthread_exit(NULL);
}


int main(int argc, char* argv[]) {
    int dim;
    pthread_t *tid;
    tArgs *args; // id locais e dimensões
    double inicio, fim, delta;

    /* Passo 1: leitura e avaliação de params de entrada */
    if(argc<2){
        printf("Digite %s <dimensão da matriz> <numero de threads>\n", argv[0]);
        return 1;
    }
    
    dim = atoi(argv[1]);
    nthreads = atoi(argv[2]);
    
    if(nthreads > dim) {
        nthreads = dim;
    }; 

    /* Passo 2: alocação de memoria para a estrutura de dados */
    matriz1 = (float *) malloc(sizeof(float) * dim * dim); //qnts bytes quer alocar na memoria
    if(matriz1 == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    matriz2 = (float *) malloc(sizeof(float) * dim * dim); //qnts bytes quer alocar na memoria
    if(matriz2 == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    matriz_concorrente = malloc(sizeof(float) * dim * dim); //qnts bytes quer alocar na memoria
    if(matriz_concorrente == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    /* Passo 3: inicialização das estruturas de dados*/

    // inicializando a 1º matriz e a 2º
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matriz1[i*dim+j] = (rand() % 10); 
            matriz2[i*dim+j] = (rand() % 10); 
            /* 
            - mat[i][j] i*dim = primeiro elemento da linha
            - utilizando a função rand() para gerar numeros aleatorios para a matriz
            */ 
        }
    }

    /* Passo 4: multiplicação das matrizes */
        // 4.1 : alocação das estruturas
    tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
    if(tid == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
    if(args == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }
        // 4.2 : criação das threads

    for(int i=0; i<nthreads; i++){
        (args+i)->id = i;
        (args+i)->dim = dim;
        if(pthread_create(tid+i, NULL, multiplica, (void*) (args+i))){
            puts("ERRO--Pthread_create");
            break;
            return 3;
        }
    }

        // 4.3 : espera pelo término das threads
    for(int i=0; i<nthreads; i++){
        pthread_join(*(tid+i), NULL);
    }

    /* Passo 5: exibição dos matriz_concorrentes (matriz x vetor = vetor) */
    puts("1º Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%.lf ", matriz1[i*dim+j]);
        }
        puts("");
    }

    puts("2º Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%.lf ", matriz2[i*dim+j]);
        }
        puts("");
    }

    puts("Matriz Identidade:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%.lf ", matriz_concorrente[i*dim+j]);
        }
        puts("");
    }
    /* Passo 6: liberação da memória */

    free(matriz1);
    free(matriz2);
    free(matriz_concorrente);

    return 0;
}