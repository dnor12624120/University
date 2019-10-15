#include <iostream>
#include <string>
#include <vector>

#include "WNetwork.h"

std::string serverIP;
short serverPort;
int array1Size;
std::vector<int> array1;
int array2Size;
std::vector<int> array2;
int resultArraySize;
std::vector<int> resultArray;

void setupData(int argc, char** argv);

int main(int argc, char** argv)
{
	setupData(argc, argv);
	
	auto manager = WSAManager::GetInstance();

	Socket client(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	client.Connect(IPv4Address(serverIP, serverPort));
	
	client.Send(&array1Size, sizeof(int));
	client.Send(array1.data(), array1Size * sizeof(int));

	client.Send(&array2Size, sizeof(int));
	client.Send(array2.data(), array2Size * sizeof(int));

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
}