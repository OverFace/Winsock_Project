#pragma once
#include "Obj.h"

class CHuman : public CObj
{
public:
	CHuman(void);
	virtual ~CHuman(void);

private:

public:
	virtual	void	Init(void);
	virtual	int		Update(void);
	virtual	void	Render(void);
	virtual void	Release(void);
};
