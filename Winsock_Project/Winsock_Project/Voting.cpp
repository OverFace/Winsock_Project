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
	
	cout << "��ǥ�� ������� ��ȣ�� �Է��� �ּ��� :"<<endl;
	cin >> choice;

	if (choice != 0) {
		Info.bCheck = true;
		Info.iGet_Count++;
		return result_f();
	}
	else
	{
		// ���
	}
}

void CVoting::result_f()
{
	result[Client] = choice;
	
	if (Client 
		==// ���� �����ִ� Ŭ���̾�Ʈ ��)
		1)
	{
		while (1)
		{
			int max_votes_won = -1; //
			int all_tied = 1;
			for (int i = 0; i <= Client; i++)
			{
				if (result[i] > max_votes_won) // i��° �ĺ��ڰ� ���� ���� ��ǥ���� �������
				{
					if (max_votes_won >= 0) //�ְ� ��ǥ���� 0�� �ƴҶ�
					{
						all_tied = 0; // ��� �ĺ����� ��ǥ���� ������ �ƴϴ�
						max_votes_won = result[i]; //�ְ� ��ǥ�� �Է�
						choice = i;
					}
				}
			}

		}
	}
	else
	{
		cout << "��ø� ��ٷ� �ּ���. �ٸ� ��ǥ�ڵ��� ��ǥ �� �Դϴ�" << endl;
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

	// ���� �ʱ�ȭ
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

	// ������ ������
	retval = send(sock,(char *)choice, BUFSIZE, 0);
	if (retval == SOCKET_ERROR) {
		err_display("send()");
		printf("[TCP Ŭ���̾�Ʈ] %d����Ʈ�� ���½��ϴ�.\n", retval);
	}

	// closesocket()
	closesocket(sock);

	// ���� ����
	WSACleanup();

	return 0;
}
