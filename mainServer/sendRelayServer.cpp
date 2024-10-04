#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "portForward.h"

#define PAR_FAIL 10

using namespace std;

int sendRelayServer(int sockfd, const char *RelayIP, int RelayPort)
{
	const char *msg = "Hello Server";
	struct sockaddr_in serverAddr;
	int sentResult, failCount;

	// Relay Serverの設定
	memset(&serverAddr, 0, sizeof(serverAddr)); // ServerAddrの初期化
	serverAddr.sin_family = AF_INET; // UDP
	serverAddr.sin_port = htons(RelayPort); // Port
	serverAddr.sin_addr.s_addr = inet_addr(RelayIP); // IP Adress

	// 送信&受信
	while (!stopF)
	{
		// 送信部分
		sentResult = sendto(sockfd, msg, strlen(msg), 0, (struct sockaddr *)&serverAddr, sizeof(serverAddr));

		// 一定回数以上送信に失敗した場合プログラムを停止
		if (sentResult == -1) {++failCount;}
		if (failCount > PAR_FAIL) {return -1;}
	}

	return 0;
}