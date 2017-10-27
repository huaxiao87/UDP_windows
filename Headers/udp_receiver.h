/*Written by Hua Xiao on Oct 26, 2017
See:http://www.cnblogs.com/churi/archive/2013/02/27/2935427.html
*/
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib") 

class UDPReceiver {
public:
	UDPReceiver(const int portNumber, const int bufferLen):bufferLength(bufferLen) {
		dataBuffer = new char[bufferLength];
		bindTo(portNumber);
	}
	virtual ~UDPReceiver() {
		delete dataBuffer;
		dataBuffer = 0;
		closesocket(serSocket);
		WSACleanup();
	}
	void bindTo(const int portNumber) {
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wsaData;

		if (WSAStartup(sockVersion, &wsaData) != 0) {
			closesocket(serSocket);
			return;
		}

		serSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (serSocket == INVALID_SOCKET) {
			closesocket(serSocket);
			return;
		}

		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(portNumber);
		serAddr.sin_addr.S_un.S_addr = INADDR_ANY;
		if (bind(serSocket, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{
			closesocket(serSocket);
			return;
		}
		else { printf("Successfully binded to port %d\n", portNumber); }
	}
	int receiveData() {
		sockaddr_in remoteAddr;
		int nAddrLen = sizeof(remoteAddr);
		int numberOfBytesRead = recvfrom(serSocket, dataBuffer, bufferLength, 0, (sockaddr *)&remoteAddr, &nAddrLen);
		if (numberOfBytesRead > 0)
		{
			dataBuffer[numberOfBytesRead] = 0x00;
			//printf("%s \r\n", inet_ntoa(remoteAddr.sin_addr));
			printf("%s\n", dataBuffer);
			return numberOfBytesRead;
		}
	}

	char* getDataBuffer() { return dataBuffer; }
	int getBufferLength() { return bufferLength; }

private:
	SOCKET serSocket;
	char* dataBuffer;
	int bufferLength;
};
