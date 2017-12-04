#include "stdafx.h"
#include "Voting.h"

CVoting::CVoting(void)
{

}

CVoting ::~CVoting(void)
{

}

void CVoting::check()
{
	Info.bCheck = false;
	Info.iGet_Count = 0;
	choice = 0;
	
	cout << "투표할 사용자의 번호를 입력해 주세요 :"<<endl;
	cin >> choice;

	if (choice != 0) {
		Info.bCheck = true;
		Info.iGet_Count++;
		return result_f();
	}
	else
	{
		// 기권
	}
}

void CVoting::result_f()
{
	result[Client] = choice;
	
	if (Client 
		==// 현재 남아있는 클라이언트 수)
		1)
	{
		while (1)
		{
			int max_votes_won = -1; //
			int all_tied = 1;
			for (int i = 0; i <= Client; i++)
			{
				if (result[i] > max_votes_won) // i번째 후보자가 가장 많은 득표수를 얻었을때
				{
					if (max_votes_won >= 0) //최고 득표수가 0이 아닐때
					{
						all_tied = 0; // 모든 후보자의 득표수는 동점이 아니다
						max_votes_won = result[i]; //최고 득표수 입력
						choice = i;
					}
				}
			}

		}
	}
	else
	{
		cout << "잠시만 기다려 주세요. 다른 투표자들이 투표 중 입니다" << endl;
	}

}

void CVoting::err_quit(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	MessageBox(NULL, (LPCTSTR)lpMsgBuf, msg, MB_ICONERROR);
	LocalFree(lpMsgBuf);
	exit(1);
}

void CVoting::err_display(char * msg)
{
	LPVOID lpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf, 0, NULL);
	printf("[%s] %s", msg, (char *)lpMsgBuf);
	LocalFree(lpMsgBuf);
}

int CVoting::ResultSendToServer(int argc, char * argv[])
{
	int retval;

	// 윈속 초기화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	// socket()
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) err_quit("socket()");

	// connect()
	SOCKADDR_IN serveraddr;
	ZeroMemory(&serveraddr, sizeof(serveraddr));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_addr.s_addr = inet_addr(SERVERIP);
	serveraddr.sin_port = htons(PORTNUMBER);
	retval = connect(sock, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	if (retval == SOCKET_ERROR) err_quit("connect()");

	// 데이터 보내기
	retval = send(sock,(char *)choice, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		printf("[TCP 클라이언트] %d바이트를 보냈습니다.\n", retval);
	}

	// closesocket()
	closesocket(sock);

	// 윈속 종료
	WSACleanup();

	return 0;
}
