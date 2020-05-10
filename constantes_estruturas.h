/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#ifndef CONSTANTES_ESTRUTURAS_H
#define CONSTANTES_ESTRUTURAS_H

#define N_LIGA 3
#define N_IDENTIFICADOR 20

//Definicao de erros
#define ERRO_FICHEIRO_LOCAIS 1
#define ERRO_FICHEIRO_PESSOAS 2 

typedef struct sala local, *plocal; 
struct sala {
    int id;                 // id numerico do local
    int capacidade;         // capacidade maxima
    int liga[N_LIGA];       // id das ligacoes
};

typedef struct amostra pessoa, *ppessoa;  
struct amostra {
    char identificador[N_IDENTIFICADOR];     // identificador unico alfanumerio (1 palavra)
    int  idade;                              // idade
    char estado;                             // estado: Saudavel, Doente, Imune
    int  dias_infetado;                      // caso esteja doente, há quantos dias foi infetado
    ppessoa prox;                            // ponteiro para o proximo elemento
};

#endif /* CONSTANTES_ESTRUTURAS_H */
