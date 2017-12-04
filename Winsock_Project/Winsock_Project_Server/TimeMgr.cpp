#include "StdAfx.h"
#include "TimeMgr.h"

IMPLEMENT_SINGLETON(CTimeMgr)

CTimeMgr::CTimeMgr(void)
{
}

CTimeMgr::~CTimeMgr(void)
{
}

float CTimeMgr::GetTime(void)
{
	return m_fTime;
}

void CTimeMgr::InitTime(void)
{
	QueryPerformanceCounter(&m_FrameTime);	//���κ��� Ÿ�̸Ӹ� ����ϱ� ���ؼ� ȣ���Ѵ�..
	QueryPerformanceCounter(&m_FixTime);	//Ÿ�̸��� ���� ���� ��� ��...1/10000 ����
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTick);	//Ÿ�̸��� �ֱ�(1�ʴ� ������)
}

void CTimeMgr::SetTime(void)
{
	//ȣ���� �� ������ ���ο� �ð��� ���Ѵ�..
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		//cpu ƽ�� ���� ����..
		QueryPerformanceFrequency(&m_CpuTick);
		//���� �����ؼ� lasttime �� �ٲ۴�..
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}
