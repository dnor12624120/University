#pragma once

#if defined(WIN32) || defined(_WIN32)
	#include <WS2tcpip.h>
#endif
	
#if defined(SetPort)
	#undef SetPort
#endif

class SocketAddress
{
	public:
		SocketAddress() = default;

		SocketAddress(unsigned short familyType, unsigned short port, unsigned long address)
		{
			m_address.sin_family = familyType;
			m_address.sin_port = port;
			m_address.sin_addr.S_un.S_addr = address;
		}

		inline unsigned short GetFamilyType() const { return m_address.sin_family; }
		inline unsigned short& GetPort() { return m_address.sin_port; }
		inline unsigned long& GetAddress() { return m_address.sin_addr.S_un.S_addr; }
		inline const sockaddr_in& GetStructure() const { return m_address; }

		inline void SetFamily(unsigned short familyType) { m_address.sin_family = familyType; }
		inline void SetPort(unsigned short port) { m_address.sin_port = port; }
		inline void SetAddress(unsigned long address) { m_address.sin_addr.S_un.S_addr; }
	private:
		sockaddr_in m_address;
};