#include "IDEA_shell.h"
#include "IDEA_utils.h"
#include <vector>
#include <iostream>

IDEA_Shell::IDEA_Shell(sc_module_name name) : sc_module(name) {
    SC_THREAD(execute);
}

void IDEA_Shell::execute(void) {
    shell_idea_data_t *toIdea;
    idea_shell_data_t *fromIdea;
    while (1) {
        int payloadSrc;
        std::vector<uint32_t> payload;
        receivePayload(payload,&payloadSrc);
        toIdea = new shell_idea_data_t();
        switch ((reg_index_t)payload.at(0)) {
            case CIFRA_OUT_H:
                toIdea->acao = READ;
                toIdea->reg_index = W1W0;
                toIdea->value = 0;
                shell_out.write(toIdea);
                fromIdea = shell_in.read();
                payload.clear();
                payload.push_back(static_cast<uint32_t>(*fromIdea));
                sendPayload(payload,payloadSrc);
                delete fromIdea;
                payload.clear();
                break;
            case CIFRA_OUT_L:
                toIdea->acao = READ;
                toIdea->reg_index = W3W2;
                toIdea->value = 0;
                shell_out.write(toIdea);
                fromIdea = shell_in.read();
                payload.clear();
                payload.push_back(static_cast<uint32_t>(*fromIdea));
                sendPayload(payload,payloadSrc);
                delete fromIdea;
                payload.clear();
                break;
            case CIFRA_IN_H:
                toIdea->acao = WRITE;
                toIdea->reg_index = W1W0;
                toIdea->value = payload.at(1);
                shell_out.write(toIdea);
                payload.clear();
                break;
            case CIFRA_IN_L:
                toIdea->acao = WRITE;
                toIdea->reg_index = W3W2;
                toIdea->value = payload.at(1);
                shell_out.write(toIdea);
                payload.clear();
                break;
            case CHAVE_128_3:
                toIdea->acao = WRITE;
                toIdea->reg_index = KG3;
                toIdea->value = payload.at(1);
                shell_out.write(toIdea);
                payload.clear();
                break;
            case CHAVE_128_2:
                toIdea->acao = WRITE;
                toIdea->reg_index = KG2;
                toIdea->value = payload.at(1);
                shell_out.write(toIdea);
                payload.clear();
                break;
            case CHAVE_128_1:
                toIdea->acao = WRITE;
                toIdea->reg_index = KG1;
                toIdea->value = payload.at(1);
                shell_out.write(toIdea);
                payload.clear();
                break;
            case CHAVE_128_0:
                toIdea->acao = WRITE;
                toIdea->reg_index = KG0;
                toIdea->value = payload.at(1);
                shell_out.write(toIdea);
                payload.clear();
                break;
            case COMMAND:
                toIdea->acao = WRITE;
                toIdea->reg_index = CMD;
                toIdea->value = payload.at(1);
                shell_out.write(toIdea);
                payload.clear();
            default:
                break;
        }
    }
}
