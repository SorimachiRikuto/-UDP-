/***********
 * リレーサーバー側
 * *********/

#include <iostream>
#include "openUdp.h"

using namespace std;

/*********
 * main関数
 * argv[1]で起動時にPort番号を受け取る
 * 正常終了時は0,エラー発生時は-1
 * *******/
int main(int argc, const char *argv[])
{
	// 開放するポート番号が指定されていない場合、停止させる。
	if (argc != 2)
	{
		cout << "Using: " << argv[0] << " <Port Number>" << endl;

		return -1;
	}

	int result;
	// 実行時に入力されたポート番号を取得し、UDPソケットを作成する
	int openPort = atoi(argv[1]);
	int  sockfd = makeSocketUDP();

	// ソケット作成が失敗した場合、停止させる
	if (sockfd == -1)
	{
		cout << "Failed make sockedt" << endl;

		return -1;
	}

	result = reception(sockfd, openPort);

	if (result == -1)
	{
		cout << "Reception failed" << endl;

		return -1;
	}

	return 0;

}