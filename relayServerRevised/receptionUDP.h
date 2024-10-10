#ifndef receptionUDP_H
#define receptionUDP_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <errno.h>
#include <signal.h>
#include "openUdp.h"

using namespace std;


/*******
* 機能:UDP通信を行うためのクラス
* 返り値:
* 説明事項:
*******/
class receptionUDP
{
public:
    receptionUDP(int port); 
    receptionUDP();
    ~receptionUDP(); 
    int reception();

private:
    int makeSocketUDP();
    int udpBind();

    int sockfd;
    char buffer[1024];
    struct sockaddr_in localAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);
};

#endif