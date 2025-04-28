#include <stdio.h>

#define TAM 10     // Tamanho do tabuleiro (10x10)
#define NAVIO 3    // Tamanho fixo dos navios

int main() {
    int tabuleiro[TAM][TAM];

    // 1. Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Coordenadas iniciais dos navios
    // Formato: {linha, coluna}
    int navioHorizontal[2] = {2, 4};  // Navio na horizontal
    int navioVertical[2]   = {5, 1};  // Navio na vertical
    int navioDiagonal1[2]  = {0, 0};  // Diagonal principal (linha == coluna)
    int navioDiagonal2[2]  = {0, 9};  // Diagonal secundária (linha + coluna == 9)

    int sobreposicao = 0;

    // --- Validação e posicionamento do navio horizontal ---
    if (navioHorizontal[1] + NAVIO > TAM) {
        printf("Erro: navio horizontal ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO; i++) {
        if (tabuleiro[navioHorizontal[0]][navioHorizontal[1] + i] == 3) {
            sobreposicao = 1;
        }
    }
    if (sobreposicao) {
        printf("Erro: sobreposição detectada no navio horizontal.\n");
        return 1;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[navioHorizontal[0]][navioHorizontal[1] + i] = 3;
    }

    // --- Validação e posicionamento do navio vertical ---
    sobreposicao = 0;
    if (navioVertical[0] + NAVIO > TAM) {
        printf("Erro: navio vertical ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO; i++) {
        if (tabuleiro[navioVertical[0] + i][navioVertical[1]] == 3) {
            sobreposicao = 1;
        }
    }
    if (sobreposicao) {
        printf("Erro: sobreposição detectada no navio vertical.\n");
        return 1;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[navioVertical[0] + i][navioVertical[1]] = 3;
    }

    // --- Validação e posicionamento do navio diagonal 1 (principal) ---
    sobreposicao = 0;
    if (navioDiagonal1[0] + NAVIO > TAM || navioDiagonal1[1] + NAVIO > TAM) {
        printf("Erro: navio diagonal 1 ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO; i++) {
        if (tabuleiro[navioDiagonal1[0] + i][navioDiagonal1[1] + i] == 3) {
            sobreposicao = 1;
        }
    }
    if (sobreposicao) {
        printf("Erro: sobreposição detectada no navio diagonal 1.\n");
        return 1;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[navioDiagonal1[0] + i][navioDiagonal1[1] + i] = 3;
    }

    // --- Validação e posicionamento do navio diagonal 2 (secundária) ---
    sobreposicao = 0;
    if (navioDiagonal2[0] + NAVIO > TAM || navioDiagonal2[1] - (NAVIO - 1) < 0) {
        printf("Erro: navio diagonal 2 ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    for (int i = 0; i < NAVIO; i++) {
        if (tabuleiro[navioDiagonal2[0] + i][navioDiagonal2[1] - i] == 3) {
            sobreposicao = 1;
        }
    }
    if (sobreposicao) {
        printf("Erro: sobreposição detectada no navio diagonal 2.\n");
        return 1;
    }
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[navioDiagonal2[0] + i][navioDiagonal2[1] - i] = 3;
    }

    // 3. Exibe o tabuleiro
    printf("\nTabuleiro:\n\n   ");
    for (int j = 0; j < TAM; j++) {
        printf("%2d", j); // Cabeçalho das colunas
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i); // Número da linha
        for (int j = 0; j < TAM; j++) {
            printf("%2d", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
