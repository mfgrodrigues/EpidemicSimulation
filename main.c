/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "constantes_estruturas.h"
#include "ficheiros.h"

void printLocais(plocal locais, int nLocais) {

    int i, j;
    for (i = 0; i < nLocais; i++) {
        printf("Local: %d\tCapacidade: %d\tLigacoes:", (locais + i)->id, (locais + i)->capacidade);
        for (j = 0; j < 3; j++) {
            if ((locais + i)->liga[j] != -1) {
                printf("%d ", (locais + i)->liga[j]);
            }
        }
        printf("\n");
    }
}

int main(int argc, char** argv) {

    // argc = 3 (nome do programa, ficheiro locais, ficheiro pessoas)
    if (argc != 3) {
        printf("Utilizacao incorreta\n");
    }
    char *nome_ficheiro = argv[1];
    plocal locais;
    int total_locais, valido;
    char opcao;

    // 1. Fase de Preparacao
    
    printf("Fase de Preparacao Iniciada\n");
    printf("A carregar locais...\n");

    locais = leFicheiroLocais(locais, &total_locais, nome_ficheiro);
    valido = validaLigacoes(locais, total_locais); 

    printLocais(locais, total_locais);

    if(valido == 0){
        printf("Os locais apresentam ligacoes invalidas.\n");
        return 0;
    }
    //printf("A carregar pessoas...\n");

    /*carregaPessoas(tab_pessoas, argv[2]); 
    
    printf("Listar Pessoas?[Y\\n]\n"); 
    scanf("%c", &opcao); 
    
    if(opcao == 'Y' || opcao == 'y')
    {
       
            printPessoas(tab_pessoas, total_pessoas); 
                
    }
    
    
    
    
    //2. Fase de Simulacao
    
     */

    free(locais); 
}

