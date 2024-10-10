#include "receptionUDP.h"

///////////////////*シグナルハンドラの定義*/////////////////////////////////////////

volatile sig_atomic_t stopF = 0;

/*******
* 機能:シグナルやkillコマンドを検知した場合、receptionUDP::receptionの動作を停止させる
* 返り値:
* 説明事項:stopFに1を代入させ、ループを停止させる
*******/
void signalHandler(int signum)
{
    cout << "\nStopping the program..." << endl;
    stopF = 1;
}

///////////////////*以下メンバ変数の定義*/////////////////////////////////////

/*******
* 機能:コンストラクタ
* 返り値:
* 説明事項:localAddrの初期化
*******/
receptionUDP::receptionUDP(int port) 
{
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET; 
    localAddr.sin_addr.s_addr = INADDR_ANY;
    localAddr.sin_port = htons(port);
    if (makeSocketUDP() == -1) { exit(EXIT_FAILURE); }
}

/*******
* 機能:コンストラクタ(引数なし)
* 返り値:
* 説明事項:
*******/
receptionUDP::receptionUDP()
{
    cout << "Port number not specified" << endl;
    exit(EXIT_FAILURE);
}


/*******
* 機能:デストラクタ
* 返り値:
* 説明事項:ソケットを閉じていない場合は閉じる
*******/
receptionUDP::~receptionUDP() 
{
    if (sockfd != -1)
    {
        close(sockfd);
    }
}

/*******
* 機能:受信するためのソケットを作成
* 返り値:成功(0)失敗(-1)
* 説明事項:
*******/
int receptionUDP::makeSocketUDP()
{
    sockfd = socket(AF_INET, SOCK_DGRAM, 0); // ソケット作成

    if (sockfd == -1) // 失敗時 
    {
        cerr << "Socket creation failed: " << strerror(errno) << endl;
        return -1;
    }

    return 0; // 成功時
}

/*******
* 機能:ソケットをバインドさせる
* 返り値:成功(0)失敗(-1)
* 説明事項:
*******/
int receptionUDP::udpBind()
{
    if (bind(sockfd, (struct sockaddr*)&localAddr, sizeof(localAddr)) != 0)
    {
        cerr << "Failed bind: " << strerror(errno) << endl;
        close(sockfd);
        return -1;
    }

    return 0;
}

/*******
* 機能:サーバー間の通信を開始する
* 返り値:成功(0)失敗(-1)
* 説明事項:
*******/
int receptionUDP::reception()
{
    int result;

    // シグナルハンドラの設定
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);
    
    // ソケットのバインド
    udpBind();

    cout << "Starting reception......" << endl;

    while (stopF == 0)
    {
        result = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&clientAddr, &addrLen);

        if (result == -1)
        {
            cout << "Failed reception: " << strerror(errno) << endl;
        }
        else
        {
            buffer[result] = '\0'; // 終端文字を追加
            cout << "Received message: " << buffer << endl;

            // 送信元アドレスの表示
            char clientIP[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
            cout << "From IP: " << clientIP << ", Port: " << ntohs(clientAddr.sin_port) << endl;
        }

        // 一度受信した場合、しばらく停止させる
        sleep(10);
    }

    close(sockfd); // ソケットを閉じる
    return 0;
}