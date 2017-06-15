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
uint16_t xor_IDEA(uint16_t a, uint16_t b){
	return (a ^ b);
}

/*
 * Adicao mod 2^(16), sem overflow
 *
 * Entradas:
 * 	- 16 bits
 * 	- 16 bits
 * Saidas:
 *  - soma as duas entradas e tira o modulo (16 bits)
 */
uint16_t add_IDEA(uint16_t a, uint16_t b){
#if	TESTES == 2
	printf("add_IDEA (a + b) = 0x%x\n", (a + b));
#endif
	return ((a + b) % MODULO_ADD);
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
uint16_t mul_IDEA(uint32_t a, uint32_t b){
	if(a == 0) a = MODULO_ADD;
	if(b == 0) b = MODULO_ADD;
#if TESTES == 2
	printf("mul_IDEA a = 0x%x\n", a);
	printf("mul_IDEA b = 0x%x\n", b);
	printf("mul_IDEA (a * b) = 0x%x\n", (a * b));
#endif
	return (uint16_t)((a * b) % MODULO_MUL);
}
