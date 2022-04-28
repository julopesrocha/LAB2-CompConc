/*
Programa Sequencial | Efetua  a multiplicação das matrizes de entrada 
de forma sequencial e armazena o resultado em uma variavel separada.
- Considerando matrizes quadradas
*/

#include<stdlib.h>
#include<stdio.h>
#include"timer.h"

float *matriz1; // 1º matriz de entrada
float *matriz2; // 2º matriz de entrada
float *resultado; // matriz de saída

/*
    optei pela função da main em receber somente um argumento que ditaria a dimensão das duas matrizes 
    devido às definições necessárias pro exercício pois elas devem ser quadradas;
    
    E em segundo lugar, pois a dimensão da matriz identidade é definida pela quantidade de colunas
    da primeira matriz x quantidade de linhas da segunda matriz, sendo elas necessariamente iguais, 
    formando uma matriz quadrada
*/

int main(int arg1, char*arg2[]) {

    int dim; // dimensão da 1º matriz de entrada
    double inicio, fim, delta; // variáveis para medição de tempo

    GET_TIME(inicio);
    /* Passo 1: leitura e avaliação de params de entrada */

    if(arg1<2){
        printf("Digite a <dimensão da matriz>\n");
        return 1;
    }
    dim = atoi(arg2[1]);
    
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

    resultado = malloc(sizeof(float) * dim * dim); //qnts bytes quer alocar na memoria
    if(resultado == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    /* Passo 3: inicialização das estruturas de dados*/

    // inicializando a 1º matriz
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matriz1[i*dim+j] = (rand() %100); //mat[i][j] i*dim = primeiro elemento da linha
        }
    }

    // inicializando a 2º matriz
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            matriz2[i*dim+j] = (rand() %100); //mat[i][j] i*dim = primeiro elemento da linha
        }
    }
    
    // inicializando a 3º matriz = identidade
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            resultado[i*dim+j] = 1; 
        }
    }
    
    /* visto que as duas matrizes sao quadradas, a matriz identidade terá sua dimensão baseada
    no número de colunas da primeira, e de nº de linhas da segunda */
    GET_TIME(fim);
    delta = fim-inicio;
    printf("Tempo Inicialização: %lf \n\n", delta);

    /* Passo 4: multiplicação das matrizes */
    GET_TIME(inicio);

    float temp; // variavel temporaria para multiplicação das matrizes

    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            temp=0.0;
            for(int k=0; k<dim; k++){
                temp = temp + matriz1[dim*i+k] * matriz2[dim*k+j]; 
            }
            resultado[i*dim+j]=temp;
        }
    }

    GET_TIME(fim);
    delta = fim-inicio;
    printf("Tempo multiplicação: %lf \n\n", delta);

    /* Passo 5: exibição dos resultados (matriz x vetor = vetor) */
    GET_TIME(inicio);
    
    puts("1º Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%.lf ", matriz1[i*dim+j]);
        }
        puts("");
    }
    printf("\n");

    puts("2º Matriz de Entrada:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%.lf ", matriz2[i*dim+j]);
        }
        puts("");
    }
    printf("\n");

    puts("Matriz Identidade:");
    for(int i=0; i<dim; i++){
        for(int j=0; j<dim; j++){
            printf("%.lf ", resultado[i*dim+j]);
        }
        puts("");
    }
    printf("\n");

    /* Passo 6: liberação da memória */

    free(matriz1);
    free(matriz2);
    free(resultado);

    GET_TIME(fim);
    delta = fim-inicio;
    printf("Tempo de Saída: %lf \n\n", delta);
    printf("Tempo Total:  ");

    return 0;
}