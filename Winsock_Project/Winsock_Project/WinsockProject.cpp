// WinsockProject.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"


int main()
{
	CMainGame_Client MainGame;
	MainGame.Init();

	while (true)
	{
		if (MainGame.Update() == 1)
		{
			MainGame.Release();
			break;
		}
	}

	
}

