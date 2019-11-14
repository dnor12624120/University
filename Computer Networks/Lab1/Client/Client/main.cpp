/*#include <iostream>
#include <string>
#include <vector>

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "WNetwork.h"

std::string serverIP = "192.168.0.133";
unsigned short serverPort = 10111;
int array1Size;
std::vector<int> array1{ 1, 2 };
int array2Size;
std::vector<int> array2{ 1, 2, 3 };
int resultArraySize;
std::vector<int> resultArray;

void setupData(int argc, char** argv);

int main(int argc, char** argv)
{
	//setupData(argc, argv);
	
	auto manager = WSAManager::GetInstance();

	Socket client(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	try
	{
		client.Connect(IPv4Address(serverIP, serverPort));

		client.Send(&array1Size, sizeof(int));
		client.Send(array1.data(), array1Size * sizeof(int));

		client.Send(&array2Size, sizeof(int));
		client.Send(array2.data(), array2Size * sizeof(int));
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << '\n';
	}
	return 0;
}

void setupData(int argc, char** argv)
{
	const int IP_INDEX = 1;
	const int PORT_INDEX = 2;
	const int ARRAY_1_SIZE_INDEX = 3;
	int ARRAY_2_SIZE_INDEX;

	serverIP = argv[IP_INDEX];
	serverPort = atoi(argv[PORT_INDEX]);

	array1Size = atoi(argv[ARRAY_1_SIZE_INDEX]);
	array1.resize(array1Size);
	ARRAY_2_SIZE_INDEX = ARRAY_1_SIZE_INDEX + array1Size + 1;

	for (int i = 0; i < array1.size(); i++)
	{
		array1[i] = atoi(argv[ARRAY_1_SIZE_INDEX + 1 + i]);
	}

	array2Size = atoi(argv[ARRAY_2_SIZE_INDEX]);
	array2.resize(array2Size);

	for (int i = 0; i < array2.size(); i++)
	{
		array2[i] = atoi(argv[ARRAY_2_SIZE_INDEX + 1 + i]);
	}
}*/


#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>

int main()
{
	WSADATA data;
	if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
	{
		return -1;
	}
	sockaddr_in server;
	SOCKET c = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	server.sin_port = htons(10111);
	server.sin_family = AF_INET;
	inet_pton(AF_INET, "192.168.0.133", &server.sin_addr.S_un.S_addr);
	
	if (connect(c, (sockaddr*)&server, sizeof(sockaddr)) != 0)
	{
		std::cout << WSAGetLastError() << '\n';
	}

	int x = 123;
	send(c, (const char*)&x, sizeof(int), 0);
	closesocket(c);
	WSACleanup();
	system("pause");
}