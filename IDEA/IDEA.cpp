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
 * Construtor
 */
idea::idea(sc_module_name nome_)
    : sc_module(nome_){

    // Inicializando os REGS
    REGS = new uint32_t[N_REGS];
    for (unsigned int i = 0; i < N_REGS; ++i)
        REGS[i] = 0;
    // Inicializando as SUBKEYS
    SUBKEYS = new uint16_t[N_SUBKEYS];
    for (unsigned int i = 0; i < N_SUBKEYS; ++i)
        SUBKEYS[i] = 0;

    SC_THREAD(execute);

}

/*
 * Destrutor
 */
idea::~idea(){
  if (REGS) delete [] REGS;
  REGS = (uint32_t *)0;

  //if (SUBKEYS) delete [] SUBKEYS;
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
	// The decryption key schedule is:
	// The first four subkeys for decryption are:
	//   KD(1) = 1/K(49)
	//   KD(2) = -K(50)
	//   KD(3) = -K(51)
	//   KD(4) = 1/K(52)
	// and they do not quite follow the same pattern as the remaining subkeys which follow.
	// The following is repeated eight times, adding 6 to every decryption key's index and subtracting 6 from every encryption key's index:
	//   KD(5) = K(47)
	//   KD(6) = K(48)
	// ...
	//   KD(7) = 1/K(43)
	//   KD(8) = -K(45)
	//   KD(9) = -K(44)
	//   KD(10) = 1/K(46)

    int i = N_WORDS;
    uint16_t *decipher_subkeys = new uint16_t[N_SUBKEYS];
    // KD(1) = 1/K(49)
    decipher_subkeys[0] = mul_inv_IDEA(SUBKEYS[48],MODULO_MUL);
    // KD(2) = -K(50)
    decipher_subkeys[1] = add_inv_IDEA(SUBKEYS[49]);
    // KD(3) = -K(51)
    decipher_subkeys[2] = add_inv_IDEA(SUBKEYS[50]);
    // KD(4) = 1/K(52)
    decipher_subkeys[3] = mul_inv_IDEA(SUBKEYS[51],MODULO_MUL);
#if TESTES == 1
	printf("KD%d: 0x%x\n", i-4, decipher_subkeys[i-4]);
	printf("KD%d: 0x%x\n", i-3, decipher_subkeys[i-3]);
	printf("KD%d: 0x%x\n", i-2, decipher_subkeys[i-2]);
	printf("KD%d: 0x%x\n", i-1, decipher_subkeys[i-1]);
#endif
    // ...
    while (i < N_SUBKEYS) {
    	// KD(5) = K(47)
    	decipher_subkeys[i] = SUBKEYS[50-i];
    	// KD(6) = K(48)
    	decipher_subkeys[i+1] = SUBKEYS[51-i];
    	// KD(7) = 1/K(43)
    	decipher_subkeys[i+2] = mul_inv_IDEA(SUBKEYS[46-i],MODULO_MUL);
    	// KD(8) = -K(45)
    	decipher_subkeys[i+3] = add_inv_IDEA(SUBKEYS[48-i]);
    	// KD(9) = -K(44)
    	decipher_subkeys[i+4] = add_inv_IDEA(SUBKEYS[47-i]);
    	// KD(10) = 1/K(46)
    	decipher_subkeys[i+5] = mul_inv_IDEA(SUBKEYS[49-i],MODULO_MUL);
    	// Adding 6 to every decryption key's index and subtracting 6 from every encryption key's index
#if TESTES == 1
    	printf("KD%d: 0x%x\n", i, decipher_subkeys[i]);
		printf("KD%d: 0x%x\n", i+1, decipher_subkeys[i+1]);
		printf("KD%d: 0x%x\n", i+2, decipher_subkeys[i+2]);
		printf("KD%d: 0x%x\n", i+3, decipher_subkeys[i+3]);
		printf("KD%d: 0x%x\n", i+4, decipher_subkeys[i+4]);
		printf("KD%d: 0x%x\n", i+5, decipher_subkeys[i+5]);
#endif
        i += 6;
    }
    // Auxiliar para sub-chaves da ultima transformacao T
    uint16_t aux49 = decipher_subkeys[49];

    // Ultima transformacao T
    decipher_subkeys[49] = decipher_subkeys[50];
    decipher_subkeys[50] = aux49;

#if TESTES == 1
	printf("KD48: 0x%x\n", decipher_subkeys[48]);
	printf("KD49: 0x%x\n", decipher_subkeys[49]);
	printf("KD50: 0x%x\n", decipher_subkeys[50]);
	printf("KD51: 0x%x\n", decipher_subkeys[51]);
#endif

    SUBKEYS = decipher_subkeys;
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
	// Variavel temporaria para manipulacao da chave secreta
	uint64_t chave_secreta_high = ((uint64_t)REGS[6] << 32) | (uint64_t)REGS[5];
	uint64_t chave_secreta_low = ((uint64_t)REGS[4] << 32) | (uint64_t)REGS[3];
	uint64_t chave_secreta_aux;

	for(unsigned int i = 0; i < 52; i+=8){
		// Primeiras iteracaoes
		if(i < 8 && i < 48){
			// Geracao das sub-chaves apos o deslocamento
			SUBKEYS[i] = chave_secreta_high >> 48;
			SUBKEYS[i+1] = chave_secreta_high >> 32;
			SUBKEYS[i+2] = chave_secreta_high >> 16;
			SUBKEYS[i+3] = chave_secreta_high;
			SUBKEYS[i+4] = chave_secreta_low  >> 48;
			SUBKEYS[i+5] = chave_secreta_low  >> 32;
			SUBKEYS[i+6] = chave_secreta_low  >> 16;
			SUBKEYS[i+7] = chave_secreta_low;
#if TESTES == 1
			printf("K%d: 0x%x\n", i, SUBKEYS[i]);
			printf("K%d: 0x%x\n", i+1, SUBKEYS[i+1]);
			printf("K%d: 0x%x\n", i+2, SUBKEYS[i+2]);
			printf("K%d: 0x%x\n", i+3, SUBKEYS[i+3]);
			printf("K%d: 0x%x\n", i+4, SUBKEYS[i+4]);
			printf("K%d: 0x%x\n", i+5, SUBKEYS[i+5]);
			printf("K%d: 0x%x\n", i+6, SUBKEYS[i+6]);
			printf("K%d: 0x%x\n", i+7, SUBKEYS[i+7]);
#endif
		}

		// Iteracoes seguintes
		if(i >= 8 && i < 48){
			// Deslocamento circular de 25 bits
			chave_secreta_aux = chave_secreta_high;
			chave_secreta_high = (chave_secreta_high << 25) | (chave_secreta_low >> 39);
			chave_secreta_low = (chave_secreta_low << 25) | (chave_secreta_aux >> 39);

			// Geracao das sub-chaves apos o deslocamento
			SUBKEYS[i] = chave_secreta_high >> 48;
			SUBKEYS[i+1] = chave_secreta_high >> 32;
			SUBKEYS[i+2] = chave_secreta_high >> 16;
			SUBKEYS[i+3] = chave_secreta_high;
			SUBKEYS[i+4] = chave_secreta_low  >> 48;
			SUBKEYS[i+5] = chave_secreta_low  >> 32;
			SUBKEYS[i+6] = chave_secreta_low  >> 16;
			SUBKEYS[i+7] = chave_secreta_low;

#if TESTES == 1
			printf("K%d: 0x%x\n", i, SUBKEYS[i]);
			printf("K%d: 0x%x\n", i+1, SUBKEYS[i+1]);
			printf("K%d: 0x%x\n", i+2, SUBKEYS[i+2]);
			printf("K%d: 0x%x\n", i+3, SUBKEYS[i+3]);
			printf("K%d: 0x%x\n", i+4, SUBKEYS[i+4]);
			printf("K%d: 0x%x\n", i+5, SUBKEYS[i+5]);
			printf("K%d: 0x%x\n", i+6, SUBKEYS[i+6]);
			printf("K%d: 0x%x\n", i+7, SUBKEYS[i+7]);
#endif
		}

		// Ultima transformacao T
		if(i >= 48){
			// Deslocamento circular de 22 bits
			chave_secreta_aux = chave_secreta_high;
			chave_secreta_high = (chave_secreta_high << 25) | (chave_secreta_low >> 39);
			chave_secreta_low = (chave_secreta_low << 25) | (chave_secreta_aux >> 39);

			// Geracao das sub-chaves apos o deslocamento
			SUBKEYS[i] = chave_secreta_high >> 48;
			SUBKEYS[i+1] = chave_secreta_high >> 32;
			SUBKEYS[i+2] = chave_secreta_high >> 16;
			SUBKEYS[i+3] = chave_secreta_high;

#if TESTES == 1
			printf("K%d: 0x%x\n", i, SUBKEYS[i]);
			printf("K%d: 0x%x\n", i+1, SUBKEYS[i+1]);
			printf("K%d: 0x%x\n", i+2, SUBKEYS[i+2]);
			printf("K%d: 0x%x\n", i+3, SUBKEYS[i+3]);
#endif
		}
	}
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

	/* Dividindo as palavras para cripografia */
	// WORDS[0] = W0 = 2 bytes MENOS significativos de REGS[1]
	WORDS[0] = REGS[1] & 0xFFFF;

	// WORDS[1] = W1 = 2 bytes MAIS significativos de REGS[1]
	WORDS[1] = REGS[1] >> 16;

	// WORDS[2] = W2 = 2 bytes MENOS significativos de REGS[2]
	WORDS[2] = REGS[2] & 0xFFFF;

	// WORDS[3] = W3 = 2 bytes MAIS significativos de REGS[2]
	WORDS[3] = REGS[2] >> 16;

#if TESTES == 1|| TESTES == 2
	// Resultado separacao
	printf("\nW0: 0x%x\n", WORDS[0]);
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
#if TESTES == 1
		printf("W0: 0x%x\n", WORDS[0]);
		printf("W1: 0x%x\n", WORDS[1]);
		printf("W2: 0x%x\n", WORDS[2]);
		printf("W3: 0x%x\n\n", WORDS[3]);
#endif
	}
	// Final round
	// Xa_final = Xa' mul K49
	// Xb_final = Xc' add K50
	// Xc_final = Xb' add K51
	// Xd_final = Xd' mul K52
	half_round(WORDS,SUBKEYS[i], SUBKEYS[i+1], SUBKEYS[i+2], SUBKEYS[i+3]);

#if TESTES == 1
	// Resultado IDEA
	printf("\nMensagem resultante\n");
	printf("W0: 0x%x\n", WORDS[0]);
	printf("W1: 0x%x\n", WORDS[1]);
	printf("W2: 0x%x\n", WORDS[2]);
	printf("W3: 0x%x\n\n", WORDS[3]);
#endif

	// Armazenando o resultado
	REGS[1] = WORDS[0];
    REGS[1] |= (WORDS[1] << 16);
    REGS[2] = WORDS[2];
    REGS[2] |= (WORDS[3] << 16);
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

void idea::execute(void){
    shell_idea_data_t *fromShell;
    idea_shell_data_t *toShell;
    while (1) {
        fromShell = idea_in.read();
        if(fromShell->acao == READ){
            toShell = new uint32_t(REGS[fromShell->reg_index]);
            idea_out.write(toShell);
        }
        else if (fromShell->acao == WRITE) {
           REGS[fromShell->reg_index] = fromShell->value;
           if(fromShell->reg_index == CMD){
               switch ((idea_cmd_t)REGS[CMD]){
                   case IDEA_CYPHER:
                       subchaves_cifrar();
                       descifrar_cifrar();
                       break;
                   case IDEA_DECYPHER:
                       subchaves_descifrar();
                       descifrar_cifrar();
                       break;
                   case IDEA_BKEYS:
                   case IDEA_IDLE:
                   case NONE:
                   default:
                       break;
               }
           }
        }
        //delete fromShell;
    }
}
