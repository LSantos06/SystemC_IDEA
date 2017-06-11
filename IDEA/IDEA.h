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

#include <systemc.h>

/* Registradores (32 bits) do modulo:
 *	[0] = CMD
 *
 *	[1] = W0W1
 *	[2] = W2W3
 *
 *  [3] = KG0
 *  [4] = KG1
 *  [5] = KG2
 *  [6] = KG3
 */
const short N_REGS = 7;

class idea
	: public sc_module{

public:
	/* Portas */


	SC_HAS_PROCESS(idea);

	/* Construtor */
	idea(sc_module_name nome_)
		: sc_module(nome_){

		// Inicializando os regs
		REGS = new uint32_t[N_REGS];
	    for (unsigned int i = 0; i < N_REGS; ++i)
	    	REGS[i] = 0;
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
	// Descifrar uma entrada (64 bits)
	void descifrar();
	// Cifrar uma entrada (64 bits)
	void cifrar();
	// Status atual do modulo de acordo com a enum
	void getStatus();

private:
	// Registradores (32 bits)
	uint32_t *REGS;

};


#endif
