#pragma once
#ifndef VOTING_H
#define VOTING_H

#include "stdafx.h"
// 서버 통신에 필요한 헤더파일
#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdlib.h>
#include <stdio.h>

#define SERVERIP   "127.0.0.1"
#define SERVERPORT 9000
#define BUFSIZE    50

class voting {

protected:
	int choice; // 클라이언트가 선택
	tagUnitInfo Info; // int iGet_Count; 투표 받은 갯수.
					 //	bool bCheck;	 투표 했는지 안했는지 체크 변수


private:
	int Client = Info.iGet_Count;
	int result[] = {0};   // 투표 결과가 담길 배열 
	void check(); // 투표 여부를 받아 투표 갯수를 세는 함수
	void result_f(); // 투표 결과가 담기는 배열에서 최다 득표자를 선출하는 함수
	void err_quit(char *msg); // 소켓 함수 오류 출력 후 종료
	void err_display(char *msg); // 소켓 함수 오류 출력
	int ResultSendToServer(int argc, char *argv[]); // 최다 득표자를 서버에게 보내는 함수
};

#endif VOTING_H