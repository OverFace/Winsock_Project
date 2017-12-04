#pragma once

class CObj;
class CMainGame_Client
{
public:
	CMainGame_Client(void);
	~CMainGame_Client(void);

private:
	eJobType			m_eJobType;
	CObj*				m_pPlayer;

public: //Getter
	inline CObj*		Get_Player(void) { return m_pPlayer; }

public: //Setter
	inline void			Set_JobType(eJobType _eType) { m_eJobType = _eType; }

public:
	void	Init(void);
	int		Update(void);
	void	Render(void);
	void	Release(void);
};