#ifndef portForward_H
#define portForward_H

#include <signal.h>
#include <iostream>

using namespace std;

// 関数の宣言
int makeSocketUDP();
int sendRelayServer(int sockfd, const char* RelayIP, int RelayPort);

// シグナルハンドラの宣言
extern volatile sig_atomic_t stopF;
void signalHandler(int);

#endif