#include <winsock2.h>
#include <iostream>
#include <string>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	// ��ʼ��
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		std::cout << "error:  WSAStartup() faile." << std::endl;
		return -1;
	}

	// ���÷����� socket
	SOCKET socket_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // IPV4
	if (socket_server == INVALID_SOCKET)
	{
		std::cout << "error: create socket fail." << std::endl;
		return -1;
	}

	// ���÷������˵�ַ
	SOCKADDR_IN addr_server;
	addr_server.sin_family = AF_INET;
	addr_server.sin_port = htons(3456);
	addr_server.sin_addr.S_un.S_addr = INADDR_ANY;

	// �󶨵�socket��
	if (bind(socket_server, (LPSOCKADDR)&addr_server, sizeof(addr_server)) == SOCKET_ERROR)
	{
		std::cout << "error: bind server fail." << std::endl;
	}

	if (listen(socket_server, 5) == SOCKET_ERROR)
	{
		std::cout << "error: server listen fail." << std::endl;
		return -1;
	}

	char recv_buf[2048];
	std::string send_buf;

	SOCKADDR_IN addr_client;
	int addr_len = sizeof(addr_client);
	while (true)
	{
		std::cout << "waiting for connection" << std::endl;
		// �������Կͻ�������
		SOCKET socket_client = accept(socket_server, (SOCKADDR*)&addr_client, &addr_len);

		if (socket_client == INVALID_SOCKET)
		{
			std::cout << "error: accept fail." << std::endl;
			continue;
		}
		//���ӿͻ��˳ɹ�
		std::cout << "Accepted client IP: " << inet_ntoa(addr_client.sin_addr) << ":" << addr_client.sin_port << std::endl;

		// ���ܿͻ�����Ϣ
		int len = recv(socket_client, recv_buf, sizeof(recv_buf), 0);
		if (len > 0)
		{
			recv_buf[len] = '\0';
			std::cout << recv_buf << std::endl;
		}

		// ��ͻ��˷�����Ϣ
		send_buf = "Hello client, this is TCP server.";
		send(socket_client, send_buf.c_str(), send_buf.size(), 0);
		closesocket(socket_client);
	}

	closesocket(socket_server);
	WSACleanup();

	return 0;
}
