#pragma once
#include "Obj.h"

class CMoniter : public CObj
{
public:
	CMoniter(void);
	virtual ~CMoniter(void);

private:
	float			m_fTime;
	int				m_iRandom;
	eJobType*		m_pJob_Array;
	bool			m_bGame_StateCheck[STATE_END];

public: //Getter
	inline eJobType* Get_JobArray(void) { return m_pJob_Array; }
	inline bool		 Get_GameState(eGameStateType _Type) { return m_bGame_StateCheck[_Type]; }

public:
	virtual	void	Init(void);
	virtual	int		Update(void);
	virtual	void	Render(void);
	virtual void	Release(void);

public:
	void			Change_GameState(void);
};