#include "tabuleiro.h"

#include <stdlib.h>

void iniciaTabuleiro(Espaco tabuleiro[8][8]) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tabuleiro[i][j].cor = VAZIO;
            tabuleiro[i][j].peca = VAZIO;
        }
    }
}

void iniciaPosicoes(Espaco tabuleiro[8][8]) {
    for (int i = 0; i < 8; i++) {
        tabuleiro[6][i].peca = PEAO;
        tabuleiro[1][i].peca = PEAO;
        tabuleiro[6][i].cor = PRETO;
        tabuleiro[1][i].cor = BRANCO;
    }
}

int *calculaMovimentacao(Espaco tabuleiro[8][8], Espaco peca, int linha, int coluna) {
    int *posicoes = NULL;
    int qtd = 0;
    if (peca.peca == PEAO) {
        int dir = (peca.cor == BRANCO) ? -1 : 1; // direção do movimento

        // Movimento simples para frente
        if (linha + dir >= 0 && linha + dir < 8 && tabuleiro[linha+dir][coluna].peca == VAZIO) {
            posicoes = realloc(posicoes, (qtd+1)*2*sizeof(int));
            posicoes[2*qtd]   = linha + dir;
            posicoes[2*qtd+1] = coluna;
            qtd++;
        }

        // Movimento de captura (diagonais)
        for (int dj = -1; dj <= 1; dj += 2) {
            int ni = linha + dir;
            int nj = coluna + dj;
            if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) {
                if (tabuleiro[ni][nj].peca != VAZIO && tabuleiro[ni][nj].cor != peca.cor) {
                    posicoes = realloc(posicoes, (qtd+1)*2*sizeof(int));
                    posicoes[2*qtd]   = ni;
                    posicoes[2*qtd+1] = nj;
                    qtd++;
                }
            }
        }
    }else if (peca.peca == TORRE) {
        int posicao[4];
        int i;
        if (linha>0) {
            i=linha-1;
            while (i>=0&&(tabuleiro[i][coluna].peca == VAZIO || tabuleiro[i][coluna].cor != peca.cor)) {
                posicao[0] = i;
                i--;
            }
        }
    }




    return posicoes;
}

void movimentaPeca(Espaco tabuleiro[8][8]) {

}


