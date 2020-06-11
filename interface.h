/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#ifndef INTERFACE_H
#define INTERFACE_H

// Imprime locais
void printLocal(local local); 

//Imprime pessoas
void printPessoa(pessoa p);

//Imprime Estado da Simulacao
void printEstadoSimulacao(pamostra dados, int nLocais);

//Imprime historico 
void printHistorico(piteracao historico, int nLocais);

//Menu Simulacao
int menu(); 

#endif /* INTERFACE_H */

