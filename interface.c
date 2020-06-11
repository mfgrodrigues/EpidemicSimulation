/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constantes_estruturas.h"
#include "interface.h"
#include "simulacao.h"

void printLocal(local local) {

    int i;

    printf("Local: %d\tCapacidade: %d\tLigacoes:", local.id, local.capacidade);
    for (i = 0; i < N_LIGA; i++) {
        if (local.liga[i] != -1) {
            printf("%d ", local.liga[i]);
        }
    }
    printf("\n");
}

void printPessoa(pessoa p) {

    printf("%-15s\t%d\t%c", p.identificador, p.idade, p.estado);
    if (p.estado == 'D') {
        printf("\t%d", p.dias_infetado);
    }
    printf("\n");
}

void printEstadoSimulacao(pamostra dados, int nLocais) {

    for (int i = 0; i < nLocais; i++) {

        printLocal(dados[i].localidade);

        ppessoa aux = dados[i].pessoas;
        while (aux != NULL) {
            printPessoa(*aux);
            aux = aux->prox;
        }
        printf("\n");
    }
}

int menu() {

    int i;

    puts("1. ADICIONAR DOENTE");
    puts("2. TRANSFERIR PESSOAS");
    puts("3. AVANCAR 1 ITERACAO NA SIMULACAO");
    puts("4. VOLTAR ATRAS X ITERACOES (UNDO X)");
    puts("5. APRESENTAR ESTATISTICA");
    puts("6. TERMINAR SIMULACAO");
    puts("Escolha uma opcao:");

    do {
        scanf("%d", &i);
    } while (i < 1 || i > 6);

    return i;
}

