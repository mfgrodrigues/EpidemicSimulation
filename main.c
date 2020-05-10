/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "constantes_estruturas.h"
#include "ficheiros.h"
#include "interface.h"

int main(int argc, char** argv) {
    
    // argc = 3 (nome do programa, ficheiro locais, ficheiro pessoas)
    if (argc != 3) {
        printf("Utilizacao incorreta\n");
    }
    char *ficheiroLocais = argv[1];
    char *ficheiroPessoas = argv[2];
    plocal locais = NULL;
    ppessoa pessoas = NULL;
    int nLocais;
    char opcao;

    initRandom(); 
    
    // 1. Fase de Preparacao

    printf("Fase de Preparacao Iniciada\n");
    printf("A carregar locais...\n");

    locais = leFicheiroLocais(&nLocais, ficheiroLocais);
    if (!locais) {
        return ERRO_FICHEIRO_LOCAIS;
    }

    printLocais(locais, nLocais);

    printf("A carregar pessoas...\n");

    pessoas = leFicheiroPessoas(ficheiroPessoas);
    if(!pessoas){
        return ERRO_FICHEIRO_PESSOAS;
    }
    
    printf("Listar Pessoas?[Y\\n]\n");
    scanf("%c", &opcao);

    if (opcao == 'Y' || opcao == 'y') {
        printPessoas(pessoas);
    }

    //2. Fase de Simulacao

    free(locais);
    free(pessoas);
}

