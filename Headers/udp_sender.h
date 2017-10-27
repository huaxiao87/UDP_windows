/*Written by Hua Xiao on Oct 26, 2017
See:http://www.cnblogs.com/churi/archive/2013/02/27/2935427.html
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") 

using namespace std;

class UDPSender {
public:
	UDPSender(const char* ipAddress, const int portNumber) {

		bindTo(ipAddress, portNumber);
	}
	virtual ~UDPSender() {
		closesocket(clientSocket);
		WSACleanup();
	}
	void bindTo(const char* ipAddress, const int portNumber) {
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsaData;

		if (WSAStartup(sockVersion, &wsaData) != 0) {
			closesocket(clientSocket);
			return;
		}

		clientSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (clientSocket == INVALID_SOCKET) {
			closesocket(clientSocket);
			return;
		}

		sockaddr_in clientAddr;
		clientAddr.sin_family = AF_INET;
		clientAddr.sin_port = htons(portNumber);
		clientAddr.sin_addr.S_un.S_addr = inet_addr(ipAddress);
		if (connect(clientSocket, (sockaddr *)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR)
		{
			closesocket(clientSocket);
			return;
		}
		else { printf("Successfully binded to port %d\n", portNumber); }
	}
	void sendData(char* data) {
		send(clientSocket, data, strlen(data), 0);
	}

private:
	SOCKET clientSocket;
};
