#ifndef _IDEA_SHELL_H
#define _IDEA_SHELL_H

#include <systemc.h>
#include <stdint.h>
#include "IDEA_utils.h"

#include "networkinterfacefrontendbase.h"

class IDEA_Shell : public sc_module, public NetworkInterfaceFrontEndBase
{
    SC_HAS_PROCESS(IDEA_Shell);
    void execute(void);
public:
    sc_fifo_out<shell_idea_data_t *> shell_out;
    sc_fifo_in<idea_shell_data_t *> shell_in;
    IDEA_Shell(sc_module_name name);
};

#endif // _IDEA_SHELL_H
