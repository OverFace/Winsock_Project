#include "stdafx.h"
#include "Doctor.h"

CDoctor::CDoctor(void)
{
}

CDoctor::~CDoctor(void)
{
	Release();
}

void CDoctor::Init(void)
{
	m_tInfo.eJobType = JOB_DOCTOR;
	m_tInfo.iGet_Count = 0;
	m_tInfo.bCheck = false;
}

int CDoctor::Update(void)
{
	return 0;
}

void CDoctor::Render(void)
{
	CObj::Render();
}

void CDoctor::Release(void)
{
}
