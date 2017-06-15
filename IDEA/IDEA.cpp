/*
 *  IDEA
 *  Modelagem de Sistemas em Silicio
 *  1/2017
 *
 *  Lucas Avelino 13/0013072
 *  Lucas Santos 14/0151010
 */

#include "IDEA.h"

/*
 * Destrutor
 */
idea::~idea(){
  if (REGS) delete [] REGS;
  REGS = (uint32_t *)0;

  if (SUBKEYS) delete [] SUBKEYS;
  SUBKEYS = (uint16_t *)0;
}

/*
 * Pega o comando e decide a acao
 *
 * Entradas:
 * 	- registrador CMD (32 bits)
 * Saidas:
 *  - acao de acordo com o valor do CMD
 */
void idea::getCMD(){

}

/*
 * Geracao das 52 subchaves para descifrar
 *
 * Entradas:
 * 	- registradores KG (128 bits)
 * Saidas:
 *  - 52 sub-chaves (16 bits cada)
 */
void idea::subchaves_descifrar(){

}

/*
 * Geracao das 52 subchaves para cifrar
 *
 * Entradas:
 * 	- registradores KG (128 bits)
 * Saidas:
 *  - 52 sub-chaves (16 bits cada)
 */
void idea::subchaves_cifrar(){

}

/*
 * Descifrar ou Cifrar uma entrada (64 bits)
 *
 * Entradas:
 * 	- 52 sub-chaves (16 bits cada) para descifrar ou cifrar
 * 	- registradores W (64 bits) com texto legivel ou ilegivel
 * Saidas:
 *  - registradores W (64 bits) com texto ilegivel ou legivel
 */
void idea::descifrar_cifrar(){
	uint16_t *WORDS;
	// Inicializando as WORDS
    WORDS = new uint16_t[N_WORDS];
    for (unsigned int i = 0; i < N_WORDS; ++i)
    	WORDS[i] = 0;

#if TESTES == 1||2
	// Valores de teste REGS[1] e REGS[2]
	printf("Teste SEPARACAO\n");
    REGS[1] = 0x12345678;
	printf("W1W0: 0x%x\n", REGS[1]);
	REGS[2] = 0x9ABCDEF0;
	printf("W3W2: 0x%x\n", REGS[2]);
#endif

	/* Dividindo as palavras para cripografia */
	// WORDS[0] = W0 = 2 bytes MENOS significativos de REGS[1]
	WORDS[0] = REGS[1] & 0xFFFF;

	// WORDS[1] = W1 = 2 bytes MAIS significativos de REGS[1]
	WORDS[1] = REGS[1] >> 16;

	// WORDS[2] = W2 = 2 bytes MENOS significativos de REGS[2]
	WORDS[2] = REGS[2] & 0xFFFF;

	// WORDS[3] = W3 = 2 bytes MAIS significativos de REGS[2]
	WORDS[3] = REGS[2] >> 16;

#if TESTES == 1
	// Resultado separacao
	printf("W0: 0x%x\n", WORDS[0]);
	printf("W1: 0x%x\n", WORDS[1]);
	printf("W2: 0x%x\n", WORDS[2]);
	printf("W3: 0x%x\n\n", WORDS[3]);
#endif

#if TESTES == 2
	// Testes para as operacoes
	printf("Teste XOR\n");
	printf("W0 xor W1 = 0x%x\n", xor_IDEA(WORDS[0],WORDS[1]));
	printf("W2 xor W3 = 0x%x\n\n", xor_IDEA(WORDS[2],WORDS[3]));
	printf("Teste ADD\n");
	printf("W0 add W1 = 0x%x\n", add_IDEA(WORDS[0],WORDS[1]));
	printf("W2 add W3 = 0x%x\n", add_IDEA(WORDS[2],WORDS[3]));
	printf("-1 add -1 = 0x%x\n\n", add_IDEA(-1,-1));
	printf("Teste MUL\n");
	printf("W0 mul W1 = 0x%x\n", mul_IDEA((uint32_t)WORDS[0],(uint32_t)WORDS[1]));
	printf("W2 mul W3 = 0x%x\n", mul_IDEA((uint32_t)WORDS[2],(uint32_t)WORDS[3]));
	printf("0 mul W1 = 0x%x\n", mul_IDEA(0,(uint32_t)WORDS[1]));
	printf("W2 mul 0 = 0x%x\n", mul_IDEA((uint32_t)WORDS[2],0));
	printf("MODULO_ADD mul 1 = 0x%x\n\n", mul_IDEA(MODULO_ADD,1));
#endif

	// Loop fazendo os rounds
	int i;
	for(i = 0; i < (N_ROUNDS*6); i+=6){
		round(WORDS, SUBKEYS[i], SUBKEYS[i+1], SUBKEYS[i+2], SUBKEYS[i+3], SUBKEYS[i+4], SUBKEYS[i+5]);
	}
	// Final round
	half_round(WORDS,SUBKEYS[i], SUBKEYS[i+1], SUBKEYS[i+2], SUBKEYS[i+3]);

	// Juntando o resultado e armazenando nos registradores
#if TESTES == 1||2
	// Resultado IDEA
	printf("Mensagem criptografada\n");
	printf("W0: 0x%x\n", WORDS[0]);
	printf("W1: 0x%x\n", WORDS[1]);
	printf("W2: 0x%x\n", WORDS[2]);
	printf("W3: 0x%x\n\n", WORDS[3]);
#endif

}

/*
 * Status atual do modulo de acordo com a enum
 *
 * Entradas:
 * Saidas:
 *  - status atual
 */
void idea::getStatus(){

}

