#include "stdafx.h"
#include "Human.h"

CHuman::CHuman(void)
{
}

CHuman::~CHuman(void)
{
	Release();
}

void CHuman::Init(void)
{
	m_tInfo.eJobType = JOB_HUMAN;
	m_tInfo.iGet_Count = 0;
	m_tInfo.bCheck = false;
}

int CHuman::Update(void)
{
	return 0;
}

void CHuman::Render(void)
{
	CObj::Render();
	cout << "[Á÷  ¾÷] : " << "½Ã¹Î" << endl;
}

void CHuman::Release(void)
{
}
