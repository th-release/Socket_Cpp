#include <iostream>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

#define PORT 4578
#define PACKET_SIZE 1024

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    // # 소켓을 사용하기위한 헤더 include 및 기본설정 지정 7 ~ 8 WSACleanup();
    SOCKET hListen;
    hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    // # 소켓 생성 10 ~ 11
    SOCKADDR_IN tListenAddr = { };
    tListenAddr.sin_family = AF_INET;
    tListenAddr.sin_port = htons(PORT); 
    tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // # 소켓의 구성요소를 담을 구조체 생성 및 값 할당 13 ~ 16

    bind(hListen, (SOCKADDR*)&tListenAddr, sizeof(tListenAddr));
    listen(hListen, SOMAXCONN);
    // # 소켓에 위에 설정한 주소정보를 묶어주고, 소켓을 접속대기상태로 만들어줌

    SOCKADDR_IN tClntAddr = {};
    int iClntSize = sizeof(tClntAddr);
    SOCKET hClient = accept(hListen, (SOCKADDR*)&tClntAddr, &iClntSize);
    // # 클라이언트 측 소켓 생성 및 정보를 담을 구조체 생성 및 값 할당, 클라이언트가 접속 요청하면 승인해주는 역할 22 ~ 24
    
    char cBuffer[PACKET_SIZE] = {};
    recv(hClient, cBuffer, PACKET_SIZE, 0);
    std::cout << "받은 메세지 : " << cBuffer;
    char cMsg[] = "서버에서 알립니다.";
    send(hClient, cMsg, strlen(cMsg), 0);

    closesocket(hClient);
    closesocket(hListen);
    // #  클라이언트 측으로부터 정보를 받아오고 출력, 클라이언트에 정보 전송 28 ~ 35

    WSACleanup();
}
