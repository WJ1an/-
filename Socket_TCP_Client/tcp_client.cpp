#include <winsock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	// 初始化
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		std::cout << "error:  WSAStartup() faile..." << std::endl;
		return -1;
	}

	// 设置服务器 socket
	SOCKET socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // IPV4
	if (socket_server == INVALID_SOCKET)
	{
		std::cout << "error: create socket fail." << std::endl;
		return -1;
	}

	// 设置服务器地址，本地地址为:127.0.0.1
	char adr_buf[20];
	std::cout << "Input server IP: ";
	std::cin >> adr_buf;
	SOCKADDR_IN addr_server;
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(3456);
	addr_server.sin_addr.S_un.S_addr = inet_addr(adr_buf);

	// 连接服务器
	if (connect(socket_server, (sockaddr*)&addr_server, sizeof(addr_server)) == SOCKET_ERROR)
	{
		std::cout << "error: connect fail." << std::endl;
		closesocket(socket_server);
		return -1;
	}

	char recv_buf[2048];
	std::string send_buf;

	std::cout << "Input message: ";
	std::cin.ignore();
	std::getline(std::cin, send_buf);

	// 发送消息
	send(socket_server, send_buf.c_str(), send_buf.size(), 0);

	// 接受来自服务器的消息
	int len = recv(socket_server, recv_buf, sizeof(recv_buf), 0);
	if (len > 0)
	{
		recv_buf[len] = '\0';
		std::cout << recv_buf << std::endl;
	}


	closesocket(socket_server);
	WSACleanup();

	return 0;
}
