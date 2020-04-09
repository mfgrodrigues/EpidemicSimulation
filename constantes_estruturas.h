/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#ifndef CONSTANTES_ESTRUTURAS_H
#define CONSTANTES_ESTRUTURAS_H

typedef struct sala local, *plocal; 
struct sala {
    int id;                 // id numerico do local
    int capacidade;         // capacidade maxima
    int liga[3];            // id das ligacoes
};


typedef struct amostra pessoa, *ppessoa;  
struct amostra {
    char identificador[20];     // identificador unico alfanumerio (1 palavra)
    int  idade;                 // idade
    char estado;                // estado: Saudavel, Doente, Imune
    int  dias_infetado;         // caso esteja doente, há quantos dias foi infetado
}; 




#endif /* CONSTANTES_ESTRUTURAS_H */