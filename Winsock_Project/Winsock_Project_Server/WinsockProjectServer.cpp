// WinsockProjectServer.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "MainGame.h"

void Err_Display(char* msg)
{

}

int main()
{
	CMainGame MainGame;

	MainGame.Init();
	
	while (true)
	{
		if (MainGame.Update() == 1)
		{
			break;
		}
	}

    return 0;
}

