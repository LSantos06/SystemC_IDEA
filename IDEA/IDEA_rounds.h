/*
 *  IDEA
 *  Modelagem de Sistemas em Silicio
 *  1/2017
 *
 *  Lucas Avelino 13/0013072
 *  Lucas Santos 14/0151010
 */

#ifndef IDEA_ROUND_H
#define IDEA_ROUND_H

#include "IDEA_operations.h"

/* Conjuntos de operações de um round do IDEA */
// Recebe as 4 primeiras sub-chaves do round atual
void parte_1(uint16_t*, uint16_t, uint16_t, uint16_t, uint16_t);

// Recebe a 5 e 6 sub-chave do round atual
void parte_2(uint16_t*, uint16_t, uint16_t);


/* Rounds */
// Round de operacoes repetido 8 vezes
void round(uint16_t*);

// Round final que gera a saida
void half_round(uint16_t*);

#endif
