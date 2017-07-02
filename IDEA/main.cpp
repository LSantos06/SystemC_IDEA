/*
 *  IDEA
 *  Modelagem de Sistemas em Silicio
 *  1/2017
 *
 *  Lucas Avelino 13/0013072
 *  Lucas Santos 14/0151010
 */


#include <systemc.h>
#include "mastershell.h"
#include "specialkernel.h"
#include "IDEA.h"
#include "IDEA_shell.h"
#include "IDEA_utils.h"

int main()
{
    MasterShell masterShell("MasterShell");

    idea IDEA_i("IDEA_i");
    IDEA_Shell IDEA_Shell_i("IDEA_Shell_i");
    sc_fifo<shell_idea_data_t> shell_idea_fifo(1);
    sc_fifo<idea_shell_data_t> idea_shell_fifo(1);
    IDEA_i.idea_out(idea_shell_fifo);
    IDEA_Shell_i.shell_in(idea_shell_fifo);
    IDEA_Shell_i.shell_out(shell_idea_fifo);
    IDEA_i.idea_in(shell_idea_fifo);

    SpecialKernel multKernel("specialKernel");
    multKernel.connectMaster(&masterShell);
    multKernel.connectSlave(&IDEA_i);

    sc_start(sc_time(100, SC_SEC),  SC_RUN_TO_TIME);
    return 0;
}

