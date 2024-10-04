#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "portForward.h"

using namespace std;

int sendRelayServer(int sockfd, const char *RelayIP, int RelayPort)
{
	const char *msg = "Hello Server";
	struct sockaddr_in serverAddr;
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(RelayPort);
	serverAddr.sin_addr.s_addr = inet_addr(RelayIP);
}