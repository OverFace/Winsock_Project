#pragma once
#ifndef VOTING_H
#define VOTING_H

#include "stdafx.h"
#include "Voting.h"

class voting {

protected : 
	int choice; // Ŭ���̾�Ʈ�� ����
	tagUnitInfo Info; // int iGet_Count; ��ǥ ���� ����.
					 //	bool bCheck;	 ��ǥ �ߴ��� ���ߴ��� üũ ����

private :
	
	int result[client];   // ��ǥ ����� ��� �迭 
	void check(); // ��ǥ ���θ� �޾� ��ǥ ������ ���� �Լ�
	void result(); // ��ǥ ����� ���� �迭���� �ִ� Ưǥ�ڸ� �����ϴ� �Լ�
	void ResultSendToServer(); // �ִ� ��ǥ�ڸ� �������� ������ �Լ�

};

#endif VOTING_H