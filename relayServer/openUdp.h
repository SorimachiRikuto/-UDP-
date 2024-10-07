#ifndef openUdp_H
#define openUdp_H

#include <signal.h>
#include <iostream>

using namespace std;

// シグナルハンドラの宣言
extern volatile sig_atomic_t stopF;
void signalHandler(int signum);

// 関数の宣言
int makeSocketUDP();
int reception(int sockfd, int openPort);

#endif