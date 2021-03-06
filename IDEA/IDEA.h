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
#include "IDEA_utils.h"

const short N_REGS = 7;
const short N_WORDS = 4;
const short N_SUBKEYS = 52;
const short N_ROUNDS = 8;

class idea
	: public sc_module{

public:
	SC_HAS_PROCESS(idea);

	/* Construtor */
	idea(sc_module_name nome_);
	/* Destrutor */
	~idea();

	/* Processos */
	// Geracao das 52 subchaves para descifrar
	void subchaves_descifrar();
	// Geracao das 52 subchaves para cifrar
	void subchaves_cifrar();
	// Descifrar ou Cifrar uma entrada (64 bits)
	void descifrar_cifrar();

    sc_fifo_in<shell_idea_data_t *> idea_in;
    sc_fifo_out<idea_shell_data_t *> idea_out;

    void execute(void);

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
};


#endif
