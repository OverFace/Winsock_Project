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
	cout << "[�г���] : " << m_szNickName << endl;
}

void CObj::Create_NickName(void)
{
	cout << "    �г����� �Է��� �ּ���!!!" << endl;
	cout << "================================" << endl;
	cin >> m_szNickName;
}
