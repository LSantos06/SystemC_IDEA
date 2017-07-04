/*
 *  IDEA
 *  Modelagem de Sistemas em Silicio
 *  1/2017
 *
 *  Lucas Avelino 13/0013072
 *  Lucas Santos 14/0151010
 */

#ifndef IDEA_H
#define IDEA_H

#include "IDEA_rounds.h"

const short N_REGS = 7;
const short N_WORDS = 4;
const short N_SUBKEYS = 52;
const short N_ROUNDS = 8;

class idea
	: public sc_module{

public:
	/* Portas */


	SC_HAS_PROCESS(idea);

	/* Construtor */
	idea(sc_module_name nome_)
		: sc_module(nome_){

		// Inicializando os REGS
		REGS = new uint32_t[N_REGS];
	    for (unsigned int i = 0; i < N_REGS; ++i)
	    	REGS[i] = 0;
		// Inicializando as SUBKEYS
	    SUBKEYS = new uint16_t[N_SUBKEYS];
	    for (unsigned int i = 0; i < N_SUBKEYS; ++i)
	    	SUBKEYS[i] = 0;

	}

	/* Destrutor */
	~idea();

	/* Processos Herdados */


	/* Processos */
	// Pega o comando e decide a acao
	void getCMD();

	// Geracao das 52 subchaves para descifrar
	void subchaves_descifrar();
	// Geracao das 52 subchaves para cifrar
	void subchaves_cifrar();
	// Descifrar ou Cifrar uma entrada (64 bits)
	void descifrar_cifrar();

	// Status atual do modulo de acordo com a enum
	void getStatus();

private:
	/* Registradores (32 bits) do modulo:
	 *	[0] = CMD
	 *
	 *	[1] = W1W0
	 *	[2] = W3W2
	 *
	 *	[3] = KG0
	 *	[4] = KG1
	 *	[5] = KG2
	 *	[6] = KG3
	 */
	uint32_t *REGS;

	// Sub-chaves (16 bits)
	uint16_t *SUBKEYS;

    int16_t add_inv(int16_t number);
    int16_t mul_inv(int32_t a, int32_t m);

};


#endif
