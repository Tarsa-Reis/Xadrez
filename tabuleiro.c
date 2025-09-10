#include "tabuleiro.h"

#include <stdlib.h>

void iniciaTabuleiro(Espaco tabuleiro[8][8]) {//inicia o tabuleiro vazio
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            tabuleiro[i][j].cor = VAZIO;
            tabuleiro[i][j].peca = VAZIO;
        }
    }
}

void iniciaPosicoes(Espaco tabuleiro[8][8]) {//inicia as peças no tabuleiro
    for (int i = 0; i < 8; i++) {

        // Posiciona os peoes
        tabuleiro[6][i].peca = PEAO;
        tabuleiro[1][i].peca = PEAO;
        tabuleiro[6][i].cor = PRETO;
        tabuleiro[1][i].cor = BRANCO;

        // Linha das peças brancas (linha 0)
        tabuleiro[0][0].peca = TORRE;  tabuleiro[0][0].cor = BRANCO;
        tabuleiro[0][7].peca = TORRE;  tabuleiro[0][7].cor = BRANCO;

        tabuleiro[0][1].peca = CAVALO; tabuleiro[0][1].cor = BRANCO;
        tabuleiro[0][6].peca = CAVALO; tabuleiro[0][6].cor = BRANCO;

        tabuleiro[0][2].peca = BISPO;  tabuleiro[0][2].cor = BRANCO;
        tabuleiro[0][5].peca = BISPO;  tabuleiro[0][5].cor = BRANCO;

        tabuleiro[0][3].peca = DAMA;   tabuleiro[0][3].cor = BRANCO;
        tabuleiro[0][4].peca = REI;    tabuleiro[0][4].cor = BRANCO;

        // Linha das peças pretas (linha 7)
        tabuleiro[7][0].peca = TORRE;  tabuleiro[7][0].cor = PRETO;
        tabuleiro[7][7].peca = TORRE;  tabuleiro[7][7].cor = PRETO;

        tabuleiro[7][1].peca = CAVALO; tabuleiro[7][1].cor = PRETO;
        tabuleiro[7][6].peca = CAVALO; tabuleiro[7][6].cor = PRETO;

        tabuleiro[7][2].peca = BISPO;  tabuleiro[7][2].cor = PRETO;
        tabuleiro[7][5].peca = BISPO;  tabuleiro[7][5].cor = PRETO;

        tabuleiro[7][3].peca = DAMA;   tabuleiro[7][3].cor = PRETO;
        tabuleiro[7][4].peca = REI;    tabuleiro[7][4].cor = PRETO;

        //Preenche o resto com vazio
        for (int i = 2; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                tabuleiro[i][j].peca = VAZIO;
                tabuleiro[i][j].cor = SEM_COR;
            }
        }

    }
}

int *calculaMovimentacao(Espaco tabuleiro[8][8], Espaco peca, int linha, int coluna) {
    if (peca.peca == PEAO) {
        int *posicoes = NULL;
        int qtd = 0;
        int dir = (peca.cor == BRANCO) ? -1 : 1; // direção do movimento

        // Movimento para frente
        if (linha + dir >= 0 && linha + dir < 8 && tabuleiro[linha+dir][coluna].peca == VAZIO) {
            posicoes = realloc(posicoes, (qtd+1)*2*sizeof(int));
            posicoes[2*qtd]   = linha + dir;
            posicoes[2*qtd+1] = coluna;
            qtd++;
        }

        // Movimento de captura
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
        return posicoes;
    }else if (peca.peca == TORRE) {
        int posicao[4]={linha,linha,coluna,coluna};//esquerda,direita,baixo,cima
        int i;
        if (linha>0) {
            i=linha-1;
            while (i>=0) {
                if(tabuleiro[i][coluna].peca != VAZIO) {
                    if(tabuleiro[i][coluna].cor == peca.cor) {
                        posicao[0] = i+1;
                    }else {
                        posicao[0] = i;
                    }
                    i=-1;
                }else {
                    posicao[0] = i;
                    i--;
                }
            }
        }
        if (linha<7) {
            i=linha+1;
            while (i<=7) {
                if(tabuleiro[i][coluna].peca != VAZIO) {
                    if(tabuleiro[i][coluna].cor == peca.cor) {
                        posicao[1] = i-1;
                    }else {
                        posicao[1] = i;
                    }
                    i=8;
                }else {
                    posicao[1] = i;
                    i++;
                }
            }
        }
        if (coluna>0) {
            i=coluna-1;
            while (i>=0) {
                if(tabuleiro[linha][i].peca != VAZIO) {
                    if(tabuleiro[linha][i].cor == peca.cor) {
                        posicao[2] = i+1;
                    }else {
                        posicao[2] = i;
                    }
                    i=-1;
                }else {
                    posicao[2] = i;
                    i--;
                }
            }
        }
        if (coluna<7) {
            i=coluna+1;
            while (i<=7) {
                if(tabuleiro[linha][i].peca != VAZIO) {
                    if(tabuleiro[linha][i].cor == peca.cor) {
                        posicao[3] = i-1;
                    }else {
                        posicao[3] = i;
                    }
                    i=8;
                }else {
                    posicao[3] = i;
                    i++;
                }
            }
        }
        return posicao;
    }else if (peca.peca == BISPO) {
        int posicao[4]={linha,linha,coluna,coluna};//esquerda,direita,baixo,cima
        int i;
        if (linha>0) {
            i=linha-1;

            while (i>=0) {
                if(tabuleiro[i][coluna].peca != VAZIO) {
                    if(tabuleiro[i][coluna].cor == peca.cor) {
                        posicao[0] = i+1;
                    }else {
                        posicao[0] = i;
                    }
                    i=-1;
                }else {
                    posicao[0] = i;
                    i--;
                }
            }
        }
        if (linha<7) {
            i=linha+1;
            while (i<=7) {
                if(tabuleiro[i][coluna].peca != VAZIO) {
                    if(tabuleiro[i][coluna].cor == peca.cor) {
                        posicao[1] = i-1;
                    }else {
                        posicao[1] = i;
                    }
                    i=8;
                }else {
                    posicao[1] = i;
                    i++;
                }
            }
        }
        if (coluna>0) {
            i=coluna-1;
            while (i>=0) {
                if(tabuleiro[linha][i].peca != VAZIO) {
                    if(tabuleiro[linha][i].cor == peca.cor) {
                        posicao[2] = i+1;
                    }else {
                        posicao[2] = i;
                    }
                    i=-1;
                }else {
                    posicao[2] = i;
                    i--;
                }
            }
        }
        if (coluna<7) {
            i=coluna+1;
            while (i<=7) {
                if(tabuleiro[linha][i].peca != VAZIO) {
                    if(tabuleiro[linha][i].cor == peca.cor) {
                        posicao[3] = i-1;
                    }else {
                        posicao[3] = i;
                    }
                    i=8;
                }else {
                    posicao[3] = i;
                    i++;
                }
            }
        }
    }
}

void movimentaPeca(Espaco tabuleiro[8][8]) {

}


