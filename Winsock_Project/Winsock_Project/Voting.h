#pragma once
#ifndef VOTING_H
#define VOTING_H

#include "stdafx.h"
#include "Voting.h"

class voting {

protected : 
	int choice; // 클라이언트가 선택
	tagUnitInfo Info; // int iGet_Count; 투표 받은 갯수.
					 //	bool bCheck;	 투표 했는지 안했는지 체크 변수

private :
	
	int result[client];   // 투표 결과가 담길 배열 
	void check(); // 투표 여부를 받아 투표 갯수를 세는 함수
	void result(); // 투표 결과가 담기는 배열에서 최다 특표자를 선출하는 함수
	void ResultSendToServer(); // 최다 득표자를 서버에게 보내는 함수

};

#endif VOTING_H