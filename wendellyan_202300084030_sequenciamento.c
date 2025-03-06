#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
    int porcentagem;
    char nome[9];
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


void calcularTabelaPrefixos(const char *padrao, int tamanhoPadrao, int *tabela) {
    int comprimento = 0;
    tabela[0] = 0;
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

int algoritmoKMP(const char *texto, int tamanhoTexto, const char *padrao, int tamanhoPadrao, int tamanhoMinimo, int *tabela) {
    int j = 0;
    calcularTabelaPrefixos(padrao, tamanhoPadrao, tabela);

    float limite = tamanhoPadrao*0.9;
    // printf("%.0f\n",limite);

    for (int i = 0; i < tamanhoTexto; i++) {
        while (j > 0 && texto[i] != padrao[j]) {
            j = tabela[j-1];
        }
        if (texto[i] == padrao[j]) {
            j++;
        }
        if (j >= limite) {
            j = tabela[j-1];
            return 1;
        }
    }
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *arquivo = fopen(argv[1], "r"), *saida = fopen(argv[2], "w");
    if (!arquivo || !saida) {
        printf("ERRO\n");
        return 1;
    }

    int tamanhoSubcadeia, quantidadeDoenca;
    fscanf(arquivo, "%d\n", &tamanhoSubcadeia);

    char cadeia[50000];
    fgets(cadeia,50000, arquivo);
    int tamanhoCadeia = strlen(cadeia)-1;
    // printf("%d\n", tamanhoCadeia);
    cadeia[strcspn(cadeia,"\n")] = 0;

    fscanf(arquivo, "%d", &quantidadeDoenca);

    Doenca doencas[quantidadeDoenca];

    int tabela[1001];
    char gene[tamanhoCadeia];
    for (int i = 0; i < quantidadeDoenca; i++) {
        int quantidadeGenes;
        fscanf(arquivo,"%s %d", doencas[i].nome, &quantidadeGenes);

        int contador = 0;
        for (int j = 0; j < quantidadeGenes; j++) {
            fscanf(arquivo,"%s", gene);

            contador += algoritmoKMP(cadeia, tamanhoCadeia, gene, strlen(gene), tamanhoSubcadeia, tabela);
            // printf("%d\n", contador);
            
        }
 
        doencas[i].porcentagem = (int)round(((float)contador/quantidadeGenes)*100);
    }

    countingSort(doencas, quantidadeDoenca);

    for (int i = 0; i < quantidadeDoenca; i++) {
        fprintf(saida,"%s->%d%%\n",doencas[i].nome, doencas[i].porcentagem);
    }

    fclose(arquivo);
    fclose(saida);

    return 0;
}
