// WinsockProject.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"

int _tmain(int argc, _TCHAR* argv[])
{
	//Main Game Allocate
	CMainGame_Client MainGame;
	MainGame.Set_JobType(JOB_HUMAN);
	MainGame.Init();

	while (true)
	{
		//MainGame Update
		if (MainGame.Update() == 1)
		{
			MainGame.Release();
			break;
		}
	}

	return 0;
}


