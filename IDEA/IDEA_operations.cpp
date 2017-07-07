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

/*
 * Inverso Aditivo
 *
 * Entradas:
 * 	- int16_t number : numero de 16 bits que deseja-se calcular o inverso aditivo
 * Saidas:
 *  - inverso aditivo de number
 */
int16_t add_inv_IDEA(int16_t number){
    return 0-number;
}

/*
 * Inverso Multiplicativo Modular
 *
 * Entradas:
 * 	- int32_t a : numero de 32 bits o qual deseja-se calcular o inverso
 * 	              multiplicativo modular
 *  - int32_t m : numero de 32 bits que representa o modulo
 * Saidas:
 *  - Retorna o inverso multiplicativo modular do numero a (mod m), isto e,
 *    encontra o numero x1, tal que, "a * x1 = 1 (mod m)" atraves do
 *    algoritmo de euclides extendido, assumindo que a e m sao
 *    relativamente primos, isto e, gcd(a, m) = 1.
 */
int16_t mul_inv_IDEA(int32_t a, int32_t m) {
    a = a&0xffff;
    int32_t m0 = m, t, q;
    int32_t x0 = 0, x1 = 1;

    if (m == 1){
      return 0;
    }

    while (a > 1)
    {
        q = a / m;
        t = m;

        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0){
       x1 += m0;
    }
    return x1;
}
