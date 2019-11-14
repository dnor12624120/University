#include <iostream>
#include "WNetwork.h"

int main()
{
	try
	{
		WSADATA data;

		if (WSAStartup(MAKEWORD(2, 2), &data) != 0)
		{
			throw 1;
		}

		SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
		sockaddr_in a;
		inet_pton(AF_INET, "192.168.0.133", &a.sin_addr.S_un.S_addr);
		a.sin_family = AF_INET;
		a.sin_port = htons(10111);

		if (connect(s, (sockaddr*)&a, sizeof(sockaddr)) != 0)
		{
			throw 1;
		}
		
		int x;
		std::cin >> x;

		if (send(s, (char*)&x, sizeof(int), 0) == 0)
		{
			std::cout << "bai\n";
		}
	}
	catch (...)
	{
		std::cout << WSAGetLastError() << '\n';
	}

	system("pause");
	return 0;
}