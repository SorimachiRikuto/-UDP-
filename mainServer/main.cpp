#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "portForward.h"

using namespace std;

int main(int argc, const char *argv[])
{
	// IP AddressとPort番号を指定させ、もし正しく指定されていない場合はプログラムを停止させる。
	if (argc != 3)
	{
		cout << "Using: " << argv[0] << " <Relay Server IP Address> <Port Number>" << endl;
		return -1;
	}

	// main関数の引数からRelay ServerのIP AddressとPort番号を設定する
	const char *RelayIP = argv[1];
	int  RelayPort = (int*)argv[2];
	int  sockfd = makeSocketUDP();

	// ソケット作成に失敗した場合、プログラムを停止させる。
	if (sockfd == -1)
	{
		cout << "Failed make sockedt" << endl;
	}

	sendRelayServer(sockfd, RelayIP, RelayPort);

	return 0;
}

/***********
 * UDP用ソケットを作成
 * *********/
int makeSocketUDP()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	return sockfd;
}

