/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "constantes_estruturas.h"
#include "utils.h"

int validaLocais(plocal locais, int nLocais) {

    int valida, i, j, k, l;

    //valida ID (positivo e unico)
    for (i = 0; i < nLocais; i++) {
        for (j = i + 1; j < nLocais; j++) {
            if (locais[i].id <= 0 || locais[i].id == locais[j].id) {
                printf("Os locais apresentam IDs invalidos.\n");
                return 0;
            }
        }
    }

    //valida ligacoes
    for (i = 0; i < nLocais; i++) {
        for (j = 0; j < 3; j++) {
            if (locais[i].liga[j] != -1) {
                valida = 0;
                for (k = 0; k < nLocais; k++) {
                    if (locais[i].liga[j] == locais[k].id) {
                        for (l = 0; l < 3; l++) {
                            if (locais[k].liga[l] == locais[i].id) {
                                valida++;
                            }
                        }
                    }
                }
                if (valida != 1) {
                    printf("Os locais apresentam ligacoes invalidas.\n");
                    return 0;
                }
            }
        }
    }

    return 1;
}

plocal leFicheiroLocais(int *total, char *ficheiroLocais) {

    FILE *f;
    plocal locais;

    f = fopen(ficheiroLocais, "rb");
    if (f == NULL) {
        printf("Erro no acesso ao ficheiro %s\n", ficheiroLocais);
        return NULL;
    }

    fseek(f, 0, SEEK_END); //move o cursor para o final do ficheiro

    //ftell devolve tamanho em bytes até ao cursor
    *total = ftell(f) / sizeof (local);

    locais = malloc(sizeof (local) * *total);
    if (locais == NULL) {
        printf("Erro ao alocar o array\n");
        fclose(f);
        return NULL;
    }

    //volta ao inicio do ficheiro
    rewind(f);

    fread(locais, sizeof (local), *total, f);

    if (!validaLocais(locais, *total)) {
        return NULL;
    }

    fclose(f);
    return locais;
}

int validaPessoas(ppessoa nova) {

    if (nova->idade <= 0) {
        return 0;
    } else if (nova->estado != 'S' && nova->estado != 'D' && nova->estado != 'I') {
        return 0;
    } else if (nova->estado == 'D' && nova->dias_infetado <= 0) {
        return 0;
    }
    return 1;
}

ppessoa leFicheiroPessoas(char *ficheiroPessoas) {

    ppessoa pessoas = NULL, nova = NULL, aux = NULL;
    int nLidos;
    FILE *f;

    f = fopen(ficheiroPessoas, "rt");
    if (f == NULL) {
        printf("Erro no acesso ao ficheiro %s\n", ficheiroPessoas);
        return NULL;
    }

    do {
        nova = malloc(sizeof (pessoa));
        if (nova == NULL) {
            printf("Erro na alocacao de memoria\n");
            fclose(f);
            return NULL;
        }

        nLidos = fscanf(f, " %s %d %c ", nova->identificador, &(nova->idade), &(nova->estado));
        if (nLidos == 1 || nLidos == 2) {
            printf("Erro no formato do ficheiro\n");
            return NULL;
        }
        if (nLidos == 3) {
            if (nova->estado == 'D') {
                fscanf(f, " %d ", &(nova->dias_infetado));
            }
            if (!validaPessoas(nova)) {
                printf("Dados invalidos\n");
                return NULL;
            }
            nova->prox = NULL;
            if (pessoas == NULL) {
                pessoas = nova;
            } else {
                aux = pessoas;
                while (aux->prox != NULL) {
                    aux = aux->prox;
                }
                aux->prox = nova;
            }
        }
    } while (nLidos == 3);

    fclose(f);
    return pessoas;
}


pamostra distibuiPessoas(plocal locais, int nLocais, ppessoa pessoas) {

    int i, posicao;
    ppessoa aux, nova;

    pamostra dados = malloc(sizeof (amostra) * nLocais);
    if (dados == NULL) {
        printf("Erro na alocacao de memoria\n");
        return NULL;
    }

    for (i = 0; i < nLocais; i++) {
        dados[i].localidade = locais[i];
        dados[i].conta_pessoas = 0; 
    }

    aux = pessoas;
    while (aux != NULL) {

        posicao = intUniformRnd(0, nLocais - 1);
        nova = aux;
        aux = aux->prox;
        dados[posicao].pessoas = insereInicio(dados[posicao].pessoas, nova);
        dados[posicao].conta_pessoas++;
    }
    
    return dados;
}
