#include "stdafx.h"
#include "Human.h"

CHuman::CHuman(void)
{
}

CHuman::~CHuman(void)
{
	Release();
}

void CHuman::Init(void)
{

}

int CHuman::Update(void)
{
	return 0;
}

void CHuman::Render(void)
{
	//이객체가 보여줄 것들
	cout << "[직업 : 시민] " << endl;
}

void CHuman::Release(void)
{
}
