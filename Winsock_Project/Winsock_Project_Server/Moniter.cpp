#include "stdafx.h"
#include "Moniter.h"
#include "TimeMgr.h"

CMoniter::CMoniter(void)
{
	m_pJob_Array = new eJobType[10];
	for (int i = 0; i < 10; ++i)
		m_pJob_Array[i] = JOB_END;

	for (int i = 0; i < STATE_END; ++i)
		m_bGame_StateCheck[i] = false;

	m_iRandom = 0;
	m_fTime = 0.f;
}

CMoniter::~CMoniter(void)
{
	Release();
}

void CMoniter::Init(void)
{
	//직업 초기화
	m_pJob_Array[0] = JOB_HUMAN;
	m_pJob_Array[1] = JOB_HUMAN;
	m_pJob_Array[2] = JOB_DOCTOR;
	m_pJob_Array[3] = JOB_HUMAN;
	m_pJob_Array[4] = JOB_MAFIA;
	m_pJob_Array[5] = JOB_POLICE;
	m_pJob_Array[6] = JOB_HUMAN;
	m_pJob_Array[7] = JOB_HUMAN;
	m_pJob_Array[8] = JOB_MAFIA;
	m_pJob_Array[9] = JOB_HUMAN;

	m_bGame_StateCheck[STATE_SELECT_JOB] = true;
}

int CMoniter::Update(void)
{
	m_fTime += GETTIME;
	Change_GameState();

	return 0;
}

void CMoniter::Render(void)
{
}

void CMoniter::Release(void)
{
	if (m_pJob_Array != NULL)
		delete[] m_pJob_Array;
}

void CMoniter::Change_GameState(void)
{
	if (m_bGame_StateCheck[STATE_SELECT_JOB] == true)
	{
		//게임 시작 되면 5초 뒤에 클라이언트 확인 작업이 들어간다.
		if (m_fTime > 5.f)
		{
			m_bGame_StateCheck[STATE_CLIENT_CHECK] = true;
			m_bGame_StateCheck[STATE_SELECT_JOB] = false;
			m_fTime = 0.f;
		}
	}

	if (m_bGame_StateCheck[STATE_CLIENT_CHECK] == true)
	{
		//마피아는 누가 마피아인지 알도록 해주는 시간이다.
		if (m_fTime > 7.f)
		{
			m_bGame_StateCheck[STATE_DAYTIME] = true;
			m_bGame_StateCheck[STATE_CLIENT_CHECK] = false;
			m_fTime = 0.f;
		}
	}

	if (m_bGame_StateCheck[STATE_DAYTIME] == true)
	{
		//낮 시간. 시간 제한 1분 30초
		if (m_fTime > 90.f)
		{
			m_bGame_StateCheck[STATE_DAYTIME] = false;
			m_bGame_StateCheck[STATE_MAFIA_NIGHT] = true;
			m_fTime = 0.f;
		}
	}

	if (m_bGame_StateCheck[STATE_MAFIA_NIGHT] == true)
	{
		//마피아의 밤 시간 제한은 30초로 둔다.
		if (m_fTime > 30.f)
		{
			m_bGame_StateCheck[STATE_POLICE_TIME] = true;
			m_bGame_StateCheck[STATE_MAFIA_NIGHT] = false;
			m_fTime = 0.f;
		}
	}

	if (m_bGame_StateCheck[STATE_POLICE_TIME] == true)
	{
		//경찰 타임 시간 제한 30초
		if (m_fTime > 30.f)
		{
			m_bGame_StateCheck[STATE_DOCTOR_TIME] = true;
			m_bGame_StateCheck[STATE_POLICE_TIME] = false;
			m_fTime = 0.f;
		}
	}

	if (m_bGame_StateCheck[STATE_DOCTOR_TIME] == true)
	{
		//의사 타임 시간 제한 30초
		if (m_fTime > 30.f)
		{
			m_bGame_StateCheck[STATE_DAYTIME] = true;
			m_bGame_StateCheck[STATE_DOCTOR_TIME] = false;
			m_fTime = 0.f;
		}
	}
}
