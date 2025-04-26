#include <stdio.h>

#define TAM 10         // Tamanho do tabuleiro (10x10)
#define NAVIO 3        // Tamanho fixo dos navios

int main() {
    int tabuleiro[TAM][TAM];

    // 1. Inicializa o tabuleiro com 0 (água)
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // 2. Coordenadas iniciais dos navios (definidas no código)
    // navioHorizontal[0] = linha, navioHorizontal[1] = coluna
    int navioHorizontal[2] = {2, 4}; // Começa na linha 2, coluna 4
    int navioVertical[2]   = {5, 1}; // Começa na linha 5, coluna 1

    // 3. Valida se o navio horizontal cabe no tabuleiro
    if (navioHorizontal[1] + NAVIO > TAM) {
        printf("Erro: navio horizontal ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    // 4. Valida se o navio vertical cabe no tabuleiro
    if (navioVertical[0] + NAVIO > TAM) {
        printf("Erro: navio vertical ultrapassa o limite do tabuleiro.\n");
        return 1;
    }

    // 5. Verifica se as posições já estão ocupadas (sobreposição)
    int sobreposicao = 0;
    for (int i = 0; i < NAVIO; i++) {
        if (tabuleiro[navioHorizontal[0]][navioHorizontal[1] + i] == 3 ||
            tabuleiro[navioVertical[0] + i][navioVertical[1]] == 3) {
            sobreposicao = 1;
            break;
        }
    }

    if (sobreposicao) {
        printf("Erro: os navios estão se sobrepondo.\n");
        return 1;
    }

    // 6. Posiciona navio horizontal
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[navioHorizontal[0]][navioHorizontal[1] + i] = 3;
    }

    // 7. Posiciona navio vertical
    for (int i = 0; i < NAVIO; i++) {
        tabuleiro[navioVertical[0] + i][navioVertical[1]] = 3;
    }

    // 8. Exibe o tabuleiro
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
