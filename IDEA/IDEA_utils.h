#ifndef _IDEA_UTILS_H
#define _IDEA_UTILS_H

#define     CMD     (0u)
#define     W1W0    (1u)
#define     W3W2    (2u)
#define     KG0     (3u)
#define     KG1     (4u)
#define     KG2     (5u)
#define     KG3     (6u)

enum idea_action_t {
    READ=0,
    WRITE
};

enum idea_cmd_t {
	NONE=0,
	IDEA_IDLE,
	IDEA_BKEYS,
	IDEA_CYPHER,
	IDEA_DECYPHER
};

enum reg_index_t { 
    CIFRA_OUT_H=0, 
    CIFRA_OUT_L,
    CIFRA_IN_H,
    CIFRA_IN_L,
    CHAVE_128_3,
    CHAVE_128_2,
    CHAVE_128_1,
    CHAVE_128_0,
    COMMAND,
    STATUS
};

struct shell_idea_data_t {
	idea_action_t acao;
	uint32_t reg_index;
	uint32_t value;
};

typedef uint32_t idea_shell_data_t;

#endif //_IDEA_UTILS_H
