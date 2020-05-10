/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "constantes_estruturas.h"

//Le o ficheiro binario e guarda em memoria dinamica 

plocal leFicheiroLocais(plocal tab_locais, int *total, char *nome_ficheiro) {

    FILE *f;

    f = fopen(nome_ficheiro, "rb");
    if (f == NULL) {
        printf("Erro no acesso ao ficheiro %s\n", nome_ficheiro);
        return 0;
    }

    fseek(f, 0, SEEK_END); //move o cursor para o final do ficheiro

    //ftell devolve tamanho em bytes até ao cursor
    *total = ftell(f) / sizeof (local);

    tab_locais = malloc(sizeof (local) * *total);
    if (tab_locais == NULL) {
        printf("Erro ao alocar o array\n");
        fclose(f);
        return NULL;
    }

    rewind(f); 
    fread(tab_locais, sizeof (local), *total, f);

    fclose(f);
    return tab_locais;
}

int validaID_Locais(plocal locais, int nLocais){

    int i; 
    
    for(i= 0; i<nLocais; i++){
        if(locais[i].id <= 0){
            return 0;
        }
    }

    return 1;
}

//Valida ligacoes, devolve 1 se valido e 0 se invalido
int validaLigacoesLocais(plocal locais, int nLocais) {

    int valida, i, j, k, l;

    for (i = 0; i < nLocais; i++) {
        for (j = 0; j < 3; j++) {
            if(locais[i].liga[j] != -1){
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
                    return 0;
                }
            }
        }
    }
    return 1;
}

//Le o ficheiro de texto e guarda em memoria dinamica
/*void carregaPessoas(pessoa *tab_pessoas, int *total_pessoas){
    
FILE *f; 
 *total_pessoas = 0; 
ppessoa p = tab_pessoas; 

if((f = fopen("pessoasA.txt", "rt")) == NULL)
  {
    printf("Erro no acesso ao ficheiro\n"); 
    return;
   } 
    
while(fscanf(f,"%s %d %s",p->identificador, &p->idade, &p->estado) == 3){
    if(p->estado == 'D'){
        fscanf(f,"%d",&p->dias_infetado);
    }
    p++; 
    (*total_pessoas)++;
}

fclose(f); 

}
 */

// Imprime informacao do ficheiro pessoasA.txt
/*void printPessoas(pessoa *tab_pessoas, int total_pessoas)
{
    int i; 
    
    for(i = 0; i < total_pessoas; i++){   
    printf("Identificador:%s   Idade:%d   Estado:%c\n", tab_pessoas[i].identificador, tab_pessoas[i].idade, tab_pessoas[i].estado); 
    
    if(tab_pessoas[i].estado == 'D')
        printf("Dias Infetado: %d\n", tab_pessoas[i].dias_infetado);
    }
}
 */
