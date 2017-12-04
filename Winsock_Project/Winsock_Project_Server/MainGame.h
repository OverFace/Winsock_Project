#pragma once

class CObj;
class CMainGame
{
public:
	CMainGame(void);
	~CMainGame(void);

private:
	CObj*	m_pMonitor;

public:
	void	Init(void);
	int		Update(void);
	void	Release(void);
};