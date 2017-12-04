#include "stdafx.h"
#include "Police.h"

CPolice::CPolice(void)
{
}

CPolice::~CPolice(void)
{
	Release();
}

void CPolice::Init(void)
{
	m_tInfo.eJobType = JOB_POLICE;
	m_tInfo.iGet_Count = 0;
	m_tInfo.bCheck = false;
}

int CPolice::Update(void)
{
	return 0;
}

void CPolice::Render(void)
{
	CObj::Render();
}

void CPolice::Release(void)
{
}
