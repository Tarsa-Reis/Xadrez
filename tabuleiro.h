//
// Created by autistictiger on 27/08/2025.
//

#ifndef XADREZ_TABULEIRO_H
#define XADREZ_TABULEIRO_H

typedef enum { VAZIO=0, PEAO, CAVALO, BISPO, TORRE, DAMA, REI } Peca;
typedef enum { SEM_COR=0, BRANCO, PRETO } Cor;

typedef struct Espaco{
     Peca peca;
     Cor cor;
}Espaco;

#endif //XADREZ_TABULEIRO_H