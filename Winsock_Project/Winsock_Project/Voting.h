#pragma once

class CVoting 
{
public:
	CVoting(void);
	~CVoting(void);

protected:
	int choice;		  // Ŭ���̾�Ʈ�� ����
	tagUnitInfo Info; // int iGet_Count; ��ǥ ���� ����.

private:
	int  Client = Info.iGet_Count;
	int  result[];   // ��ǥ ����� ��� �迭 

private:
	void check(); // ��ǥ ���θ� �޾� ��ǥ ������ ���� �Լ�
	void result_f(); // ��ǥ ����� ���� �迭���� �ִ� ��ǥ�ڸ� �����ϴ� �Լ�
	void err_quit(char *msg); // ���� �Լ� ���� ��� �� ����
	void err_display(char *msg); // ���� �Լ� ���� ���
	int  ResultSendToServer(int argc, char *argv[]); // �ִ� ��ǥ�ڸ� �������� ������ �Լ�
};

