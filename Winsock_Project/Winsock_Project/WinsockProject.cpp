// WinsockProject.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"

int			m_iRetavl;					//Retval
WSADATA		m_wsaInfo;					//WSA Struct
SOCKET		m_Socket;					//Socket Struct
SOCKADDR_IN m_Remote_Addr;				//SOCKADDR_IN Struct
char		m_szBuf[BUFSIZE + 1];		//Data Container
int			m_iLen;						//Buf Length

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

int main(void)
{
	//Main Game Allocate
	CMainGame_Client MainGame;
	MainGame.Set_JobType(JOB_MAFIA);
	MainGame.Init();

#pragma region Window Socket
	//Init Winsock
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaInfo) != 0)
		return 1;

	//Create Socket
	m_Socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_Socket == INVALID_SOCKET)
		err_quit("socket()");

	//Setting Multi Cast TLL
	int ttl = 2;
	m_iRetavl = setsockopt(m_Socket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&ttl, sizeof(ttl));
	if (m_iRetavl == SOCKET_ERROR)
		err_quit("setsockopt()");

	//Init Socket Address Struct
	ZeroMemory(&m_Remote_Addr, sizeof(m_Remote_Addr));
	m_Remote_Addr.sin_family = AF_INET;
	m_Remote_Addr.sin_addr.s_addr = inet_addr(MULTICASTIP);
	m_Remote_Addr.sin_port = htons(PORTNUMBER);
#pragma endregion

	while (true)
	{
		//MainGame Update
		if (MainGame.Update() == 1)
		{
			MainGame.Release();
			break;
		}
		MainGame.Render();

		//임시로 교제에 있는 그대로 데이터 통신을 하게 한다.
		//Data Input
		cout << "보낼 데이터 : ";
		cin >> m_szBuf;
		if (m_szBuf == NULL)
			break;

		//'\n' 문자 제거
		m_iLen = strlen(m_szBuf);
		if (m_szBuf[m_iLen - 1] == '\n')
			m_szBuf[m_iLen - 1] = '\0';
		if (strlen(m_szBuf) == 0)
			break;

		//Send Data
		m_iRetavl = sendto(m_Socket, m_szBuf, strlen(m_szBuf), 0, (SOCKADDR*)&m_Remote_Addr, sizeof(m_Remote_Addr));
		if (m_iRetavl == SOCKET_ERROR)
		{
			err_display("sendto()");
			continue;
		}
	}

	//Close Socket
	closesocket(m_Socket);

	//Close WinSock
	WSACleanup();
	return 0;
}


