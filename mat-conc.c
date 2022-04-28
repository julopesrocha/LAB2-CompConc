/*
Programa Concorrente | Efetua  a multiplicação das matrizes de entrada 
de forma sequencial e armazena o resultado em uma variavel separada.
- Considerando matrizes quadradas
*/

// recebe int mat1 ( numero dim ) int mat 2
#include<stdlib.h>
#include<stdio.h>

float *matriz1; // 1º matriz de entrada
float *matriz2; // 2º matriz de entrada
float *resultado; // matriz de saída

int main(int arg1, int arg2) {
    int dim1; // dimensão da 1º matriz de entrada
    int dim2; // dimensão da 2º matriz de entrada

    /* Passo 1: leitura e avaliação de params de entrada */
    if(arg1<2){
        printf("Digite a <dimensão da matriz>\n");
        return 1;
    }
    dim1 = arg1;
    dim2 = arg2;
    
    /* Passo 2: alocação de memoria para a estrutura de dados */
    matriz1 = (float *) malloc(sizeof(float) * dim1 * dim1); //qnts bytes quer alocar na memoria
    if(matriz1 == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    matriz2 = (float *) malloc(sizeof(float) * dim1 * dim1); //qnts bytes quer alocar na memoria
    if(matriz2 == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    resultado = malloc(sizeof(float) * dim1 * dim1); //qnts bytes quer alocar na memoria
    if(resultado == NULL) {
        printf("ERRO --malloc\n");
        return 2;
    }

    /* Passo 3: inicialização das estruturas de dados*/

    // inicializando a 1º matriz
    for(int i=0; i<dim1; i++){
        for(int j=0; j<dim1; j++){
            matriz1[i*dim1+j] = 1; 
            /* 
            - mat[i][j] i*dim = primeiro elemento da linha
            - utilizando a função rand() para gerar numeros aleatorios para a matriz
            */ 
        }
    }

    // inicializando a 2º matriz
    for(int i=0; i<dim2; i++){
        for(int j=0; j<dim2; j++){
            matriz2[i*dim2+j] = 1; //mat[i][j] i*dim = primeiro elemento da linha
        }
    }

    // inicializando a 3º matriz = identidade
    for(int i=0; i<dim2; i++){
        for(int j=0; j<dim1; j++){
            resultado[i*dim2+j] = 1; //mat[i][j] i*dim = primeiro elemento da linha
        }
    }
    /* visto que as duas matrizes sao quadradas, a matriz identidade terá sua dimensão baseada
    no número de colunas da primeira, e de nº de linhas da segunda */

    /* Passo 4: multiplicação das matrizes */
    for(int i=0; i<dim2; i++){
        for(int j=0; j<dim1; j++){
            resultado[i*dim2+j] += matriz1[dim1*j+i] * matriz2[i*dim2+j];
        }
    }

    /* Passo 5: exibição dos resultados (matriz x vetor = vetor) */
    puts("1º Matriz de Entrada:");
    for(int i=0; i<dim1; i++){
        for(int j=0; j<dim1; j++){
            printf("%.lf ", matriz1[i*dim1+j]);
        }
        puts("");
    }

    puts("2º Matriz de Entrada:");
    for(int i=0; i<dim2; i++){
        for(int j=0; j<dim2; j++){
            printf("%.lf ", matriz2[i*dim2+j]);
        }
        puts("");
    }

    puts("Matriz Identidade:");
    for(int i=0; i<dim2; i++){
        for(int j=0; j<dim2; j++){
            printf("%.lf ", resultado[i*dim2+j]);
        }
        puts("");
    }
    /* Passo 6: liberação da memória */

    free(matriz1);
    free(matriz2);
    free(resultado);

    return 0;
}