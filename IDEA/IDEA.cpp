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
    int i = 4;
    uint16_t *decipher_subkeys = new uint16_t[52];
    decipher_subkeys[0] = mul_inv(SUBKEYS[48],65537);
    decipher_subkeys[1] = add_inv(SUBKEYS[49]);
    decipher_subkeys[2] = add_inv(SUBKEYS[50]);
    decipher_subkeys[3] = mul_inv(SUBKEYS[51],65537);
    while (i < 52) {
        decipher_subkeys[i] = SUBKEYS[50-i];
        decipher_subkeys[i+1] = SUBKEYS[51-i];
        decipher_subkeys[i+2] = mul_inv(SUBKEYS[46-i],65537);
        decipher_subkeys[i+3] = add_inv(SUBKEYS[48-i]);
        decipher_subkeys[i+4] = add_inv(SUBKEYS[47-i]);
        decipher_subkeys[i+5] = mul_inv(SUBKEYS[49-i],65537);
        i += 6;
    }
    delete [] SUBKEYS;
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
    int i,j,k, offset, n_bits, T_transf;
    i = 0;
    T_transf = 0;
    for (k = 0; k < 7; k++) {
        offset = T_transf ? 22 : 25*k;
        j = (offset/32)%4;
        n_bits = 32 - (offset - j*32);
        while (i < (k*8)+8 || (T_transf && i < 52)) {
            int bits_missing, bits_remaining;
            if(16 > n_bits){
                bits_missing = 16 - n_bits;
                bits_remaining = 0;
            }
            else{
                bits_missing = 0;
                bits_remaining = n_bits - 16;
            }
            uint32_t amount = (uint32_t)(((int64_t)1 << n_bits)-1);
            SUBKEYS[i] = (int16_t)(((REGS[j+3] & amount) >> bits_remaining) << bits_missing);
            if(bits_missing){
                j = (j + 1)%4;
                SUBKEYS[i] |= (int16_t)(REGS[j+3] >> (32 - bits_missing));
            }
            n_bits = (bits_missing ? 32 - bits_missing : bits_remaining);
            i++;
        }
        if(i >= 48 && i < 52){
            T_transf = 1;
        }
        else{
            T_transf = 0;
        }
    }
}

/*
 * Inverso Aditivo
 *
 * Entradas:
 * 	- int16_t number : numero de 16 bits que deseja-se calcular o inverso aditivo 
 * Saidas:
 *  - inverso aditivo de number
 */
int16_t idea::add_inv(int16_t number){
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
int16_t idea::mul_inv(int32_t a, int32_t m) {
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
                       subchaves_cifrar();
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
        delete fromShell;
    }
}
