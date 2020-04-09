/* 
 * Author: Maria de Fatima Gomes Rodrigues (2019112924)
 * Created on April 7, 2020, 10:40 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "constantes_estruturas.h"
#include "ficheiros.h"



int main(int argc, char** argv){
   
    local tab_locais[5]; 
    pessoa tab_pessoas[10]; 
    int total_locais, total_pessoas; 
    char opcao; 
    
    
    // 1. Fase de Preparacao
    
    printf("Fase de Preparacao Iniciada\n"); 
    
    printf("A carregar locais...\n"); 
    
    carregaLocais(tab_locais, &total_locais); 
    
    printf("A carregar pessoas...\n"); 
    
    carregaPessoas(tab_pessoas, &total_pessoas); 
    
    printf("Listar Pessoas?[Y\\n]\n"); 
    scanf("%c", &opcao); 
    
    if(opcao == 'Y' || opcao == 'y')
    {
       
            printPessoas(tab_pessoas, total_pessoas); 
                
    }
    
    
    
    
    //2. Fase de Simulacao
    
    
    
    
}

