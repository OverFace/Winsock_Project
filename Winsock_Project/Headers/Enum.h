#ifndef enum_h_
#define enum_h_

enum eJobType
{
	JOB_MAFIA,		//���Ǿ�
	JOB_POLICE,		//����
	JOB_DOCTOR,		//�ǻ�
	JOB_HUMAN,		//�Ϲ� �ù�
	JOB_END
};

enum eGameStateType
{
	STATE_SELECT_JOB,
	STATE_CLIENT_CHECK,
	STATE_MAFIA_NIGHT,
	STATE_DAYTIME,
	STATE_POLICE_TIME,
	STATE_DOCTOR_TIME,
	STATE_END
};

#endif // !enum_h_
