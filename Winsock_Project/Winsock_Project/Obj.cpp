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
	cout << "[닉네임] : " << m_szNickName << endl;
}

void CObj::Create_NickName(void)
{
	cout << "    닉네임을 입력해 주세요!!!" << endl;
	cout << "================================" << endl;
	cin >> m_szNickName;
}
