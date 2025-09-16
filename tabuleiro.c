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
        tabuleiro[6][i].movido = 0;
        tabuleiro[1][i].movido = 0;

        //
        tabuleiro[0][i].movido = 0;
        tabuleiro[7][i].movido = 0;
    }

    // Linha das peças brancas (linha 0)
    tabuleiro[0][0].peca = TORRE;  tabuleiro[0][0].cor = BRANCO;
    tabuleiro[0][7].peca = TORRE;  tabuleiro[0][7].cor = BRANCO;

    tabuleiro[0][1].peca = CAVALO; tabuleiro[0][1].cor = BRANCO;
    tabuleiro[0][6].peca = CAVALO; tabuleiro[0][6].cor = BRANCO;

    tabuleiro[0][2].peca = BISPO;  tabuleiro[0][2].cor = BRANCO;
    tabuleiro[0][5].peca = BISPO;  tabuleiro[0][5].cor = BRANCO;

    tabuleiro[0][3].peca = RAINHA;   tabuleiro[0][3].cor = BRANCO;
    tabuleiro[0][4].peca = REI;    tabuleiro[0][4].cor = BRANCO;

    // Linha das peças pretas (linha 7)
    tabuleiro[7][0].peca = TORRE;  tabuleiro[7][0].cor = PRETO;
    tabuleiro[7][7].peca = TORRE;  tabuleiro[7][7].cor = PRETO;

    tabuleiro[7][1].peca = CAVALO; tabuleiro[7][1].cor = PRETO;
    tabuleiro[7][6].peca = CAVALO; tabuleiro[7][6].cor = PRETO;

    tabuleiro[7][2].peca = BISPO;  tabuleiro[7][2].cor = PRETO;
    tabuleiro[7][5].peca = BISPO;  tabuleiro[7][5].cor = PRETO;

    tabuleiro[7][3].peca = RAINHA;   tabuleiro[7][3].cor = PRETO;
    tabuleiro[7][4].peca = REI;    tabuleiro[7][4].cor = PRETO;

    //Preenche o resto com vazio
    for (int i = 2; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            tabuleiro[i][j].peca = VAZIO;
            tabuleiro[i][j].cor = SEM_COR;
            tabuleiro[i][j].movido = 1;
        }
    }


}


void calculaMovimentoEmLinha(Espaco tabuleiro[8][8], Espaco peca, int linha, int coluna, int vertical, int horizontal, int indice, Coordenada ***coordenada) {

    int i = linha + vertical;
    int j = coluna + horizontal;

    if (i >= 0 && i < 8 && j >= 0 && j < 8) {
        if (*coordenada == NULL) {
            *coordenada = malloc(sizeof(Coordenada*) * 4);
            if (*coordenada == NULL) return;
            for (int n = 0; n < 4; n++) {
                (*coordenada)[n] = NULL;
            }
        }
        (*coordenada)[indice] = malloc(sizeof(Coordenada));
    }

    while (i >= 0 && i < 8 && j >= 0 && j < 8) {
        if (tabuleiro[i][j].peca != VAZIO) {
            if (tabuleiro[i][j].cor != peca.cor) {
                (*coordenada)[indice]->linha = i;
                (*coordenada)[indice]->coluna = j;
                i = 10;
            }else {
                (*coordenada)[indice]->linha = i-vertical;
                (*coordenada)[indice]->coluna = j-horizontal;
                i=10;
            }
        }
        i = i + vertical;
        j = j + horizontal;
    }
}



void calculaMovimentoDiagonal(Espaco tabuleiro[8][8], Espaco peca, int linha, int coluna, int vertical, int horizontal, int indice, Coordenada ***coordenada) {
    int auxv;
    int auxh;


    if (vertical>0) {
        auxv = 8;
    }else {
        auxv = -1;
    }

    if (horizontal>0) {
        auxh = 8;
    }else {
        auxh = -1;
    }
    int i = linha + vertical;
    int j = coluna + horizontal;

    if ((i!=auxv)&&(j!=auxh)) {
        if (*coordenada==NULL) {
            *coordenada = malloc(sizeof(Coordenada*)*4);
            for (int n =0;n<4;n++) {
                (*coordenada)[n] = NULL;
            }
        }
        (*coordenada[indice]) = malloc(sizeof(Coordenada));
    }

    while (i!=auxv&&j!=auxh) {
        if (tabuleiro[i][j].peca!=VAZIO) {
            if (tabuleiro[i][j].cor==peca.cor) {
                (*coordenada[indice])->linha = i-vertical;
                (*coordenada[indice])->coluna = j-horizontal;
                i=auxv;
            }else {
                (*coordenada[indice])->linha = i;
                (*coordenada[indice])->coluna = j;
                i=auxv;
            }
        }
        i=i+vertical;
        j=j+horizontal;
    }

}

void calculaCavalo(Espaco tabuleiro[8][8], Espaco peca, int linha, int coluna, int vertical, int horizontal, int indice, Coordenada ***coordenada) {
    int i = linha + vertical;
    int j = coluna + horizontal;
    if (i<=7&&j<=7&&i>=0&&j>=0&&tabuleiro[i][j].cor!=peca.cor){
        if (coordenada==NULL) {
            *coordenada = malloc(sizeof(Coordenada*)*8);
            for (int n =0;n<8;n++) {
                (*coordenada)[n] = NULL;
            }
        }
        (*coordenada[indice]) = malloc(sizeof(Coordenada));
        (*coordenada[indice])->linha = i;
        (*coordenada[indice])->coluna = j;
    }


}

Coordenada **calculaMovimentacao(Espaco tabuleiro[8][8], Espaco peca, int linha, int coluna) {
    if (peca.peca == PEAO) {
        Coordenada **coordenada = NULL;
        int qtd = 0;
        int dir = (peca.cor == BRANCO) ? -1 : 1; // direção do movimento

        // Movimento para frente
        if (linha + dir >= 0 && linha + dir < 8 && tabuleiro[linha+dir][coluna].peca == VAZIO) {
            coordenada = realloc(coordenada, sizeof(Coordenada*));
            coordenada[qtd] = malloc(sizeof(Coordenada));
            coordenada[qtd]->linha   = linha + dir;
            coordenada[qtd]->coluna = coluna;
            qtd++;
        }

        // Movimento de captura
        for (int dj = -1; dj <= 1; dj += 2) {
            int ni = linha + dir;
            int nj = coluna + dj;
            if (ni >= 0 && ni < 8 && nj >= 0 && nj < 8) {
                if (tabuleiro[ni][nj].peca != VAZIO && tabuleiro[ni][nj].cor != peca.cor) {
                    coordenada = realloc(coordenada, qtd*sizeof(*coordenada));
                    coordenada[qtd] = malloc(sizeof(Coordenada));
                    coordenada[qtd]->linha   = ni;
                    coordenada[qtd]->coluna = nj;
                    qtd++;
                }
            }
        }
        return coordenada;
    }else if (peca.peca == TORRE) {
        Coordenada **coordenada = NULL;
        int indice = 0;
        calculaMovimentoEmLinha(tabuleiro,peca,linha,coluna,1,1,indice,&coordenada);
        indice++;
        calculaMovimentoEmLinha(tabuleiro,peca,linha,coluna,1,1,indice,&coordenada);
        indice++;
        calculaMovimentoEmLinha(tabuleiro,peca,linha,coluna,1,1,indice,&coordenada);
        indice++;
        calculaMovimentoEmLinha(tabuleiro,peca,linha,coluna,1,1,indice,&coordenada);

        return coordenada;
    }else if (peca.peca == BISPO) {

        Coordenada **coordenada=NULL;
        int indice=0;

        calculaMovimentoDiagonal(tabuleiro,peca,linha,coluna,-1,-1,indice,&coordenada);
        indice = indice+1;
        calculaMovimentoDiagonal(tabuleiro,peca,linha,coluna,-1,1,indice,&coordenada);
        indice = indice+1;
        calculaMovimentoDiagonal(tabuleiro,peca,linha,coluna,1,-1,indice,&coordenada);
        indice = indice+1;
        calculaMovimentoDiagonal(tabuleiro,peca,linha,coluna,1,1,indice,&coordenada);

        return coordenada;
    }else if (peca.peca == CAVALO) {
        Coordenada **coordenada=NULL;

        int indice=0;

        calculaCavalo(tabuleiro,peca,linha,coluna,2,1,indice,&coordenada);
        indice = indice+1;
        calculaCavalo(tabuleiro,peca,linha,coluna,-2,-1,indice,&coordenada);
        indice = indice+1;
        calculaCavalo(tabuleiro,peca,linha,coluna,2,-1,indice,&coordenada);
        indice = indice+1;
        calculaCavalo(tabuleiro,peca,linha,coluna,-2,1,indice,&coordenada);
        indice = indice+1;
        calculaCavalo(tabuleiro,peca,linha,coluna,1,2,indice,&coordenada);
        indice = indice+1;
        calculaCavalo(tabuleiro,peca,linha,coluna,-1,-2,indice,&coordenada);
        indice = indice+1;
        calculaCavalo(tabuleiro,peca,linha,coluna,1,-2,indice,&coordenada);
        indice = indice+1;
        calculaCavalo(tabuleiro,peca,linha,coluna,-1,2,indice,&coordenada);
        return coordenada;

    }else if (peca.peca == REI) {
        Coordenada **coordenada=NULL;
        int indice=0;
    }
}

void movimentaPeca(Espaco tabuleiro[8][8]) {

}


