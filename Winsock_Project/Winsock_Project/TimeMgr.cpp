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
	QueryPerformanceCounter(&m_FrameTime);	//메인보드 타이머를 사용하기 위해서 호출한다..
	QueryPerformanceCounter(&m_FixTime);	//타이머의 현재 값을 얻는 것...1/10000 단위
	QueryPerformanceCounter(&m_LastTime);
	QueryPerformanceFrequency(&m_CpuTick);	//타이머의 주기(1초당 진동수)
}

void CTimeMgr::SetTime(void)
{
	//호출이 될 때마다 새로운 시간을 구한다..
	QueryPerformanceCounter(&m_FrameTime);

	if (m_FrameTime.QuadPart - m_LastTime.QuadPart > m_CpuTick.QuadPart)
	{
		//cpu 틱을 새로 갱신..
		QueryPerformanceFrequency(&m_CpuTick);
		//새로 갱신해서 lasttime 도 바꾼다..
		m_LastTime.QuadPart = m_FrameTime.QuadPart;
	}

	m_fTime = float(m_FrameTime.QuadPart - m_FixTime.QuadPart) / m_CpuTick.QuadPart;

	m_FixTime = m_FrameTime;
}
