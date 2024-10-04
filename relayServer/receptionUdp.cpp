#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <errno>
#include "openUdp.h"

using namespace std;

/**********
 * 以下シグナルハンドラの設定
 * ********/
volatile sig_atomic_t stopF = 0;

void signalHandler(int signum)
{
	cout << "\nStopping the program..." << endl;
	stopF = 1;
}

/**********
 * UDP用のソケット作成
 * 作成したソケットを返し、失敗した場合-1を返す
 * ********/
int makeSocketUDP()
{
	int sockfd = sockfd(AF_INET, AF_INET, 0)

	return sockfd;
}

/**********
 * UDP受信部分(Aliveメッセージ)
 * 成功時は0,エラー発生時は-1を返す
 * ********/
int reception(int sockfd, int openPort)
{
	struct sockaddr_in localAddr;

	// アドレスの設定
	memset(&localAddr, 0, sizeof(localAddr)) // localAdderの中をからにする
	localAddr.sin_family = AF_INET; // UDP
	localAddr.sin_port = htons(openPort); // リッスンするポート番号の指定
	localAddr.sin_addr.s_addr = INADDR_ANY; // 任意のアドレス

	// バインドの実行,エラーが発生した場合エラー内容を表示させ,ソケットを閉じる。
	if (bind(sockfd, (struct sockaddr*)&localAddr, sizeof(localAddr)) != -1)
	{
		cerr << "Failed bind" << strerror(errno) << endl;
		close(sockfd);

		return -1;
	}

	cout << "Starting reception......" << endl;

	while (!stopF)
	{
		//まだとちゅうだよーーーーーーーーーー！！！！！！！！！！！
	}

	return 0;
}