#ifndef struct_h_
#define struct_h_

typedef struct tagUnitInfo
{
	eJobType	eJobType;		//직업 타입
	int			iGet_Count;		//투표 받은 갯수.
	bool		bCheck;			//투표 했는지 안했는지 체크 변수.
}UNITINFO;

#endif // !struct_h_
