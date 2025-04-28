#include <stdio.h>

#define TAM 10    // Tamanho do tabuleiro
#define NAVIO 3   // Tamanho fixo dos navios
#define HABSZ 5   // Tamanho das matrizes de habilidade (5x5)

void inicializarTabuleiro(int tabuleiro[TAM][TAM]);
void posicionarNavios(int tabuleiro[TAM][TAM]);
void construirCone(int habilidade[HABSZ][HABSZ]);
void construirCruz(int habilidade[HABSZ][HABSZ]);
void construirOctaedro(int habilidade[HABSZ][HABSZ]);
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HABSZ][HABSZ], int origemLinha, int origemColuna);
void exibirTabuleiro(int tabuleiro[TAM][TAM]);

int main() {
    int tabuleiro[TAM][TAM];
    
    // Matrizes para habilidades especiais
    int cone[HABSZ][HABSZ];
    int cruz[HABSZ][HABSZ];
    int octaedro[HABSZ][HABSZ];

    inicializarTabuleiro(tabuleiro);
    posicionarNavios(tabuleiro);

    // Construção das habilidades
    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Aplicação das habilidades
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Cone centrado em (2,2)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz centrada em (5,5)
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);   // Octaedro centrado em (7,7)

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}

// Inicializa todas as posições do tabuleiro como água (0)
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }
}

// Posiciona os quatro navios conforme especificação
void posicionarNavios(int tabuleiro[TAM][TAM]) {
    int sobreposicao = 0;

    // Navio horizontal
    int linhaH = 2, colunaH = 4;
    if (colunaH + NAVIO <= TAM) {
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaH][colunaH + i] == 3) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (int i = 0; i < NAVIO; i++) {
                tabuleiro[linhaH][colunaH + i] = 3;
            }
        }
    }

    // Navio vertical
    sobreposicao = 0;
    int linhaV = 5, colunaV = 1;
    if (linhaV + NAVIO <= TAM) {
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaV + i][colunaV] == 3) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (int i = 0; i < NAVIO; i++) {
                tabuleiro[linhaV + i][colunaV] = 3;
            }
        }
    }

    // Navio diagonal principal
    sobreposicao = 0;
    int linhaD1 = 0, colunaD1 = 0;
    if (linhaD1 + NAVIO <= TAM && colunaD1 + NAVIO <= TAM) {
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaD1 + i][colunaD1 + i] == 3) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (int i = 0; i < NAVIO; i++) {
                tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
            }
        }
    }

    // Navio diagonal secundária
    sobreposicao = 0;
    int linhaD2 = 0, colunaD2 = 9;
    if (linhaD2 + NAVIO <= TAM && colunaD2 - (NAVIO - 1) >= 0) {
        for (int i = 0; i < NAVIO; i++) {
            if (tabuleiro[linhaD2 + i][colunaD2 - i] == 3) sobreposicao = 1;
        }
        if (!sobreposicao) {
            for (int i = 0; i < NAVIO; i++) {
                tabuleiro[linhaD2 + i][colunaD2 - i] = 3;
            }
        }
    }
}

// Constrói a matriz Cone
void construirCone(int habilidade[HABSZ][HABSZ]) {
    for (int i = 0; i < HABSZ; i++) {
        for (int j = 0; j < HABSZ; j++) {
            if (j >= (HABSZ/2 - i) && j <= (HABSZ/2 + i)) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Constrói a matriz Cruz
void construirCruz(int habilidade[HABSZ][HABSZ]) {
    for (int i = 0; i < HABSZ; i++) {
        for (int j = 0; j < HABSZ; j++) {
            if (i == HABSZ/2 || j == HABSZ/2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Constrói a matriz Octaedro
void construirOctaedro(int habilidade[HABSZ][HABSZ]) {
    for (int i = 0; i < HABSZ; i++) {
        for (int j = 0; j < HABSZ; j++) {
            if (abs(i - HABSZ/2) + abs(j - HABSZ/2) <= HABSZ/2) {
                habilidade[i][j] = 1;
            } else {
                habilidade[i][j] = 0;
            }
        }
    }
}

// Aplica a matriz de habilidade no tabuleiro a partir do ponto de origem
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[HABSZ][HABSZ], int origemLinha, int origemColuna) {
    int deslocamento = HABSZ / 2;  // Quantidade de deslocamento do centro da habilidade

    for (int i = 0; i < HABSZ; i++) {
        for (int j = 0; j < HABSZ; j++) {
            int linhaTab = origemLinha + (i - deslocamento);
            int colunaTab = origemColuna + (j - deslocamento);

            // Verifica se a posição está dentro dos limites do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAM && colunaTab >= 0 && colunaTab < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == 0) {
                    tabuleiro[linhaTab][colunaTab] = 5; // Marca área afetada (se não for navio)
                }
            }
        }
    }
}

// Exibe o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\nTabuleiro Final:\n\n   ");
    for (int j = 0; j < TAM; j++) {
        printf("%2d", j);
    }
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%2d ", i);
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == 0) {
                printf(" ~"); // Água
            } else if (tabuleiro[i][j] == 3) {
                printf(" N"); // Navio
            } else if (tabuleiro[i][j] == 5) {
                printf(" *"); // Área de habilidade
            }
        }
        printf("\n");
    }
}
