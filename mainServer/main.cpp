#include <sys/socket.h> 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include "portForward.h"

using namespace std;

/*********
 * main関数
 * argv[1],argv[2]で起動時にIP AddresとPort番号を受け取る
 * *******/
int main(int argc, const char *argv[])
{
	// IP AddressとPort番号を指定させ、もし正しく指定されていない場合はプログラムを停止させる。
	if (argc != 3)
	{
		cout << "Using: " << argv[0] << " <Relay Server IP Address> <Port Number>" << endl;
		return -1;
	}


	int Result;
	// main関数の引数からRelay ServerのIP AddressとPort番号を設定する
	const char *RelayIP = argv[1];
	int  RelayPort = atoi(argv[2]);
	int  sockfd = makeSocketUDP();

	// ソケット作成に失敗した場合、プログラムを停止させる。
	if (sockfd == -1)
	{
		cout << "Failed make sockedt" << endl;
	}

	Result = sendRelayServer(sockfd, RelayIP, RelayPort);

	if (Result == -1)
	{
		cout << "Sending failure" << endl;

		return -1;
	}

	return 0;
}

/***********
 * UDP用ソケットを作成
 * 失敗した場合-1を返す
 * *********/
int makeSocketUDP()
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	return sockfd;
}

/**********
 * 以下シグナルハンドラの設定
 * ********/

volatile sig_atomic_t stopF = 0;

void signalHandler(int signum)
{
	cout << "\nStopping the program..." << endl;
	stopF = 1;
}

