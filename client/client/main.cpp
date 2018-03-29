#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")


#define PORT "1080"
#define BUFFER 512
#define SERVER_PORT 27015
#define SET_BYTE(p,data) (*(char*)p = data)

int __cdecl main(int argc, char **argv)
{
	WSADATA wsaData;
	short int portNum = SERVER_PORT;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL, *p = NULL, x;

	char buffer[BUFFER] = { 0 };
	char receive_buf[BUFFER];
	char* pBuff;
	pBuff = buffer;
	int iResult;
	int recvbuflen = BUFFER;

	if (argc != 2) {
		printf("usage: %s server-name\n", argv[0]);
		return 1;
	}

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&x, sizeof(x));
	x.ai_family = AF_INET;
	x.ai_socktype = SOCK_STREAM;
	x.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo(argv[1], PORT, &x, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	for (p = result; p != NULL; p = p->ai_next) {
		ConnectSocket = socket(p->ai_family, p->ai_socktype,
			p->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		iResult = connect(ConnectSocket, p->ai_addr, (int)p->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}


	SET_BYTE(pBuff++, 5);
	printf("Socks protocol version %x\n", buffer[0]);
	SET_BYTE(pBuff++, 2);          
	printf("Supporting %x auth methods\n", buffer[1]);
	SET_BYTE(pBuff++, 0x00);
	printf("First ver method %x\n", buffer[2]);
	SET_BYTE(pBuff++, 0x02);
	printf("Second ver method %x\n", buffer[3]);
	iResult = send(ConnectSocket, buffer, 4, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("Bytes Sent: %ld\n", iResult);

	iResult = recv(ConnectSocket, receive_buf, 2, 0);
	if (iResult == SOCKET_ERROR) {
		printf("Recieve failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	unsigned char respCode = receive_buf[1];
	if ((receive_buf[0] != buffer[0]) || (respCode == 0xFF))
	{
		printf("Proxy response: %x %x\n", receive_buf[0], receive_buf[1]);
		printf("Wrong version of socks protocol or unsupported vrefication method \n");
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		return 1;
	}
	else {
		pBuff = buffer;
		char username[] = "Nemanja";
		printf("username: %s\n", username);
		char password[] = "roki94";
		printf("password: %s\n", password);
		char usernameLen = strlen(username);
		printf("usernameLen: %d\n", usernameLen);
		char passwordLen = strlen(password);
		printf("passwordLen: %d\n", passwordLen);
		SET_BYTE(pBuff++, 0x01);
		SET_BYTE(pBuff++, usernameLen);
		for (int i = 0; i<usernameLen; i++) {
			SET_BYTE(pBuff++, username[i]);
		}
		SET_BYTE(pBuff++, passwordLen);
		for (int i = 0; i<passwordLen; i++) {
			SET_BYTE(pBuff++, password[i]);
		}
		int packetLen = 3 + usernameLen + passwordLen;
		iResult = send(ConnectSocket, buffer, packetLen, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		printf("Bytes Sent: %ld\n", iResult);
	}

	
	iResult = recv(ConnectSocket, receive_buf, 2, 0);
	if (iResult == SOCKET_ERROR) {
		printf("Recieve failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	respCode = receive_buf[1];
	if (receive_buf[0] == buffer[0] && receive_buf[1] == 0x00){
		printf("Authentication successful \n");

	}else{
		printf("Authentication failed \n");
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
		return 1;
	}
	pBuff = buffer;
	
	SET_BYTE(pBuff++, 0x05); 
	SET_BYTE(pBuff++, 0x01); 
	SET_BYTE(pBuff++, 0x00); 
	SET_BYTE(pBuff++, 0x01); 
	SET_BYTE(pBuff++, 127); 
	SET_BYTE(pBuff++, 0);
	SET_BYTE(pBuff++, 0);
	SET_BYTE(pBuff++, 1);
	SET_BYTE(pBuff++, (portNum >> 8));
	printf(" FIRST_PART: %x \n", buffer[8]);
	SET_BYTE(pBuff++, (char)(portNum & 0xff));
	printf("SECOND_PART: %x\n", (buffer[9]));

	iResult = send(ConnectSocket, buffer, 10, 0);
	if (iResult == SOCKET_ERROR) {
		printf("send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	printf("Bytes Sent: %ld\n", iResult);

	iResult = recv(ConnectSocket, receive_buf, 10, 0);
	if (iResult == SOCKET_ERROR) {
		printf("Recieve failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	if (receive_buf[1] == 0x00)
	{
		printf("Connected to server \n");
		printf("Sending file: \n");
		FILE *file = NULL;
		size_t bytesRead = 0;


		if (file != NULL)
		{
			fseek(file, 0, SEEK_END);
			int len = ftell(file);
			rewind(file);
			printf("Size of file %d\n", len);
			buffer[0] = (len >> 24) & 0xff;
			buffer[1] = (len >> 16) & 0xff;
			buffer[2] = (len >> 8) & 0xff;
			buffer[3] = len & 0xff;

			iResult = send(ConnectSocket, buffer, 4, 0);
			if (iResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
				return 1;
			}
			while ((bytesRead = fread(buffer, 1, sizeof(buffer), file)) > 0){

				iResult = send(ConnectSocket, buffer, sizeof(buffer), 0);
				if (iResult == SOCKET_ERROR) {
					printf("send failed with error: %d\n", WSAGetLastError());
					closesocket(ConnectSocket);
					WSACleanup();
					return 1;
				}
				printf("Bytes Sent: %ld\n", iResult);
				iResult = recv(ConnectSocket, receive_buf, 1, 0);
				if (iResult == SOCKET_ERROR) {
					printf("recv failed with error: %d\n", WSAGetLastError());
					closesocket(ConnectSocket);
					WSACleanup();
					return 1;
				}
				printf("ACK received: %ld\n", iResult);
			}
		}else{ 
			printf("file error\n"); 
		}

	}else{
		printf("Connection to server failed \n");
		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
	}
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}
