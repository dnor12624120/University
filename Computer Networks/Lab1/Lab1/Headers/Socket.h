#pragma once

#include "WinSockException.h"
#include "IPv4Address.h"

#if defined(WIN32) || defined(_WIN32)
	#include <WinSock2.h>
#endif

class Socket
{
	public:
		Socket() = default;
		Socket(unsigned short family, int type, int protocol) :
			m_family{ family },
			m_type{ type },
			m_protocol{ protocol }
		{			
			m_handle = socket(m_family, m_type, m_protocol);
			if (m_handle == INVALID_SOCKET)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error creating socket! (" + errorCode + ")").c_str());
			}
		}

		Socket(SOCKET handle, unsigned short family, int type, int protocol) :
			m_handle{ handle },
			m_family{ family },
			m_type{ type },
			m_protocol{ protocol }
		{
		
		}

		Socket(const Socket& socket) = delete;
		Socket& operator=(const Socket& socket) = delete;

		Socket(Socket&& socket) :
			m_handle{ socket.m_handle },
			m_family{ socket.m_family },
			m_type{ socket.m_type },
			m_protocol{ socket.m_protocol }
		{
			socket.m_handle = INVALID_SOCKET;
		}

		Socket& operator=(Socket&& socket)
		{
			m_handle = socket.m_handle;
			m_family = socket.m_family;
			m_type = socket.m_type;
			m_protocol = socket.m_protocol;
			socket.m_handle = INVALID_SOCKET;
		}

		~Socket()
		{
			if (m_handle == INVALID_SOCKET)
			{
				throw WinSockException("Trying to close an invalid socket!");
			}
			if (closesocket(m_handle) == SOCKET_ERROR)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error closing socket! (" + errorCode + ")").c_str());
			}
		}

		void Bind(const IPv4Address& address)
		{
			if (bind(m_handle, (sockaddr*)&address.GetSocketAddress().GetStructure(), sizeof(sockaddr)) != 0)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error binding socket! (" + errorCode + ")").c_str());
			}
		}

		void Listen(int backlog)
		{
			if (listen(m_handle, backlog) != 0)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error trying to listen to incoming connections! (" + errorCode + ")").c_str());
			}
		}


		void Accept(Socket& clientSocket, IPv4Address& clientAddress)
		{
			sockaddr_in address;
			int addressSize = sizeof(sockaddr_in);
			SOCKET clientHandle = accept(m_handle, (sockaddr*)&address, &addressSize);
			if (clientHandle == INVALID_SOCKET)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error accepting connection! (" + errorCode + ")").c_str());
			}
			clientAddress = SocketAddress(address.sin_family, address.sin_port, address.sin_addr.S_un.S_addr);
			clientSocket = Socket(clientHandle, AF_INET, SOCK_STREAM, IPPROTO_TCP);
		}

		void Connect(const IPv4Address& address)
		{
			auto structure = address.GetSocketAddress().GetStructure();
			int result = connect(m_handle, (sockaddr*)&structure, sizeof(sockaddr));
			if (result != 0)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error accepting connection! (" + errorCode + ")").c_str());
			}
		}

		void Send(const void* data, int size)
		{
			int currentSize{ 0 };
			while (currentSize < size)
			{
				int sentBytes = SendImplementation((const char*)data + currentSize, size - currentSize);
				currentSize += sentBytes;
			}
		}

		void Receive(void* data, int size)
		{
			int currentSize{ 0 };
			while (currentSize != size)
			{
				int receivedBytes = ReceiveImplementation((char*)data + currentSize, size - currentSize);
				currentSize += receivedBytes;
				if (currentSize == 0)
				{
					throw WinSockException("Client disconnected!\n");
				}
			}
		}

		void ReceiveAll(void* data, int& size)
		{
			int currentSize{ 0 };
			int receivedBytes{ 0 };
			do
			{
				receivedBytes = ReceiveImplementation((char*)data + currentSize, Socket::DefaultReceiveSize);
				currentSize += receivedBytes;
			}
			while (receivedBytes != 0);
			size = currentSize;
		}
	private:
		int SendImplementation(const void* data, int size)
		{
			int bytesSent = send(m_handle, (const char*)data, size, 0);
			if (bytesSent == SOCKET_ERROR)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error sending data! (" + errorCode + ")").c_str());
			}
			return bytesSent;
		}

		int ReceiveImplementation(void* data, int size)
		{
			int bytesSent = recv(m_handle, (char*)data, size, 0);
			if (bytesSent == SOCKET_ERROR)
			{
				std::string errorCode(std::to_string(WSAGetLastError()));
				throw WinSockException(std::string("Error recieving data! (" + errorCode + ")").c_str());
			}
			return bytesSent;
		}

		SOCKET m_handle;
		int m_family;
		int m_type;
		int m_protocol;
		static const int DefaultReceiveSize{ 128 };
};