/*
 *  IDEA
 *  Modelagem de Sistemas em Silicio
 *  1/2017
 *
 *  Lucas Avelino 13/0013072
 *  Lucas Santos 14/0151010
 */

#include "IDEA_operations.h"

/*
 * Xor
 *
 * Entradas:
 * 	- 16 bits
 * 	- 16 bits
 * Saidas:
 *  - xor entre as duas entradas (16 bits)
 */
uint16_t xorIDEA(uint16_t a, uint16_t b){
	return (a ^ b);
}

/*
 * Adicao mod 2^(16)
 *
 * Entradas:
 * 	- 16 bits
 * 	- 16 bits
 * Saidas:
 *  - soma as duas entradas e tira o modulo (16 bits)
 */
uint16_t addIDEA(uint16_t a, uint16_t b){
	return (uint16_t)((a + b) % MODULO_ADD);
}

/*
 * Multiplicacao mod 2^(16+1)
 *
 * Entradas:
 * 	- 16 bits
 * 	- 16 bits
 * Saidas:
 *  - multiplica as duas entradas e tira o modulo (16 bits)
 */
uint16_t mulIDEA(uint16_t a, uint16_t b){
	if(a == 0) a = (uint16_t)MODULO_ADD;
	if(b == 0) b = (uint16_t)MODULO_ADD;
	return (uint16_t)((a * b) % MODULO_MUL);
}

/*
 * Linha 1 de um round ou half-round
 *
 * Entradas:
 * 	- 4 primeiras sub-chaves de 16 bits
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 4 palavras de 16 bits operadas
 */
void linha1(uint16_t, uint16_t, uint16_t, uint16_t){

}

/*
 * Linhas 2 e 3 de um round
 *
 * Entradas:
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 2 palavras de 16 bits operadas
 */
void linha_2_3(){

}

/*
 * Linhas 4 e 5 de um round
 *
 * Entradas:
 * 	- 2 ultimas sub-chaves de 16 bits
 * 	- 2 palavras de 16 bits
 * Saidas:
 *  - 2 palavras de 16 bits operadas
 */
void linha_4_5(uint16_t, uint16_t){

}

/*
 * Linhas 6 e 7 de um round
 *
 * Entradas:
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 4 palavras de 16 bits operadas
 */
void linha_6_7(){

}
