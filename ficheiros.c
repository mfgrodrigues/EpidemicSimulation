/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include "constantes_estruturas.h"

//Le o ficheiro binario e guarda em memoria dinamica 
void carregaLocais(local *tab_locais, int *total){

    FILE *f; 
    local aux; 
    int i; 
    *total = 0; 
    
    
    if((f = fopen("E1.bin", "rb")) == NULL)
    {
        printf("Erro no acesso ao ficheiro\n"); 
        return;
    }
    
    fread(&aux, sizeof(local), 1, f); 
    while(feof(f) == 0)
    {
        tab_locais[(*total)++] = aux; 
        printf("Local ID: %d, Capacidade: %d\n", aux.id, aux.capacidade);
        for(i = 0; i < 3; i++)
        {
            printf("Ligacao: %d\n", aux.liga[i]); 
        }
        fread(&aux, sizeof(local), 1, f); 
        
    }
    
    fclose(f);

}


//Le o ficheiro de texto e guarda em memoria dinamica
void carregaPessoas(pessoa *tab_pessoas, int *total_pessoas){
    
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


// Imprime informacao do ficheiro pessoasA.txt
void printPessoas(pessoa *tab_pessoas, int total_pessoas)
{
    int i; 
    
    for(i = 0; i < total_pessoas; i++){   
    printf("Identificador:%s   Idade:%d   Estado:%c\n", tab_pessoas[i].identificador, tab_pessoas[i].idade, tab_pessoas[i].estado); 
    
    if(tab_pessoas[i].estado == 'D')
        printf("Dias Infetado: %d\n", tab_pessoas[i].dias_infetado);
    }
}

