#include <stdio.h>
#include <string.h>

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

    for (int i = 0; i < tamanhoTexto; i++) {
        while (j > 0 && texto[i] != padrao[j]) {
            j = tabela[j - 1];  // Ajusta o índice do padrão usando a tabela de prefixos
        }
        if (texto[i] == padrao[j]) {
            j++;
        }
        if (j == tamanhoPadrao) {
            // Padrão encontrado
            return i - j + 1;  // Retorna a posição onde o padrão começa no texto
        }
    }

    return -1;  // Padrão não encontrado
}

int main() {
    
    const char *texto = "ABABDABACDABABCABAB";
    const char *padrao = "ABABCABAB";
    int tamanhoTexto = strlen(texto);
    int tamanhoPadrao = strlen(padrao);

    int posicao = algoritmoKMP(texto, tamanhoTexto, padrao, tamanhoPadrao);

    if (posicao != -1) {
        printf("Padrão encontrado na posição: %d\n", posicao);
    } else {
        printf("Padrão não encontrado.\n");
    }

    return 0;
}