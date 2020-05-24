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
    for (j = 0; i < nLocais; i++) {
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

    int i, recuperado;
    float prob_recuperacao;
    ppessoa doente;


    for (i = 0; i < nLocais; i++) {

        doente = dadosSim[i].pessoas;
        while (doente != NULL) {
            if (doente->estado == 'D' && doente->dias_infetado == (doente->idade / 10) + 5) {
                doente->estado = 'S';
                doente->dias_infetado = 0;
            } else if (doente->estado == 'D') {
                prob_recuperacao = 1 / (doente->idade);
                recuperado = probEvento(prob_recuperacao);
                if (recuperado == 1) {
                    doente->estado = 'S';
                    doente->dias_infetado = 0;
                }
            }
        }
        doente = doente->prox;
    }
}

void pessoaImune(pamostra dadosSim, int nLocais) {

    int i, imune;
    ppessoa psaudavel;

    for (i = 0; i < nLocais; i++) {

        psaudavel = dadosSim[i].pessoas;
        while (psaudavel != NULL) {
            if (psaudavel->estado == 'S') {
                imune = probEvento(IMUNIDADE);
                if (imune == 1) {
                    psaudavel->estado = 'I';
                }
            }
        }
    }
}

pamostra avancaIteracao(pamostra dadosSim, int nLocais) {

    int i;
    ppessoa aux;
    
    printf("incremento");
    
    for (i = 0; i < nLocais; i++) {
        aux = dadosSim[i].pessoas;
        while (aux != NULL) {
            if (aux->estado == 'D') {
                aux->dias_infetado++;
                aux = aux->prox;
            }
        }
    }
    
    printf("doenca"); 
    
    propagacaoDoenca(dadosSim, nLocais);

    printf("recuperacao");
    recuperaDoente(dadosSim, nLocais);
    
    printf("imunidade"); 
    pessoaImune(dadosSim, nLocais);

    return dadosSim;
}


/*void apresentaEstatistica(pamostra dadosSim, int nlocais){


}*/





