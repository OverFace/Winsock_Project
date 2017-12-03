#pragma once

class CObj;
class CMainGame_Client
{
public:
	CMainGame_Client(void);
	~CMainGame_Client(void);

private:
	list<CObj*>		m_Client_List;

public: //Getter
	inline list<CObj*>*	Get_Client_List(void) { return &m_Client_List; }
	
public: //Setter
	inline void			Add_Client_List(CObj* pObj) { m_Client_List.push_back(pObj); }

public:
	void	Init(void);
	int		Update(void);
	void	Render(void);
	void	Release(void);
};