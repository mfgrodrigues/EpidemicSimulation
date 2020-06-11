/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constantes_estruturas.h"
#include "utils.h"
#include "preparacao.h"
#include "interface.h"
#include "simulacao.h"

pamostra adicionaPessoaLocalidade(pamostra dadosSim, int nLocais, int localizacao, ppessoa pessoa) {

    int i;

    for (i = 0; i < nLocais; i++) {
        if (localizacao == dadosSim[i].localidade.id) {
            dadosSim[i].pessoas = insereInicio(dadosSim[i].pessoas, pessoa);
            dadosSim[i].conta_pessoas++;
        }
    }
    return dadosSim;
}

int existeLocal(pamostra dadosSim, int nLocais, int localizacao) {

    int i;

    for (i = 0; i < nLocais; i++) {
        if (localizacao == dadosSim[i].localidade.id) {
            return i;
        }
    }
    return -1;
}

int excedeCapacidade(pamostra dadosSim, int nLocais, int localizacao, int nPessoas) {

    int i;

    for (i = 0; i < nLocais; i++) {
        if (localizacao == dadosSim[i].localidade.id && dadosSim[i].conta_pessoas >= dadosSim[i].localidade.capacidade - nPessoas) {
            return 1;
        }
    }
    return 0;
}

int verificaExisteNome(pamostra dadosSim, int nLocais, ppessoa pessoa) {

    int i;
    ppessoa aux;

    for (i = 0; i < nLocais; i++) {
        aux = dadosSim[i].pessoas;
        while (aux != NULL && strcmp(pessoa[i].identificador, aux->identificador) != 0) {
            aux = aux->prox;
        }
        if (aux != NULL) {
            return 1;
        }
    }

    return 0;
}

int validaOrigemDestino(pamostra dadosSim, int nLocais, int origem, int destino) {

    int i, j, k, check_locais = 0, check_liga = 0;

    //verifica se o local de origem e destino fazem parte dos locais da amostra
    for (i = 0; i < nLocais; i++) {
        if (origem == dadosSim[i].localidade.id) {
            check_locais++;
            break;
        }
    }

    for (j = 0; j < nLocais; j++) {
        if (destino == dadosSim[j].localidade.id) {
            check_locais++;
            break;
        }
    }

    if (check_locais != 2) {
        printf("ID Local invalido\n");
        return 1;
    }

    //Verifica ligacoes
    for (k = 0; k < 3; k++) {
        if (dadosSim[i].localidade.liga[k] == dadosSim[j].localidade.id) {
            check_liga = 1;
        }
    }

    if (check_liga != 1) {
        printf("Ligacoes invalidas\n");
        return 1;
    }

    return 0;
}

pamostra transferePessoas(pamostra dadosSim, int nLocais, int origem, int destino, int Npessoas) {

    int i, j, k, posicao, contador;
    ppessoa aux;

    for (i = 0; i < nLocais; i++) {
        if (origem == dadosSim[i].localidade.id) {

            for (j = 0; j < Npessoas; j++) {
                contador = 0;
                posicao = intUniformRnd(0, dadosSim[i].conta_pessoas - 1);
                aux = dadosSim[i].pessoas;
                while (contador != posicao) {
                    aux = aux->prox;
                    contador++;
                }
                dadosSim[i].pessoas = removeElementoLista(dadosSim[i].pessoas, aux->identificador);
                dadosSim[i].conta_pessoas--;
                dadosSim = adicionaPessoaLocalidade(dadosSim, nLocais, destino, aux);
            }
        }
    }
    return dadosSim;
}

void propagacaoDoenca(pamostra dadosSim, int nLocais) {

    int i, infetado;
    ppessoa doente, aux;

    for (i = 0; i < nLocais; i++) {

        doente = dadosSim[i].pessoas;
        while (doente != NULL) {
            if (doente->estado == 'D' && doente->dias_infetado > 1) {
                aux = dadosSim[i].pessoas;
                while (aux != NULL) {
                    if (aux->estado == 'S') {
                        infetado = probEvento(DISSEMINACAO);
                        if (infetado == 1) {
                            aux->estado = 'D';
                            aux->dias_infetado = 1;
                        }
                    }
                    aux = aux->prox;
                }
            }
            doente = doente->prox;
        }
    }
}

void recuperaDoente(pamostra dadosSim, int nLocais) {

    int i, recuperado, imune;
    float prob_recuperacao;
    ppessoa doente;


    for (i = 0; i < nLocais; i++) {

        doente = dadosSim[i].pessoas;
        while (doente != NULL) {
            if (doente->estado == 'D') {
                prob_recuperacao = 1 / (doente->idade);
                recuperado = probEvento(prob_recuperacao);
                if (recuperado == 1) {
                    doente->estado = 'S';
                    doente->dias_infetado = 0;
                }
                if (doente->dias_infetado == (doente->idade / 10) + 5) {
                    doente->estado = 'S';
                    doente->dias_infetado = 0;
                }
                if (doente->estado == 'S') {
                    imune = probEvento(IMUNIDADE);
                    if (imune == 1) {
                        doente->estado = 'I';
                    }
                }
            }
            doente = doente->prox;
        }
    }
}

pamostra avancaIteracao(pamostra dadosSim, int nLocais) {

    int i;
    ppessoa aux;

    for (i = 0; i < nLocais; i++) {
        aux = dadosSim[i].pessoas;
        while (aux != NULL) {
            if (aux->estado == 'D') {
                aux->dias_infetado++;
            }
            aux = aux->prox;
        }
    }

    propagacaoDoenca(dadosSim, nLocais);

    recuperaDoente(dadosSim, nLocais);

    return dadosSim;
}

piteracao duplicaAmostra(pamostra dadosSim, int nLocais) {

    int i;
    piteracao it;
    ppessoa aux, nova;

    it = malloc(sizeof (iteracao));
    if (it == NULL) {
        printf("Erro na alocacao de memoria\n");
        return NULL;
    }

    it->dados = malloc(sizeof (amostra) * nLocais);
    if (it->dados == NULL) {
        printf("Erro na alocacao de memoria\n");
        return NULL;
    }

    for (i = 0; i < nLocais; i++) {
        it->dados[i].localidade = dadosSim[i].localidade;
        it->dados[i].conta_pessoas = dadosSim[i].conta_pessoas;
        aux = dadosSim[i].pessoas;
        while (aux != NULL) {
            nova = malloc(sizeof (pessoa));
            if (nova == NULL) {
                printf("Erro na alocacao de memoria\n");
                return NULL;
            }
            *nova = *aux;
            nova->prox = NULL;
            it->dados[i].pessoas = insereFinal(it->dados[i].pessoas, nova);
            aux = aux->prox;
        }
    }
    return it;
}

piteracao insereHistorico(piteracao historico, piteracao it) {

    int amostras = 0;
    piteracao aux;

    historico = insereAmostraInicio(historico, it);

    aux = historico;
    while (aux != NULL) {
        amostras++;
        aux = aux->prox;
    }

    if (amostras > 3) {
        historico = removeUltimaAmostra(historico);
    }

    return historico;
}

pamostra undoIteracoes(piteracao *historico, int conta_iteracoes, int nLocais) {

    int contador = 0;
    piteracao aux, anterior;
    pamostra atual;

    aux = *historico;
    
    //verifica se existe a possibilidade de recuar o numero de iteracoes introduzido pelo utilizador
    while (aux != NULL) {
        contador++;
        aux = aux->prox; 
    }
    
    if(contador != conta_iteracoes){
        return NULL;
    }
    
    //recua as iteracoes pretendidas e liberta as iteracoes nao necessarias
    contador = 1;
   
    while (aux != NULL && contador != conta_iteracoes) {
        contador++;
        anterior = aux;
        aux = aux->prox;
        libertaIteracao(anterior);
    }
    
    *historico = aux->prox; 
    atual = duplicaAmostra(aux->dados, nLocais)->dados;
    libertaIteracao(aux);
    return atual;
}

void contaISD(ppessoa dadosSim, int *imunes, int *saudaveis, int *doentes) {

    int i;
    ppessoa aux;
    *imunes = 0;
    *saudaveis = 0;
    *doentes = 0;

    aux = dadosSim;
    while (aux != NULL) {
        if (aux->estado == 'I') {
            (*imunes)++;
        }
        if (aux->estado == 'S') {
            (*saudaveis)++;
        }
        if (aux->estado == 'D') {
            (*doentes)++;
        }
        aux = aux->prox;
    }
}

void printEstatistica(amostra dadosSim, int imunes, float tImunes, int saudaveis, float tSaudaveis, int doentes, float tDoentes) {

    int i;
    printf("LOCAL:%d\tTOTAL DE PESSOAS:%d\n", dadosSim.localidade.id, dadosSim.conta_pessoas);

    if (dadosSim.conta_pessoas) {
        printf("Imunes:%d \tSaudaveis:%d \tDoentes: %d\n", imunes, saudaveis, doentes);
        if (imunes > 0) {
            printf("Taxa de Imunes:%.1f%%\n", tImunes);
        }
        if (saudaveis > 0) {
            printf("Taxa de Saudaveis:%.1f%%\n", tSaudaveis);
        }
        if (doentes > 0) {
            printf("Taxa de Infetados:%.1f%%\n", tDoentes);
        }
    }
    printf("\n");
}

void calculaEstatistica(pamostra dadosSim, int nLocais, int print) {

    int i, imunes, saudaveis, doentes, nPessoas = 0, contaI = 0, contaS = 0, contaD = 0, j = 0;
    float tImunes, tSaudaveis, tDoentes;
    float totalI, totalS, totalD;

    for (i = 0; i < nLocais; i++) {
        if (dadosSim[i].conta_pessoas) {
            contaISD(dadosSim[i].pessoas, &imunes, &saudaveis, &doentes);
            if (imunes > 0) {
                tImunes = ((float) imunes / dadosSim[i].conta_pessoas)*100;
                contaI += imunes;
            }
            if (saudaveis > 0) {
                tSaudaveis = ((float) saudaveis / dadosSim[i].conta_pessoas)*100;
                contaS += saudaveis;
            }
            if (doentes > 0) {
                tDoentes = ((float) doentes / dadosSim[i].conta_pessoas)*100;
                contaD += doentes;
            }
            nPessoas += dadosSim[i].conta_pessoas;
        }
        if (print == 1) {
            printEstatistica(dadosSim[i], imunes, tImunes, saudaveis, tSaudaveis, doentes, tDoentes);
        }
    }

    totalI = ((float) contaI / nPessoas)*100;
    totalS = ((float) contaS / nPessoas)*100;
    totalD = ((float) contaD / nPessoas)*100;


    printf("\nTaxa Total de Imunes: %.1f%%\tTaxa Total de Saudaveis: %.1f%%\tTaxa Total de Infetados: %.1f%%\n", totalI, totalS, totalD);
}

void EstatisticaIteracaoAnt(piteracao historico, int nLocais) {

    piteracao aux = historico;
    int it = 0;
    float i, s, d;

    if (aux == NULL) {
        return;
    } else {
        while (aux != NULL) {
            printf("\nITERACAO -%d:\n", ++it);
            calculaEstatistica(aux->dados, nLocais, 0);
            aux = aux->prox;
        }
    }
}

void gravaDadosSimulacao(pamostra dadosSim, int nLocais) {

    FILE *f;
    int i, imunes, saudaveis, doentes;

    f = fopen("report.txt", "wt");
    if (f == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    for (i = 0; i < nLocais; i++) {
        fprintf(f, "Local:%d\tTotal de pessoas:%d\n", dadosSim[i].localidade.id, dadosSim[i].conta_pessoas);
        contaISD(dadosSim[i].pessoas, &imunes, &saudaveis, &doentes);
        fprintf(f, "Imunes:%d \tSaudaveis:%d \tDoentes: %d\n\n", imunes, saudaveis, doentes);
    }

    fclose(f);
}

void gravaIteracao(char *ficheiro, pamostra dadosSim, int nLocais) {

    FILE *f;
    int i;
    ppessoa aux;

    f = fopen(ficheiro, "wt");

    if (f == NULL) {
        printf("Erro no acesso ao ficheiro\n");
        return;
    }

    for (i = 0; i < nLocais; i++) {
        fprintf(f, "\nLocal:%d\tTotal de pessoas:%d\n", dadosSim[i].localidade.id, dadosSim[i].conta_pessoas);
        aux = dadosSim[i].pessoas;
        while (aux != NULL) {
            fprintf(f, "%s\t%d\t%c\t", aux->identificador, aux->idade, aux->estado);
            if (aux->estado == 'D') {
                fprintf(f, "%d", aux->dias_infetado);
            }
            fprintf(f, "\n");
            aux = aux->prox;
        }
    }

    fclose(f);
}
