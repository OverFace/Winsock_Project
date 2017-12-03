#include "stdafx.h"
#include "MainGame.h"
#include "Obj.h"

typedef list<CObj*>::iterator OBJITER;

CMainGame_Client::CMainGame_Client(void)
{
}

CMainGame_Client::~CMainGame_Client(void)
{
	Release();
}

void CMainGame_Client::Init(void)
{

}

int CMainGame_Client::Update(void)
{
	OBJITER iter = m_Client_List.begin();
	OBJITER iter_End = m_Client_List.end();

	for (iter; iter != iter_End; ++iter)
	{
		(*iter)->Update();
	}
	
	return 0;
}

void CMainGame_Client::Render(void)
{
	OBJITER iter = m_Client_List.begin();
	OBJITER iter_End = m_Client_List.end();

	for (iter; iter != iter_End; ++iter)
	{
		(*iter)->Render();
	}
}

void CMainGame_Client::Release(void)
{
	OBJITER iter = m_Client_List.begin();
	OBJITER iter_End = m_Client_List.end();

	for (iter; iter != iter_End; ++iter)
	{
		(*iter)->Release();
	}
}
