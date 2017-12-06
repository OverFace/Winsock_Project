// WinsockProject.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"

int			m_iRetavl;					//Retval
WSADATA		m_wsaInfo;					//WSA Struct
SOCKET		m_Socket;					//Socket Struct
SOCKADDR_IN m_Server_Addr;				//SOCKADDR_IN Struct
char		m_szBuf[BUFSIZE + 1];

//Thread
void		recv_thread(void*);
HANDLE		m_hMutex;

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

int recvn(SOCKET s, char* buf, int len, int flags)
{
	int received;
	char* ptr = buf;
	int left = len;

	while (left > 0)
	{
		received = recv(s, ptr, left, flags);
		if (received == SOCKET_ERROR)
		{
			return SOCKET_ERROR;
		}
		else if (received == 0)
		{
			break;
		}

		left -= received;
		ptr += received;
	}
}

int main(void)
{
#pragma region Window Socket
	//Create Mutex
	m_hMutex = CreateMutex(NULL, FALSE, FALSE);
	if (!m_hMutex)
		return 1;

	//Init Winsock
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaInfo) != 0)
		return 1;

	//Create Socket
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket == INVALID_SOCKET)
		err_quit("socket()");

	//Init Socket Address Struct
	ZeroMemory(&m_Server_Addr, sizeof(m_Server_Addr));
	m_Server_Addr.sin_family = AF_INET;
	m_Server_Addr.sin_addr.s_addr = inet_addr(SERVERIP);
	m_Server_Addr.sin_port = htons(PORTNUMBER);
#pragma endregion

	//Connect
	if (connect(m_Socket, (SOCKADDR*)&m_Server_Addr, sizeof(m_Server_Addr)) == SOCKET_ERROR)
	{
		closesocket(m_Socket);
		WSACleanup();
		return 1;
	}
	
	CMainGame_Client MainGame;
	int	ijobType;

	m_iRetavl = recvn(m_Socket, m_szBuf, BUFSIZE, 0);
	
	if (!strcmp("가득찼습니다.\n", m_szBuf))
	{
		printf("%s", "I'm sorry. The room is full\n");
		closesocket(m_Socket);
		WSACleanup();
		return 0;
	}

	//Main Game Allocate
	ijobType = atoi(m_szBuf);
	MainGame.Set_JobType(eJobType(ijobType));
	MainGame.Init();

	//Thread
	//_beginthread(recv_thread, 0, NULL);

	//채팅방 보내는 메세지는 스레드로 넣을 필요 없고 MainGame에서
	//낮일때 돌려주자.

	while (true)
	{
		//MainGame Update
		if (MainGame.Update() == 1)
		{
			MainGame.Release();
			break;
		}
		MainGame.Render();

		//서버에서 받은 게임 상태 값에 따른 게임 진행을 이제 짜야 된다.

		//Data Input
		//MainGame.Data_Input();

		//Data Send
		//m_iRetavl = MainGame.Data_Send(&m_Socket, &m_Server_Addr, m_iRetavl);

		//Data Recv
		//m_iRetavl = MainGame.Data_Recv(&m_Socket, &m_Server_Addr, m_iRetavl);

		//Data Render
		//MainGame.Data_Render(m_iRetavl);
	}

	//Close Socket
	closesocket(m_Socket);

	//Close WinSock
	WSACleanup();
	return 0;
}

void recv_thread(void* pData)
{
	int iRetval_Thread = 65535;
	char buff_Thread[BUFSIZE] = { 0 };

	while (iRetval_Thread != INVALID_SOCKET || iRetval_Thread != SOCKET_ERROR)
	{
		Sleep(10);

		iRetval_Thread = recv(m_Socket, buff_Thread, sizeof(buff_Thread), 0);

		if (iRetval_Thread == INVALID_SOCKET || iRetval_Thread == SOCKET_ERROR)
			break;

		memset(buff_Thread, 0, BUFSIZE);
	}

	WaitForSingleObject(m_hMutex, 100L);
	m_iRetavl = INVALID_SOCKET;
	ReleaseMutex(m_hMutex);

	return;
}

