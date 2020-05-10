/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */


#ifndef FICHEIROS_H
#define FICHEIROS_H

//Valida conteudo locais, devolve 1 se valido e 0 se invalido
int validaLocais(plocal locais, int nLocais);  

//Le o ficheiro binario e guarda em memoria dinamica 
plocal leFicheiroLocais(int *total, char *ficheiroLocais);

//Valida conteudo de pessoa, devolve 1 se valido e 0 se invalido
int validaPessoas(ppessoa nova); 

//Le o ficheiro de texto e guarda em estruturas dinamicas do tipo lista ligada
ppessoa leFicheiroPessoas(char *ficheiroPessoas);

#endif /* FICHEIROS_H */

