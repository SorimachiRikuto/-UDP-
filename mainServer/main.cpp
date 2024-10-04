/**********
 * クライアント側
 * ********/

#include <iostream>
#include "portForward.h"

using namespace std;

/*********
 * main関数
 * argv[1],argv[2]で起動時にIP AddresとPort番号を受け取る
 * 正常終了0,異常終了-1
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

	// 送信を行う関数を呼び出す
	Result = sendRelayServer(sockfd, RelayIP, RelayPort);

	// 一定回数以上送信に失敗した場合停止
	if (Result == -1)
	{
		cout << "Sending failure" << endl;

		return -1;
	}

	return 0;
}



