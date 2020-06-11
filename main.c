/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 */

#include <stdio.h>
#include <stdlib.h>
#include "constantes_estruturas.h"
#include "utils.h"
#include "preparacao.h"
#include "interface.h"
#include "simulacao.h"

int main(int argc, char** argv) {

    // argc = 3 (nome do programa, ficheiro locais, ficheiro pessoas)
    if (argc != 3) {
        printf("Utilizacao incorreta\n");
    }
    char *ficheiroLocais = argv[1];
    char *ficheiroPessoas = argv[2];
    plocal locais = NULL;
    ppessoa pessoas = NULL;
    pamostra dadosSim = NULL;
    piteracao historico = NULL;
    piteracao it = NULL;
    int i, nLocais;
    char opcao;

    initRandom();

    // 1. Fase de Preparacao

    printf("Fase de Preparacao Iniciada\n");
    printf("A carregar locais...\n");

    locais = leFicheiroLocais(&nLocais, ficheiroLocais);
    if (!locais) {
        return ERRO_FICHEIRO_LOCAIS;
    }

    printf("A carregar pessoas...\n");

    pessoas = leFicheiroPessoas(ficheiroPessoas);
    if (!pessoas) {
        return ERRO_FICHEIRO_PESSOAS;
    }

    dadosSim = distibuiPessoas(locais, nLocais, pessoas);

    free(locais);

    printf("Pretende iniciar simulação?[Y\\n]\n");
    scanf("%c", &opcao);

    if (opcao != 'Y' && opcao != 'y') {
        return 0;
    }

    // 2. Fase de Simulacao

    char op;
    int localizacao, nPessoas, origem, destino, conta_iteracoes;
    ppessoa doente;
    pamostra dadosAux;
    char ficheiro[FICHEIRO];

    do {
        printf("......................................................................................................\n");
        printf("\nAMOSTRA:\n");
        printEstadoSimulacao(dadosSim, nLocais);
        printf("......................................................................................................\n");
        i = menu();


        switch (i) {
            case 1:
                doente = malloc(sizeof (pessoa));
                if (doente == NULL) {
                    printf("Erro na alocacao de memoria\n");
                    return ERRO_ALOCACAO_MEMORIA;
                }
                doente->estado = 'D';
                printf("Indique o id do local a adicionar: ");
                scanf("%d", &localizacao);
                if(existeLocal(dadosSim, nLocais,localizacao) == -1){
                    printf("O local indicado nao pertence a amostra.\n");
                    break;
                }
                if (excedeCapacidade(dadosSim, nLocais, localizacao, 1) == 1) {
                    printf("O local %d ja se encontra na capacidade maxima\n", localizacao);
                    break;
                }

                printf("Indique o identificador do doente:");
                scanf("%s", doente->identificador);
                if (verificaExisteNome(dadosSim, nLocais, doente) == 1) {
                    printf("O identificador inserido ja existe\n");
                    break;
                }
                fflush(stdin);
                printf("Idade: ");
                scanf("%d", &doente->idade);
                printf("Numero de dias de infecao: ");
                scanf("%d", &doente->dias_infetado);
                dadosSim = adicionaPessoaLocalidade(dadosSim, nLocais, localizacao, doente);
                break;

            case 2:
                printf("Indique o numero de pessoas que pretende mover:");
                scanf("%d", &nPessoas);
                printf("Local de origem: ");
                scanf("%d", &origem);
                printf("Local de destino: ");
                scanf("%d", &destino);
                if (excedeCapacidade(dadosSim, nLocais, destino, nPessoas) == 1) {
                    printf("Local ja se encontra na capacidade maxima\n");
                    break;
                } else if (validaOrigemDestino(dadosSim, nLocais, origem, destino) == 1) {
                    break;
                }

                dadosSim = transferePessoas(dadosSim, nLocais, origem, destino, nPessoas);
                break;

            case 3:
                historico = insereHistorico(historico, duplicaAmostra(dadosSim, nLocais));
                dadosSim = avancaIteracao(dadosSim, nLocais);
                break;
                
            case 4:
                do {
                    printf("Indique o numero de iterações que pretende recuar:");
                    scanf("%d", &conta_iteracoes);
                } while (conta_iteracoes < 1 || conta_iteracoes > 3);
                dadosAux = undoIteracoes(&historico, conta_iteracoes, nLocais);
                if(dadosAux == NULL){
                    printf("Nao foi possivel recuar %d iteracoes\n", conta_iteracoes);
                }
                else{
                    libertaLista(dadosSim->pessoas);
                    free(dadosSim);
                    dadosSim = dadosAux;
                }
                break;
                
            case 5: 
                printf("......................................................................................................\n");
                printf("DADOS ESTATISTICOS DA SIMULACAO:\n");
                calculaEstatistica(dadosSim, nLocais,1);
                printf("......................................................................................................\n");
                EstatisticaIteracaoAnt(historico, nLocais); 
                break;
                
            case 6:
                printf("A gerar relatório da simulacao...\n");
                gravaDadosSimulacao(dadosSim, nLocais);
                printf("Pretende guardar a amostra da ultima iteracao da simulacao?[Y\\n]\n");
                fflush(stdin);
                scanf("%c", &op);
                if (op != 'Y' && op != 'y') {
                    libertaLista(dadosSim->pessoas);
                    return EXIT_SUCCESS;
                }
                printf("Indique o nome do ficheiro de texto (nome.txt): ");
                scanf("%s", ficheiro);
                gravaIteracao(ficheiro, dadosSim, nLocais);
                libertaLista(dadosSim->pessoas);
        }
    } while (i != 6);
}
