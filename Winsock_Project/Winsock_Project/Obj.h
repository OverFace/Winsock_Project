#pragma once

class CObj
{
public:
	CObj(void);
	virtual ~CObj(void);

protected:	//Unit Info


public:
	virtual	void	Init(void) = 0;
	virtual	int		Update(void) = 0;
	virtual	void	Render(void) = 0;
	virtual void	Release(void) = 0;
};