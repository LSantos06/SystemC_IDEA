/*
 *  IDEA
 *  Modelagem de Sistemas em Silicio
 *  1/2017
 *
 *  Lucas Avelino 13/0013072
 *  Lucas Santos 14/0151010
 */

#ifndef IDEA_OPS_H
#define IDEA_OPS_H

#include <systemc.h>

#define TESTES 1

const int MODULO_ADD = 65536;
const int MODULO_MUL = 65537;

/* Tres operacoes basicas do IDEA */
// Ou-exclusivo bit a bit, sobre 16 bits
uint16_t xor_IDEA(uint16_t, uint16_t);

// Adicao mod 2^(16)
uint16_t add_IDEA(uint16_t, uint16_t);

// Multiplicacao mod 2^(16+1), onde:
//  - Se alguma entrada for 0 => 2^(16)
//  - Se a saida for 2^(16) => 0
uint16_t mul_IDEA(uint16_t, uint16_t);


/* Linhas de operações do IDEA */
// Recebe as 4 primeiras sub-chaves do round atual
void linha_1(uint16_t, uint16_t, uint16_t, uint16_t);

// Não recebe sub-chaves
void linha_2_3();

// Recebe a 5 e 6 sub-chave do round atual
void linha_4_5(uint16_t, uint16_t);

// Não recebe sub-chaves
void linha_6_7();

#endif
