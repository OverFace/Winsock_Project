#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"
#include "Moniter.h"

//Manager
#include "TimeMgr.h"

CMainGame::CMainGame(void)
{
	m_pMonitor = NULL;
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
	m_pMonitor->Update();
	m_pMonitor->Render();

	return 0;
}

void CMainGame::Release(void)
{
	CTimeMgr::GetInstance()->DestroyInstance();
	delete m_pMonitor;
}
