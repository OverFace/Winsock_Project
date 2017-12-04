#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"

//Player
#include "Doctor.h"
#include "Human.h"
#include "Mafia.h"
#include "Police.h"

CMainGame_Client::CMainGame_Client(void)
{
	m_eJobType = JOB_END;
	m_pPlayer = NULL;
}

CMainGame_Client::~CMainGame_Client(void)
{
	Release();
}

void CMainGame_Client::Init(void)
{
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
	Render();

	if (m_pPlayer != NULL)
	{
		m_pPlayer->Update();
	}

	return 0;
}

void CMainGame_Client::Render(void)
{
	system("cls");
	cout << "==========================================" << endl;
	cout << "||              MAFIA GAME              ||" << endl;
	cout << "==========================================" << endl;
	if (m_pPlayer != NULL)
		m_pPlayer->Render();
	cout << "==========================================" << endl;
}

void CMainGame_Client::Release(void)
{
	if (m_pPlayer != NULL)
		delete m_pPlayer;
}
