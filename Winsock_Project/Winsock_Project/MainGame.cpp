#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"

//Manager
#include "TimeMgr.h"

//Player
#include "Doctor.h"
#include "Human.h"
#include "Mafia.h"
#include "Police.h"

CMainGame_Client::CMainGame_Client(void)
{
	m_eJobType = JOB_END;
	m_pPlayer = NULL;
	ZeroMemory(&m_Peer_Addr, sizeof(m_Peer_Addr));
}

CMainGame_Client::~CMainGame_Client(void)
{
	Release();
}

void CMainGame_Client::Init(void)
{
	CTimeMgr::GetInstance()->InitTime();

	switch (m_eJobType)
	{
	case JOB_HUMAN:
		m_pPlayer = new CHuman();
		break;
	case JOB_DOCTOR:
		m_pPlayer = new CDoctor();
		break;
	case JOB_MAFIA:
		m_pPlayer = new CMafia();
		break;
	case JOB_POLICE:
		m_pPlayer = new CPolice();
		break;
	}

	if (m_pPlayer != NULL)
	{
		m_pPlayer->Init();
		m_pPlayer->Create_NickName();
	}
}

int CMainGame_Client::Update(void)
{
	CTimeMgr::GetInstance()->SetTime();

	if (m_pPlayer != NULL)
	{
		m_pPlayer->Update();
	}

	return 0;
}

void CMainGame_Client::Render(void)
{
	Sleep(100);
	system("cls");
	cout << "==================================================================" << endl;
	cout << "||                         MAFIA GAME                           ||" << endl;
	cout << "==================================================================" << endl;
	if (m_pPlayer != NULL)
		m_pPlayer->Render();
	cout << "==================================================================" << endl;
}

void CMainGame_Client::Release(void)
{
	if (m_pPlayer != NULL)
		delete m_pPlayer;

	CTimeMgr::GetInstance()->DestroyInstance();
}

void CMainGame_Client::Data_Input(void)
{
	//Data Input Function
	cout << "보넬 데이터 : ";
	if (fgets(m_szBuf, BUFSIZE + 1, stdin) == NULL)
		return;
}

int CMainGame_Client::Data_Send(SOCKET * pSocket, SOCKADDR_IN* pServer_Addr, int iRetval)
{
	//'\n'문자 제거
	m_iLen = strlen(m_szBuf);
	if (m_szBuf[m_iLen - 1] == '\n')
		m_szBuf[m_iLen - 1] = '\0';

	if (strlen(m_szBuf) == 0)
		return -1;

	iRetval = sendto(*pSocket, m_szBuf, strlen(m_szBuf), 0, (SOCKADDR*)pServer_Addr, sizeof(*pServer_Addr));
	if (iRetval == SOCKET_ERROR)
	{
		cout << "Client : 보내기 에러 " << endl;
		return -1;
	}

	return iRetval;
}

int CMainGame_Client::Data_Recv(SOCKET* pSocket, SOCKADDR_IN* pServer_Addr, int iRetval)
{
	m_iAddr_Len = sizeof(m_Peer_Addr);

	iRetval = recvfrom(*pSocket, m_szBuf, BUFSIZE, 0, (SOCKADDR*)&m_Peer_Addr, &m_iAddr_Len);
	if (iRetval == SOCKET_ERROR)
	{
		cout << "Client : 받기 에러" << endl;
		return -1;
	}

	if (memcmp(&m_Peer_Addr, pServer_Addr, sizeof(m_Peer_Addr)))
	{
		cout << "잘못된 데이터 입니다." << endl;
		return -1;
	}

	return iRetval;
}

void CMainGame_Client::Data_Render(int iRetval)
{
	m_szBuf[iRetval] = '\0';
	printf("%s\n", m_szBuf);
}

