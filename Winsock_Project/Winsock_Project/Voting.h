#pragma once

class CVoting 
{
public:
	CVoting(void);
	~CVoting(void);

protected:
	int choice;		  // 클라이언트가 선택
	tagUnitInfo Info; // int iGet_Count; 투표 받은 갯수.

private:
	int  Client = Info.iGet_Count;
	int  result[];   // 투표 결과가 담길 배열 

private:
	void check(); // 투표 여부를 받아 투표 갯수를 세는 함수
	void result_f(); // 투표 결과가 담기는 배열에서 최다 득표자를 선출하는 함수
	void err_quit(char *msg); // 소켓 함수 오류 출력 후 종료
	void err_display(char *msg); // 소켓 함수 오류 출력
	int  ResultSendToServer(int argc, char *argv[]); // 최다 득표자를 서버에게 보내는 함수
};

