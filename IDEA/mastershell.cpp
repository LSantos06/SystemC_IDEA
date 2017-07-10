#include "mastershell.h"
#include <stdio.h>
#include <iostream>

/* Registradores (32 bits) do modulo IDEA:
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

MasterShell::MasterShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void MasterShell::_threadRun()
{
    uint32_t message[2] = {0x01234567, 0x8ABCDEF0};
	uint32_t encrypted_message[2];
	uint32_t decrypted_message[2];
    int payloadSrc;
    int payloadDst = 1;
    std::vector<uint32_t> payload;

    printf("Message = 0x%08x, 0x%08x\n", message[0], message[1]);
    
    // Sending values of message and key to encrypt
    // HIGH FIRST
    // REGS[2]
    payload.push_back(2);
    payload.push_back(message[1]);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();

    // REGS[1]
    payload.push_back(3);
    payload.push_back(message[0]);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();

    // REGS[6]
    payload.push_back(4);
    payload.push_back(0x00010002);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();

    // REGS[5]
    payload.push_back(5);
    payload.push_back(0x00030004);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();

    // REGS[4]
    payload.push_back(6);
    payload.push_back(0x00050006);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();

    // REGS[3]
    payload.push_back(7);
    payload.push_back(0x00070008);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();
    
    // Sending generate keys command
    payload.push_back(8);
    payload.push_back(2);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();
    
    // Sending cypher command 
    payload.push_back(8);
    payload.push_back(3);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();
    
    // Reading the message encrypted
    // REGS[2]
    payload.push_back(0);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    encrypted_message[1] = payload.at(0);
    payload.clear();

    // REGS[1]
    payload.push_back(1);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    encrypted_message[0] = payload.at(0);
    payload.clear();

    printf("Message encrypted = 0x%08x, 0x%08x\n", encrypted_message[0], encrypted_message[1]);
       
    // Sending generate keys command
    payload.push_back(8);
    payload.push_back(2);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();
    
    // Sending decrypt command
    payload.push_back(8);
    payload.push_back(4);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    payload.clear();
    
    // Reading the message decrypted
    // REGS[2]
    payload.push_back(0);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    decrypted_message[1] = payload.at(0);
    payload.clear();

    // REGS[1]
    payload.push_back(1);
    sendPayload(payload, payloadDst);
    receivePayload(payload, &payloadSrc);
    decrypted_message[0] = payload.at(0);
    payload.clear();
    printf("Message decrypted = 0x%08x, 0x%08x\n", decrypted_message[0], decrypted_message[1]);
}
