#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    char nome[9];
    int porcentagem;
} Doenca;


void countingSort(Doenca *doencas, int quantidade) {
    const int maximoPercentual = 100;
    Doenca saida[quantidade];  
    int contador[maximoPercentual+ 1];  

    memset(contador, 0, sizeof(contador));

    for (int i = 0;i < quantidade; i++) {
        contador[doencas[i].porcentagem]++;
    }

    for (int i = maximoPercentual- 1; i >= 0; i--) {
        contador[i] += contador[i + 1];
    }

    for (int i = quantidade-1; i >= 0;i--) {
        saida[contador[doencas[i].porcentagem]- 1] = doencas[i];
        contador[doencas[i].porcentagem]--;
    }

    memcpy(doencas,saida, quantidade*sizeof(Doenca));
}


// Função para calcular a tabela de prefixos (tabela de falhas)
void calcularTabelaPrefixos(const char *padrao, int tamanhoPadrao, int *tabela) {
    int comprimento = 0;  // Comprimento do prefixo mais longo que também é sufixo
    tabela[0] = 0;        // A primeira posição sempre será 0

    for (int i = 1; i < tamanhoPadrao; i++) {
        while (comprimento > 0 && padrao[i] != padrao[comprimento]) {
            comprimento = tabela[comprimento - 1];
        }
        if (padrao[i] == padrao[comprimento]) {
            comprimento++;
        }
        tabela[i] = comprimento;
    }
}

// Função principal do algoritmo KMP
int algoritmoKMP(const char *texto, int tamanhoTexto, const char *padrao, int tamanhoPadrao) {
    int tabela[tamanhoPadrao];  // Tabela de prefixos
    calcularTabelaPrefixos(padrao, tamanhoPadrao, tabela);

    int j = 0;  // Índice para o padrão
    float limite = tamanhoPadrao*0.9;

    for (int i = 0; i < tamanhoTexto; i++) {
        while (j > 0 && texto[i] != padrao[j]) {
            j = tabela[j - 1];  // Ajusta o índice do padrão usando a tabela de prefixos
        }
        if (texto[i] == padrao[j]) {
            j++;
        }
        if (j>=limite) {
            // Padrão encontrado
            return 1;  // Retorna a posição onde o padrão começa no texto
        }
    }

    return 0;  // Padrão não encontrado
}


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

        int soma;
        for(int j = 0; j < quantidadeGenes; j++){
            fscanf(arquivo,"%s",genes);
            // printf("%s\n",genes);
            soma += algoritmoKMP(cadeia,tamanhoCadeia,genes,strlen(genes));
            // printf("Gene: %s, Posição: %d\n",genes,posicao);
        }
        doencas[i].porcentagem = (int)round(((float)soma/quantidadeGenes)*100);
        // printf("Porcentagem: %d\n",doencas[i].porcentagem);

    }

    countingSort(doencas,quantidadeDoencas);
    for(int i = 0; i < quantidadeDoencas; i++){
            fprintf(saida,"%s %d\n",doencas[i].nome,doencas[i].porcentagem);
        
    }






    fclose(arquivo);
    fclose(saida);
    return 0;
}