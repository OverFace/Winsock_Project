#pragma once
#ifndef VOTING_H
#define VOTING_H

#include "stdafx.h"
// ���� ��ſ� �ʿ��� �������
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    50

class voting {

protected:
	int choice; // Ŭ���̾�Ʈ�� ����
	tagUnitInfo Info; // int iGet_Count; ��ǥ ���� ����.
					 //	bool bCheck;	 ��ǥ �ߴ��� ���ߴ��� üũ ����


private:
	int Client = Info.iGet_Count;
	int result[] = {0};   // ��ǥ ����� ��� �迭 
	void check(); // ��ǥ ���θ� �޾� ��ǥ ������ ���� �Լ�
	void result_f(); // ��ǥ ����� ���� �迭���� �ִ� ��ǥ�ڸ� �����ϴ� �Լ�
	void err_quit(char *msg); // ���� �Լ� ���� ��� �� ����
	void err_display(char *msg); // ���� �Լ� ���� ���
	int ResultSendToServer(int argc, char *argv[]); // �ִ� ��ǥ�ڸ� �������� ������ �Լ�
};

#endif VOTING_H