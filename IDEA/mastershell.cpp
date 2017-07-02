#include "mastershell.h"
#include <stdio.h>


MasterShell::MasterShell(sc_module_name name) :
    sc_module(name)
{
    SC_THREAD(_threadRun);
}

void MasterShell::_threadRun()
{
	uint32_t encrypted_message[2];
	uint32_t decrypted_message[2];
    int payloadSrc;
    int payloadDst = 1;
    std::vector<uint32_t> payload;
    
    // Sending values of message and key to encrypt
    payload.push_back(2);
    payload.push_back(0x00020003);
    sendPayload(payload,payloadDst);
    payload.clear();
    payload.push_back(3);
    payload.push_back(0x00000001);
    sendPayload(payload,payloadDst);
    payload.clear();
    payload.push_back(4);
    payload.push_back(0x00070008);
    sendPayload(payload,payloadDst);
    payload.clear();
    payload.push_back(5);
    payload.push_back(0x00050006);
    sendPayload(payload,payloadDst);
    payload.clear();
    payload.push_back(6);
    payload.push_back(0x00030004);
    sendPayload(payload,payloadDst);
    payload.clear();
    payload.push_back(7);
    payload.push_back(0x00010002);
    sendPayload(payload,payloadDst);
    payload.clear();
    
    // Sending generate keys command
    payload.push_back(8);
    payload.push_back(2);
    sendPayload(payload,payloadDst);
    payload.clear();
    
    // Sending cypher command 
    payload.push_back(8);
    payload.push_back(3);
    sendPayload(payload,payloadDst);
    payload.clear();
    
    // Reading the message encrypted
    payload.push_back(0);
    sendPayload(payload,payloadDst);
    receivePayload(payload, &payloadSrc);
    encrypted_message[1] = payload.at(0);
    payload.clear();
    payload.push_back(1);
    sendPayload(payload,payloadDst);
    receivePayload(payload, &payloadSrc);
    encrypted_message[0] = payload.at(0);
    payload.clear();
    printf("Message encrypted = #04x, #04x", encrypted_message[0], encrypted_message[1]);
       
    // Sending generate keys command
    payload.push_back(8);
    payload.push_back(2);
    sendPayload(payload,payloadDst);
    payload.clear();
    
    // Sending decrypt command
    payload.push_back(8);
    payload.push_back(4);
    sendPayload(payload,payloadDst);
    payload.clear();
    
    // Reading the message decrypted
    payload.push_back(0);
    sendPayload(payload,payloadDst);
    receivePayload(payload, &payloadSrc);
    decrypted_message[1] = payload.at(0);
    payload.clear();
    payload.push_back(1);
    sendPayload(payload,payloadDst);
    receivePayload(payload, &payloadSrc);
    decrypted_message[0] = payload.at(0);
    payload.clear();
    printf("Message decrypted = #04x, #04x", decrypted_message[0], decrypted_message[1]);
}
