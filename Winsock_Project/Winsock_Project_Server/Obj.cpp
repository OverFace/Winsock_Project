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