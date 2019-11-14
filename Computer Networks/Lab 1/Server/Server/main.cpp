#include <iostream>
#include <mutex>
#include <string>
#include <condition_variable>
#include <vector>
#include <queue>

#include "WNetwork.h"

struct Client
{
	Socket socket;
	IPv4Address address;
};

void handleClient();

const int BACKLOG = 8;
const std::string SERVER_IP = "127.0.0.1";
const unsigned short SERVER_PORT = 10111;
const int THREADPOOL_SIZE = std::thread::hardware_concurrency();

std::vector<std::thread> threadpool;
std::queue<Client> clients;
std::mutex clientQueueMutex;
std::condition_variable clientJoined;

int main()
{
	try
	{
		auto manager = WSAManager::GetInstance();
		Socket server{ AF_INET, SOCK_STREAM, IPPROTO_TCP };
		server.Bind(IPv4Address(SERVER_IP, SERVER_PORT));
		server.Listen(BACKLOG);
		
		for (int i = 0; i < THREADPOOL_SIZE; i++)
		{
			threadpool.emplace_back(std::thread(handleClient));
		}

		while (true)
		{
			Client client{ Socket{}, IPv4Address{} };
			server.Accept(client.socket, client.address);
			std::unique_lock<std::mutex> lock(clientQueueMutex);
			clients.push(std::move(client));
			lock.unlock();
			clientJoined.notify_one();
		}
	}
	catch (WinSockException& exception)
	{
		std::cout << exception.what() << '\n';
	}
	system("pause");
	return 0;
}

void handleClient()
{
	while (true)
	{
		std::unique_lock<std::mutex> lock(clientQueueMutex);
		clientJoined.wait(lock, []{ return !clients.empty(); });	
		Client client = std::move(clients.front());
		clients.pop();
		lock.unlock();
		int x;
		client.socket.Receive(&x, sizeof(int));
		std::cout << x << '\n';
	}
}