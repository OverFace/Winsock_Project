// WinsockProjectServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"

//Socket Create Variable
int				m_iRetavl;							//Retval
WSADATA			m_wsaInfo;							//WSA Struct
SOCKET			m_Socket;							//Socket Struct
SOCKADDR_IN		m_Server_Addr;						//SOCKADDR_IN Struct

//Multiple Variable
int				m_iClient_Num = 0;					//Client 인원
int				m_iSeat = 0;						//Client 번호
int				m_iClient_Sock[ALLOW];				//Client Socket
char			m_szWelecom_Ok[] = "님 환영합니다.\n\0";
char			m_szWelecom_Full[] = "가득찼습니다.\n";

//Thread 
HANDLE			m_hMutex = 0;
void			recv_client(void* ns);

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
#pragma region Window Socket
	//Create Mutex
	m_hMutex = CreateMutex(NULL, FALSE, NULL);
	if (!m_hMutex)
		return 1;

	//Init Winsock
	if (WSAStartup(MAKEWORD(2, 2), &m_wsaInfo) != 0)
		return 1;

	//Create Socket
	m_Socket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_Socket == INVALID_SOCKET)
		err_quit("socket()");

	//Init Addr Struct
	ZeroMemory(&m_Server_Addr, sizeof(m_Server_Addr));
	m_Server_Addr.sin_family = AF_INET;
	m_Server_Addr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_Server_Addr.sin_port = htons(PORTNUMBER);

	//Bind
	m_iRetavl = bind(m_Socket, (SOCKADDR*)&m_Server_Addr, sizeof(m_Server_Addr));
	if (m_iRetavl == SOCKET_ERROR)
		err_quit("bind()");

	CMainGame MainGame;
	MainGame.Init();
	
	//Listen
	MainGame.Listen_Client(&m_Socket, m_iClient_Num);
#pragma endregion

	while (true)
	{
		if (MainGame.Update() == 1)
		{
			MainGame.Release();
			break;
		}

		//Client 기다린다.
		m_iClient_Sock[m_iSeat] = MainGame.Client_Accept(&m_Socket);

		if (m_iClient_Num < MAX_CLIENT)
		{
			//정상적인 접속
			if (m_iClient_Sock[m_iSeat] != INVALID_SOCKET)
			{	
				MainGame.Client_Accept_Render(m_iSeat);

				//이 함수가 여기 있어서 제대로 작동하는지 확인 해야 된다.
				MainGame.GameState_SendTo_Client(m_iClient_Sock[m_iSeat], m_iSeat);
				
				//Thread
				_beginthread(recv_client, 0, &m_iClient_Sock[m_iSeat]);
			}
		}
		else
		{
			//가득 참.
			if (m_iClient_Sock[m_iSeat] == INVALID_SOCKET)
			{
				closesocket(m_iClient_Sock[m_iSeat]);
				closesocket(m_Socket);
				WSACleanup();
				return 1;
			}

			m_iRetavl = MainGame.Data_Send(m_iClient_Sock[m_iSeat], m_iRetavl, m_szWelecom_Full);
			closesocket(m_iClient_Sock[m_iSeat]);
		}

		//Main Game을 통해서 Data Recv
		//m_iRetavl = MainGame.Data_Recv(&m_Socket, m_iRetavl);

		//Data Render
		//MainGame.Data_Render(m_iRetavl);

		//Send Data
		//char szMsg[BUFSIZE + 1];
		//MainGame.Data_Send(&m_Socket, m_iRetavl, m_szWelecom_Full);
	}

	//Close Socket
	closesocket(m_Socket);
	
	//Close Winsock
	WSACleanup();
    return 0;
}

void recv_client(void* ns)
{
	//정상적으로 받아 들일때 스레드 실행.
	//클라이언트 숫자를 늘림.

	WaitForSingleObject(m_hMutex, INFINITE);
	++m_iClient_Num;
	++m_iSeat;
	ReleaseMutex(m_hMutex);

	char welecom[100] = { 0 };
	char buff[BUFSIZE] = { 0 };
	int  retval;

	itoa(m_iSeat, welecom, 10);
	strcat(welecom, m_szWelecom_Ok);
	retval = send(*(SOCKET*)ns, welecom, sizeof(welecom), 0);

	while (retval != SOCKET_ERROR || retval != INVALID_SOCKET)
	{
		retval = recv(*(SOCKET*)ns, buff, BUFSIZE, 0);

		//Broad Cast
		for (int i = 0; i < ALLOW; ++i)
		{
			WaitForSingleObject(m_hMutex, INFINITE);
			if((unsigned*)&m_iClient_Sock[i] != (SOCKET*)ns)
			{
				send(m_iClient_Sock[i], buff, strlen(buff), 0);
			}
			ReleaseMutex(m_hMutex);
		}

		memset(buff, 0, BUFSIZE);
	}

	WaitForSingleObject(m_hMutex, INFINITE);
	--m_iClient_Num;
	ReleaseMutex(m_hMutex);
	closesocket(*(int*)ns);
	return;
}

