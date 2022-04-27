#include "socket.h"


bool MYsocket::MYconnect()
{

	WSADATA wsa_data;
	if (WSAStartup(MAKEWORD(2, 2), &wsa_data))
	{
		return 0;
	}

	SOCKADDR_IN address{ };

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(server_ip);
	address.sin_port = htons(server_port);

	connection = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);


	int time = 10000;
	setsockopt(connection, SOL_SOCKET,SO_RCVTIMEO,(char*) &time, sizeof(time));

	if (connection == INVALID_SOCKET)
	{
		WSACleanup();
		return 0;
	}

	if (connect(connection, (SOCKADDR*)&address, sizeof(address)) == SOCKET_ERROR)
	{
		WSACleanup();
		closesocket(connection);
		return 0;
	}
	return 1;
}

bool MYsocket::MYdisconnect()
{
	return !WSACleanup() && !closesocket(connection);
}


size_t MYsocket::MYrecv_simple(unsigned char* buff, size_t buff_size)
{
	return recv(connection,(char*)buff, buff_size, 0);
}

size_t MYsocket::MYsend_simple(char* buff, int len)
{
	if (connection != NULL)return send(connection, buff, len, 0);
	else return 0;
}