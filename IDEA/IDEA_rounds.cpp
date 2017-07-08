/*
 *  IDEA
 *  Modelagem de Sistemas em Silicio
 *  1/2017
 *
 *  Lucas Avelino 13/0013072
 *  Lucas Santos 14/0151010
 */

#include "IDEA_rounds.h"

/*
 * Parte 1 de um round ou half-round
 *
 * Entradas:
 * 	- 4 primeiras sub-chaves de 16 bits
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 4 palavras de 16 bits operadas
 */
void parte_1(uint16_t *x, uint16_t k_a, uint16_t k_b, uint16_t k_c, uint16_t k_d){
	// Variavel auxiliar para guardar o valor de x[1]
	uint16_t aux1 = x[1];

	// Xa' = Xa mul Ka
	x[3] = mul_IDEA(x[3], k_a);
	// Xc' = Xb add Kb
	x[1] = add_IDEA(x[2], k_b);
	// Xb' = Xc add Kc
	x[2] = add_IDEA(aux1, k_c);
	// Xd' = Xd mul Kd
	x[0] = mul_IDEA(x[0], k_d);
}

/*
 * Parte 2 de um round
 *
 * Entradas:
 * 	- 2 ultimas sub-chaves de 16 bits
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 4 palavras de 16 bits finais
 */
void parte_2(uint16_t *x, uint16_t k_e, uint16_t k_f){
	uint16_t y[2],z[2];

	// Y1 = Xa xor Xb
	y[0] = xor_IDEA(x[3], x[2]);
	// Z1 = Xc xor Xd
	z[0] = xor_IDEA(x[1], x[0]);

	// Y2 = [(Ke mul Y1) add Z1] mul Kf
	y[1] = mul_IDEA(k_e, y[0]);
	y[1] = add_IDEA(y[1], z[0]);
	y[1] = mul_IDEA(y[1], k_f);

	// Z2 = (Ke mul Y1) add Y2
	z[1] = mul_IDEA(k_e, y[0]);
	z[1] = add_IDEA(z[1], y[1]);

	// Xa = Xa xor Y2
	x[3] = xor_IDEA(x[3], y[1]);
	// Xb = Xb xor Y2
	x[2] = xor_IDEA(x[2], y[1]);
	// Xc = Xc xor Z2
	x[1] = xor_IDEA(x[1], z[1]);
	// Xd = Xd xor Z2
	x[0] = xor_IDEA(x[0], z[1]);
}

/*
 * Um round de operacoes
 *
 * Entradas:
 * 	- 4 palavras de 16 bits
 * 	- 6 sub-chaves
 * Saidas:
 *  - 4 palavras de 16 bits operadas
 */
void round(uint16_t *x, uint16_t k_a, uint16_t k_b, uint16_t k_c, uint16_t k_d, uint16_t k_e, uint16_t k_f){
	parte_1(x, k_a, k_b, k_c, k_d);
	parte_2(x, k_e, k_f);
}

/*
 * Ultimo round de operacoes
 *
 * Entradas:
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 4 palavras de 16 bits operadas
 */
// Round final que gera a saida
void half_round(uint16_t *x, uint16_t k_a, uint16_t k_b, uint16_t k_c, uint16_t k_d){
	parte_1(x, k_a, k_c, k_b, k_d);
}
