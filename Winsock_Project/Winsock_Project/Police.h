#pragma once
#include "Obj.h"

class CPolice : public CObj
{
public:
	CPolice(void);
	virtual ~CPolice(void);

private:

public:
	virtual	void	Init(void);
	virtual	int		Update(void);
	virtual	void	Render(void);
	virtual void	Release(void);
};