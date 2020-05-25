/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#ifndef SIMULACAO_H
#define SIMULACAO_H


//Adiciona uma nova pessoa doente a uma local indicado pelo utilizador
pamostra adicionaPessoaLocalidade(pamostra dadosSim, int nLocais, int localizacao, ppessoa doente); 

//Valida quantidade de pessoas num local, devolve 1 se ja esta na capacidade maxima
int excedeCapacidade(pamostra dadosSim, int nLocais, int localizacao, int nPessoas); 

//verifica se no local ja existe uma pessoa com o identificador inserido
int verificaExisteNome(pamostra dadosSim,int nLocais, ppessoa doente);

//Valida local origem e destino
int validaOrigemDestino(pamostra dadosSim,int nLocais, int origem, int destino);

//Transfere pessoas de um local origem para um local destino inserido pelo utilizdador
pamostra transferePessoas(pamostra dadosSim, int nLocais, int origem, int destino, int Npessoas);

//Calcula Taxa de Disseminacao
void propagacaoDoenca(pamostra dadosSim, int nLocais);

//Calcula Taxa de Recuperacao (por recuperacao ou por ter ultrapassado a duracao maxima da infecao) com probabilidade de ficar imune
void recuperaDoente(pamostra dadosSim, int nLocais); 

//Avanca 1 iteracao na simulacao
pamostra avancaIteracao(pamostra dadosSim, int nLocais);

//Copia conteudo da amostra da simulacao
piteracao duplicaAmostra(pamostra dadosSim, int nLocais);

//Insere iteracao no historico
piteracao insereHistorico(piteracao historico, piteracao it); 

//Volta atras ate 3 iteracoes
pamostra undoIteracoes(piteracao historico, int conta_iteracoes);

#endif /* SIMULACAO_H */

