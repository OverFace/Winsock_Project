// WinsockProjectServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"

int				m_iRetavl;					//Retval
WSADATA			m_wsaInfo;					//WSA Struct
SOCKET			m_Socket;					//Socket Struct
struct ip_mreq  m_Mreq;						//Struct ip_Mreq
SOCKADDR_IN		m_Local_Addr;				//SOCKADDR_IN Struct
SOCKADDR_IN		m_Peer_Addr;				//SOCKADDR_IN Struct
int				m_iLen;						//Buf Length
char			m_szBuf[BUFSIZE + 1];		//Data Container

void err_quit(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void err_display(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int main()
{
	CMainGame MainGame;
	MainGame.Init();
	
#pragma region Window Socket
	//Init Winsock
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaInfo) != 0)
		return 1;

	//Create Socket
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
		err_quit("socket()");

	//SO_REUSEADDR Option Setting
	BOOL bOptval = TRUE;
	m_iRetavl = setsockopt(m_Socket, SOL_SOCKET, SO_REUSEADDR, (char*)&bOptval, sizeof(bOptval));
	if (m_iRetavl == SOCKET_ERROR)
		err_quit("setsockopt()");

	//Bind
	ZeroMemory(&m_Local_Addr, sizeof(m_Local_Addr));
	m_Local_Addr.sin_family = AF_INET;
	m_Local_Addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_Local_Addr.sin_port = htons(PORTNUMBER);
	
	m_iRetavl = bind(m_Socket, (SOCKADDR*)&m_Local_Addr, sizeof(m_Local_Addr));
	if (m_iRetavl == SOCKET_ERROR)
		err_quit("bind()");

	//Multi Cast Group Add
	m_Mreq.imr_multiaddr.s_addr = inet_addr(MULTICASTIP);
	m_Mreq.imr_interface.s_addr = htonl(INADDR_ANY);
	
	m_iRetavl = setsockopt(m_Socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&m_Mreq, sizeof(m_Mreq));
	if (m_iRetavl == SOCKET_ERROR)
		err_quit("setsockopt()");
#pragma endregion

	while (true)
	{
		if (MainGame.Update() == 1)
		{
			MainGame.Release();
			break;
		}

		//Recv Data
		m_iLen = sizeof(m_Peer_Addr);
		m_iRetavl = recvfrom(m_Socket, m_szBuf, BUFSIZE, 0, (SOCKADDR*)&m_Peer_Addr, &m_iLen);
		if (m_iRetavl == SOCKET_ERROR)
		{
			err_display("recvfrom()");
			continue;
		}

		//Data Render
		m_szBuf[m_iRetavl] = '\0';
		cout << m_szBuf << endl;
	}

	//Multi Cast Member Drop
	m_iRetavl = setsockopt(m_Socket, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&m_Mreq, sizeof(m_Mreq));
	if (m_iRetavl == SOCKET_ERROR)
		err_quit("setsockopt()");

	//Close Socket
	closesocket(m_Socket);
	
	//Close Winsock
	WSACleanup();
    return 0;
}

