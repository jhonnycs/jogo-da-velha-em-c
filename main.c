#include <stdio.h>

typedef struct {
    char nome[20];
    char letra;
    int vitorias;
} Jogador;

void imprimirTabuleiro(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%c ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

char verificarVencedor(char tabuleiro[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] &&
            tabuleiro[i][1] == tabuleiro[i][2] &&
            tabuleiro[i][0] != ' ') {
            return tabuleiro[i][0];
        }

        if (tabuleiro[0][i] == tabuleiro[1][i] &&
            tabuleiro[1][i] == tabuleiro[2][i] &&
            tabuleiro[0][i] != ' ') {
            return tabuleiro[0][i];
        }
    }

    if (tabuleiro[0][0] == tabuleiro[1][1] &&
        tabuleiro[1][1] == tabuleiro[2][2] &&
        tabuleiro[0][0] != ' ') {
        return tabuleiro[0][0];
    }

    if (tabuleiro[0][2] == tabuleiro[1][1] &&
        tabuleiro[1][1] == tabuleiro[2][0] &&
        tabuleiro[0][2] != ' ') {
        return tabuleiro[0][2];
    }
    return ' ';
}

void realizarJogada(char tabuleiro[3][3], int linha, int coluna, char jogador) {
    tabuleiro[linha][coluna] = jogador;
}

void obterDadosJogador(Jogador *jogador) {
    printf("Digite o nome do jogador: ");

    scanf("%s", jogador->nome);

    printf("Escolha sua letra (um caractere): ");

    scanf(" %c", &jogador->letra);
}

void atualizarRanking(Jogador *jogadores, int numJogadores) {
    printf("\nRanking:\n");

    for (int i = 0; i < numJogadores; i++) {
        printf("%s - Vitórias: %d\n", jogadores[i].nome, jogadores[i].vitorias);
    }
}

void salvarEmArquivo(Jogador *jogadores, int numJogadores, int rodada) {
    FILE *arquivo = fopen("resultados.txt", "a");

    if (arquivo != NULL) {
        fprintf(arquivo, "\n---- Resultados da Rodada %d ----\n", rodada);

        for (int i = 0; i < numJogadores; i++) {
            fprintf(arquivo, "%s - Vitórias: %d\n", jogadores[i].nome,
                    jogadores[i].vitorias);
        }

        fclose(arquivo);

    } else {
        printf("Erro ao abrir o arquivo para salvar resultados.\n");
    }
}

int main() {
    const int MAX_JOGADORES = 2;
    const int NUM_RODADAS = 5;

    Jogador jogadores[MAX_JOGADORES];

    char tabuleiro[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};

    int linha, coluna;
    int rodadas = 0;

    for (int i = 0; i < MAX_JOGADORES; i++) {
        obterDadosJogador(&jogadores[i]);
    }

    while (rodadas < NUM_RODADAS) {
        for (int i = 0; i < MAX_JOGADORES; i++) {
            imprimirTabuleiro(tabuleiro);

            printf("\n%s, sua vez.\n", jogadores[i].nome);
            printf("Insira a linha (0-2) e coluna (0-2) separadas por espaço: ");

            scanf("%d %d", &linha, &coluna);

            if (tabuleiro[linha][coluna] == ' ') {
                realizarJogada(tabuleiro, linha, coluna, jogadores[i].letra);
                char vencedor = verificarVencedor(tabuleiro);

                if (vencedor != ' ') {
                    imprimirTabuleiro(tabuleiro);

                    printf("\n%s venceu esta rodada!\n", jogadores[i].nome);

                    jogadores[i].vitorias++;

                    rodadas++;

                    salvarEmArquivo(jogadores, MAX_JOGADORES, rodadas);

                    if (jogadores[i].vitorias == 3) {
                        printf("\n%s é o campeão!\n", jogadores[i].nome);

                        atualizarRanking(jogadores, MAX_JOGADORES);

                        return 0;
                    }

                    for (int a = 0; a < 3; a++) {
                        for (int b = 0; b < 3; b++) {
                            tabuleiro[a][b] = ' ';
                        }
                    }
                    break;
                }
            } else {
                printf("Posição ocupada. Tente novamente.\n");
                i--;
            }
        }
    }

    return 0;
}