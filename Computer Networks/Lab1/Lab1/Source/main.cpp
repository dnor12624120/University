#include <iostream>
#include "WNetwork.h"

int main()
{
	try
	{
		auto manager = WSAManager::GetInstance();
		Socket socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		socket.Connect(IPv4Address("127.0.0.1", 10111));
		int x = 123;
		socket.Send(&x, sizeof(int));
	}
	catch (WinSockException& exception)
	{
		std::cout << exception.what() << '\n';
	}
	system("pause");
}