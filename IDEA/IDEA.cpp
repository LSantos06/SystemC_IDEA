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
 * Descifrar uma entrada (64 bits)
 *
 * Entradas:
 * 	- 52 sub-chaves (16 bits cada) para descifrar
 * 	- registradores W (64 bits) com texto ilegivel
 * Saidas:
 *  - registradores W (64 bits) com texto legivel
 */
void idea::descifrar(){

}

/*
 * Cifrar uma entrada (64 bits)
 *
 * Entradas:
 * 	- 52 sub-chaves (16 bits cada) para descifrar
 * 	- registradores W (64 bits) com texto legivel
 * Saidas:
 *  - registradores W (64 bits) com texto ilegivel
 */
void idea::cifrar(){

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

