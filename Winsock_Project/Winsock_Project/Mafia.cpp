#include "stdafx.h"
#include "Mafia.h"

CMafia::CMafia(void)
{
}

CMafia::~CMafia(void)
{
	Release();
}

void CMafia::Init(void)
{
	m_tInfo.eJobType = JOB_MAFIA;
	m_tInfo.iGet_Count = 0;
	m_tInfo.bCheck = false;
}

int CMafia::Update(void)
{
	return 0;
}

void CMafia::Render(void)
{
	CObj::Render();
}

void CMafia::Release(void)
{
}
