#pragma once
#include "Obj.h"

class CDoctor : public CObj
{
public:
	CDoctor(void);
	virtual ~CDoctor(void);

private:

public:
	virtual	void	Init(void);
	virtual	int		Update(void);
	virtual	void	Render(void);
	virtual void	Release(void);
};