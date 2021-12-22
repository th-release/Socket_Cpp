// ClientSocket.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <WinSock2.h>
#pragma warning(suppress : 4996)
#pragma comment (lib, "ws2_32")

#define PORT 4578
#define PACKET_SIZE 1024

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	SOCKET hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

	SOCKADDR_IN tAddr = {};
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	connect(hSocket, (SOCKADDR*)&tAddr, sizeof(tAddr));

	char cMsg[] = "클라이언트에서 알립니다.";
	send(hSocket, cMsg, strlen(cMsg), 0);

	char cBuffer[PACKET_SIZE] = {};
	recv(hSocket, cBuffer, PACKET_SIZE, 0);

	std::cout << "받은 메세지 : " << cBuffer;
	closesocket(hSocket);

	WSACleanup();
	return 0;
}
