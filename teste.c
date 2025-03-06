#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char nome[9];
    int porcentagem;
} Doenca;



int main(int argc, char *argv[]) {
    FILE *arquivo = fopen(argv[1], "r"), *saida = fopen(argv[2], "w");
    if (!arquivo || !saida) {
        printf("ERRO\n");
        return 1;
    }

    int tamanhoMinimo,quantidadeDoencas;

    fscanf(arquivo,"%d\n",&tamanhoMinimo);

    char cadeia[31];
    fgets(cadeia,31,arquivo);
    // printf("%s",cadeia);
    
    int tamanhoCadeia = strlen(cadeia);
    // printf("%d\n",tamanhoCadeia);

    //limpa o \n
    cadeia[strcspn(cadeia,"\n")] = 0;

    fscanf(arquivo,"%d\n",&quantidadeDoencas);
    Doenca doencas[quantidadeDoencas];
    char genes[tamanhoCadeia];
    int quantidadeGenes;
    for(int i = 0; i < quantidadeDoencas; i++){
        
        fscanf(arquivo,"%s %d\n",doencas[i].nome,&quantidadeGenes);
        // printf("%s %d\n",doencas[i].nome,quantidadeGenes);

        for(int j = 0; j < quantidadeGenes; j++){
            fscanf(arquivo,"%s",genes);
            // printf("%s\n",genes);
        }


    }







    fclose(arquivo);
    fclose(saida);
    return 0;
}