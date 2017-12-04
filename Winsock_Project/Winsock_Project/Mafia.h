#pragma once
#include "Obj.h"

class CMafia : public CObj
{
public:
	CMafia(void);
	virtual ~CMafia(void);

private:

public:
	virtual	void	Init(void);
	virtual	int		Update(void);
	virtual	void	Render(void);
	virtual void	Release(void);
};