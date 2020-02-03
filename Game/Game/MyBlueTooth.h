#pragma once
#include <Siv3D.hpp>
#include <WinSock2.h>
#include <ws2bth.h>
#include "MyBlueToothLib.h"

class MyBlueTooth {
private:
	static MyBlueToothLib* lib;

public:
	MyBlueTooth() = delete;

	static void initialize() {
		lib = new MyBlueToothLib();
	}
	static void finalize() {
		delete lib;
	}

	static bool test()
	{
		WSAData wsaData = { 0 };
		WSAStartup(MAKEWORD(2, 2), &wsaData);

		SOCKET listen_sock = socket(AF_BTH, SOCK_STREAM, BTHPROTO_RFCOMM);
		if (listen_sock == INVALID_SOCKET) {
			return false;
		}

		SOCKADDR_BTH sa = { 0 };
		sa.addressFamily = AF_BTH;
		sa.port = BT_PORT_ANY;

		if (bind(listen_sock, (SOCKADDR*)&sa, sizeof(sa)) == SOCKET_ERROR) {
			return false;
		}

		int size = sizeof(sa);
		getsockname(listen_sock, (SOCKADDR*)&sa, &size);

		CSADDR_INFO info = { 0 };
		info.LocalAddr.lpSockaddr = (LPSOCKADDR)&sa;
		info.LocalAddr.iSockaddrLength = sizeof(sa);
		info.iSocketType = SOCK_STREAM;
		info.iProtocol = BTHPROTO_RFCOMM;

		WSAQUERYSET set = { 0 };
		set.dwSize = sizeof(WSAQUERYSET);                              // Must be set to sizeof(WSAQUERYSET)
		set.dwOutputFlags = 0;                                         // Not used
		set.lpszServiceInstanceName = (LPWSTR)"Server";                        // Recommended.
		set.lpServiceClassId = (LPGUID)&SerialPortServiceClass_UUID;   // Requred.
		set.lpVersion = NULL;                                          // Not used.
		set.lpszComment = NULL;                                        // Optional.
		set.dwNameSpace = NS_BTH;                                      // Must be NS_BTH.
		set.lpNSProviderId = NULL;                                     // Not required.
		set.lpszContext = NULL;                                        // Not used.
		set.dwNumberOfProtocols = 0;                                   // Not used.
		set.lpafpProtocols = NULL;                                     // Not used.
		set.lpszQueryString = NULL;                                    // not used.
		set.dwNumberOfCsAddrs = 1;                                     // Must be 1.
		set.lpcsaBuffer = &info;                                       // Pointer to a CSADDR_INFO.
		set.lpBlob = NULL;                                             // Optional.

		if (WSASetService(&set, RNRSERVICE_REGISTER, 0) != 0) {
			return false;
		}

		listen(listen_sock, 0);

		SOCKADDR_BTH sab2;
		int ilen = sizeof(sab2);
		SOCKET socket = accept(listen_sock, (SOCKADDR*)&sab2, &ilen);

		char buf[1024] = { 0 };
		int res = recv(socket, buf, sizeof(buf), 0);

		if (res > 0) {
			std::cout << buf << std::endl;
		}

		closesocket(listen_sock);
		closesocket(socket);

		WSACleanup();
	}
};