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
    char *nome_ficheiro = argv[1];
    plocal locais;
    int nLocais, valido;
    char opcao;

    // 1. Fase de Preparacao
    
    printf("Fase de Preparacao Iniciada\n");
    printf("A carregar locais...\n");

    locais = leFicheiroLocais(locais, &nLocais, nome_ficheiro);
    
    valido = validaID_Locais(locais, nLocais); 
    if(valido == 0){
        printf("Os locais apresentam IDs negativos.\n");
        return 0;
    }
    
    valido = validaLigacoesLocais(locais, nLocais);
    if(valido == 0){
        printf("Os locais apresentam ligacoes invalidas.\n");
        return 0;
    }
    
    printLocais(locais, nLocais);

    
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

