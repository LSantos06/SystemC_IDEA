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

#define TESTES 0
// 1 cifragem e decifragem
// 2 operacoes

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
uint16_t mul_IDEA(uint32_t, uint32_t);

/* Operacoes inversas do IDEA */
// Inverso da multiplicacao 2^(16+1)
int16_t add_inv_IDEA(int16_t);

// Inverso da adicao mod 2^(16)
int16_t mul_inv_IDEA(int32_t, int32_t);

#endif
