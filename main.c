/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
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

    printEstadoSimulacao(dadosSim, nLocais);

    printf("Pretende iniciar simulação?[Y\\n]\n");
    scanf("%c", &opcao);

    if (opcao != 'Y' && opcao != 'y') {
        return 0;
    }

    // 2. Fase de Simulacao
    
    int localizacao, nPessoas, origem, destino, conta_iteracoes;
    ppessoa doente;

    do {
        printEstadoSimulacao(dadosSim, nLocais);
        i = menu();
        
        switch (i) {
            case 1:
                doente = malloc(sizeof(pessoa));
                if (doente == NULL) {
                    printf("Erro na alocacao de memoria\n");
                    return ERRO_ALOCACAO_MEMORIA;
                }
                doente->estado = 'D';
                
                printf("Indique o id do local a adicionar: ");
                scanf("%d", &localizacao);
                if(excedeCapacidade(dadosSim, nLocais, localizacao, 1) == 1){
                    printf("Local ja se encontra na capacidade maxima\n"); 
                    break;
                }
                
                printf("Indique o identificador do doente:");
                scanf("%s", doente->identificador);
                if(verificaExisteNome(dadosSim, nLocais, doente) == 1) {
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
                if(excedeCapacidade(dadosSim, nLocais, destino, nPessoas) == 1){
                    printf("Local ja se encontra na capacidade maxima\n"); 
                    break;
                }
                else if(validaOrigemDestino(dadosSim,nLocais, origem, destino) == 1){
                    break;
                }
                
                dadosSim = transferePessoas(dadosSim, nLocais, origem, destino, nPessoas);
                break;
                
            case 3: 
                historico = insereHistorico(historico, duplicaAmostra(dadosSim, nLocais));
                dadosSim = avancaIteracao(dadosSim, nLocais);   
                break;
            case 4: 
                do{
                printf("Indique o numero de iterações que pretende recuar:"); 
                scanf("%d", &conta_iteracoes);
                }while(conta_iteracoes < 1 || conta_iteracoes > 3); 
                dadosSim = undoIteracoes(historico, conta_iteracoes); 
                break;
                /*case 5: break; 
                case 6: break;*/
        }
    } while (i != 6);
}
