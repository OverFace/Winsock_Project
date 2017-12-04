#pragma once

class CObj
{
public:
	CObj(void);
	virtual ~CObj(void);

protected:	//Unit Info
	UNITINFO		m_tInfo;
	char			m_szNickName[MAX_PATH];

public:	//Getter
	inline UNITINFO*	Get_UnitInfo(void) { return &m_tInfo; }

public: //Setter
	inline void			Set_UnitInfo(UNITINFO* pInfo) { memcpy_s(&m_tInfo, sizeof(UNITINFO), pInfo, sizeof(UNITINFO)); }

public:
	virtual	void	Init(void)PURE;
	virtual	int		Update(void)PURE;
	virtual	void	Render(void)PURE;
	virtual void	Release(void)PURE;

public:
	void			Create_NickName(void);
};