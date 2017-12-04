#include "stdafx.h"
#include "Obj.h"

CObj::CObj(void)
{
	ZeroMemory(&m_tInfo, sizeof(UNITINFO));
	ZeroMemory(m_szNickName, sizeof(MAX_PATH));
}

CObj::~CObj(void)
{
}

void CObj::Render(void)
{
	cout << "[´Ð³×ÀÓ] : " << m_szNickName << endl;
}

void CObj::Create_NickName(void)
{
	cin >> m_szNickName;
}
