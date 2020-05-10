/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constantes_estruturas.h"
#include "interface.h"

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

void printPessoas(ppessoa pessoas){
    
    while(pessoas != NULL){
        printf("%s\t%d\t%c", pessoas->identificador, pessoas->idade, pessoas->estado);
        if(pessoas->estado == 'D'){
            printf("\t%d",pessoas->dias_infetado);
        }
        printf("\n");
        
        pessoas = pessoas->prox;
    }
}


