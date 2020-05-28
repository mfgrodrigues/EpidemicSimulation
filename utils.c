// Trabalho Pratico Programacao - LEI
// DEIS-ISEC 2019-2020

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "constantes_estruturas.h"
#include "utils.h"

void initRandom() {
    srand(time(NULL));
}

int intUniformRnd(int a, int b) {
    return a + rand() % (b - a + 1);
}

int probEvento(float prob) {
    return prob > ((float) rand() / RAND_MAX);
}

ppessoa insereInicio(ppessoa lista, ppessoa nova) {

    nova->prox = lista;
    lista = nova;
    return lista;
}

ppessoa insereFinal(ppessoa lista, ppessoa nova) {

    ppessoa aux;

    if (lista == NULL) {
        return nova;
    }

    aux = lista;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = nova;

    return lista;
}

ppessoa removeElementoLista(ppessoa lista, char ID[]) {

    ppessoa atual, anterior = NULL;

    atual = lista;
    while (atual != NULL && strcmp(atual->identificador, ID) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        return lista;
    }

    if (anterior == NULL) {
        lista = atual->prox;
    } else {
        anterior->prox = atual->prox;
    }

    return lista;
}

void libertaLista(ppessoa lista){
    ppessoa aux;
    
    while (lista != NULL) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }
}
