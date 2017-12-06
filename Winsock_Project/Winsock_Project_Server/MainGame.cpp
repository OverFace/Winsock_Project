#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "Moniter.h"

//Manager
#include "TimeMgr.h"

CMainGame::CMainGame(void)
{
	m_pMonitor = NULL;
	ZeroMemory(&m_Client_Addr, sizeof(m_Client_Addr));
}

CMainGame::~CMainGame(void)
{
	Release();
}

void CMainGame::Init(void)
{
	CTimeMgr::GetInstance()->InitTime();

	m_pMonitor = new CMoniter();
	m_pMonitor->Init();
}

int CMainGame::Update(void)
{
	CTimeMgr::GetInstance()->SetTime();

	//Monitor
	m_pMonitor->Update();
	m_pMonitor->Render();

	return 0;
}

void CMainGame::Release(void)
{
	CTimeMgr::GetInstance()->DestroyInstance();
	delete m_pMonitor;
}

int CMainGame::Data_Recv(SOCKET * pSocket, int iRetval)
{
	//Data Recv를 하는 함수.
	m_iAddr_Len = sizeof(m_Client_Addr);

	iRetval = recvfrom(*pSocket, m_szBuf, BUFSIZE, 0, (SOCKADDR*)&m_Client_Addr, &m_iAddr_Len);
	if (iRetval == SOCKET_ERROR)
	{
		cout << "Server : 받기 에러" << endl;
		return -1;
	}

	return iRetval;
}

void CMainGame::Data_Render(int iRetval)
{
	m_szBuf[iRetval] = '\0';
	printf("%s\n", m_szBuf);
}

int CMainGame::Data_Send(int iClient_Sock, int iRetval, char* pString)
{
	iRetval = send(iClient_Sock, pString, BUFSIZE, 0);
	if (iRetval == SOCKET_ERROR)
	{
		cout << "Server : 보내기 에러" << endl;
		return -1;
	}

	return iRetval;
}

void CMainGame::Listen_Client(SOCKET* pSocket, int iClient_Num)
{
	cout << "클라이언트를 기다립니다 " << MAX_CLIENT - iClient_Num << "남음" << endl;
	listen(*pSocket, 10);
}

int CMainGame::Client_Accept(SOCKET * pSocket)
{
	m_iAddr_Len = sizeof(m_Client_Addr);

	int iRetval = accept(*pSocket, (SOCKADDR*)&m_Client_Addr, &m_iAddr_Len);
	if (iRetval == SOCKET_ERROR)
		cout << "Accept 실패" << endl;

	return iRetval;
}

void CMainGame::Client_Accept_Render(int iSeat)
{
	Sleep(10);
	cout << iSeat << "번 클라이언트 접속" << endl;
}

void CMainGame::JobType_SendTo_Client(int iClient_Sock, int iSeat)
{
	eJobType* pArray = ((CMoniter*)m_pMonitor)->Get_JobArray();

	//직업 값 Client로 보내기
	int iType = int(pArray[iSeat]);
	itoa(iType, m_szBuf, 10);
	
	if (send(iClient_Sock, m_szBuf, BUFSIZE, 0) == SOCKET_ERROR)
	{
		cout << "직업 정보 보내기 실패" << endl;
	}
}

void CMainGame::GameState_SendTo_Client(int iClient_Sock, int iSeat)
{
	bool* bStateArray = ((CMoniter*)m_pMonitor)->Get_GameState();

	for (int i = 0; i < STATE_END; ++i)
	{
		switch (i)
		{
		case STATE_SELECT_JOB:
			if (bStateArray[i] == true)
			{
				JobType_SendTo_Client(iClient_Sock, iSeat);
			}
			break;
		case STATE_CLIENT_CHECK:
			if (bStateArray[i] == true)
			{
				eGameStateType eState = STATE_CLIENT_CHECK;
				int iState = int(eState);
				itoa(iState, m_szBuf, 10);

				if (send(iClient_Sock, m_szBuf, BUFSIZE, 0) == SOCKET_ERROR)
				{
					cout << "클라이언트 확인 상태 보내기 실패" << endl;
				}
			}
			break;
		case STATE_MAFIA_NIGHT:
			if (bStateArray[i] == true)
			{
				eGameStateType eState = STATE_MAFIA_NIGHT;
				int iState = int(eState);
				itoa(iState, m_szBuf, 10);

				if (send(iClient_Sock, m_szBuf, BUFSIZE, 0) == SOCKET_ERROR)
				{
					cout << "마피아의 밤 상태 보내기 실패" << endl;
				}
			}
			break;
		case STATE_DAYTIME:
			if (bStateArray[i] == true)
			{
				eGameStateType eState = STATE_DAYTIME;
				int iState = int(eState);
				itoa(iState, m_szBuf, 10);

				if (send(iClient_Sock, m_szBuf, BUFSIZE, 0) == SOCKET_ERROR)
				{
					cout << "낮 상태 보내기 실패" << endl;
				}
			}
			break;
		case STATE_POLICE_TIME:
			if (bStateArray[i] == true)
			{
				eGameStateType eState = STATE_POLICE_TIME;
				int iState = int(eState);
				itoa(iState, m_szBuf, 10);

				if (send(iClient_Sock, m_szBuf, BUFSIZE, 0) == SOCKET_ERROR)
				{
					cout << "경찰 시간 상태 보내기 실패" << endl;
				}
			}
			break;
		case STATE_DOCTOR_TIME:
			if (bStateArray[i] == true)
			{
				eGameStateType eState = STATE_DOCTOR_TIME;
				int iState = int(eState);
				itoa(iState, m_szBuf, 10);

				if (send(iClient_Sock, m_szBuf, BUFSIZE, 0) == SOCKET_ERROR)
				{
					cout << "의사 시간 상태 보내기 실패" << endl;
				}
			}
			break;
		}
	}
}
