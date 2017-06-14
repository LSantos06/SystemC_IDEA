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
 * Linha 1 de um round ou half-round
 *
 * Entradas:
 * 	- 4 primeiras sub-chaves de 16 bits
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 4 palavras de 16 bits operadas
 */
void linha_1(uint16_t, uint16_t, uint16_t, uint16_t){

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

/*
 * Um round de operacoes
 *
 * Entradas:
 * 	- 4 palavras de 16 bits
 * Saidas:
 *  - 4 palavras de 16 bits operadas
 */
// Round de operacoes repetido 8 vezes
void round(){
//	linha_1();
//	linha_2_3();
//	linha_4_5();
//	linha_6_7();
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
void half_round(){
//	linha_1();
}
