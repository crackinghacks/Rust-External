#pragma once
#include <windows.h>
#include <iostream>
#pragma comment(lib, "ws2_32.lib")




#pragma warning(disable: 4996)


class MYsocket
{
private:
	SOCKET connection = 0;
	u_short server_port;
	const char* server_ip;

public:
	MYsocket(u_short server_port, const char* server_addr) :server_port(server_port), server_ip(server_addr) {};

	bool MYconnect();
	bool MYdisconnect();


	size_t MYrecv_simple(unsigned char* buff, size_t buff_size);
	size_t MYsend_simple(char* buff, int len);

};