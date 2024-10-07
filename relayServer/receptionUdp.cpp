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

volatile sig_atomic_t stopF = 0;

void signalHandler(int signum)
{
    cout << "\nStopping the program..." << endl;
    stopF = 1;
}

int makeSocketUDP()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0); // 修正ポイント
    return sockfd;
}

int reception(int sockfd, int openPort)
{
    // シグナルハンドラの設定
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    int result;
    char buffer[1024];
    struct sockaddr_in localAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET; 
    localAddr.sin_port = htons(openPort);
    localAddr.sin_addr.s_addr = INADDR_ANY; 

    if (bind(sockfd, (struct sockaddr*)&localAddr, sizeof(localAddr)) != 0) // 修正ポイント
    {
        cerr << "Failed bind: " << strerror(errno) << endl;
        close(sockfd);
        return -1;
    }

    cout << "Starting reception......" << endl;

    while (stopF == 0)
    {
        result = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrLen);

        if (result == -1)
        {
            cout << "Failed reception: " << strerror(errno) << endl; // 強化
        }

        buffer[result] = '\0';
        cout << "Received message: " << buffer << endl;

        // 送信元アドレスの表示（オプション）
        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
        cout << "From IP: " << clientIP << ", Port: " << ntohs(clientAddr.sin_port) << endl;
    }

    close(sockfd); // ソケットを閉じる
    return 0;
}
