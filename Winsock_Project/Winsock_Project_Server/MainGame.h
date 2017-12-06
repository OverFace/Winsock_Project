#pragma once

class CObj;
class CMainGame
{
public:
	CMainGame(void);
	~CMainGame(void);

private: //Data Send & Recv
	CObj*			m_pMonitor;
	SOCKADDR_IN		m_Client_Addr;
	int				m_iAddr_Len;
	char			m_szBuf[BUFSIZE + 1];

public:	//Getter

public: //Setter
	inline void		Set_PeerAddr_Struct(SOCKADDR_IN* pAddr) { memcpy_s(&m_Client_Addr, sizeof(m_Client_Addr), pAddr, sizeof(m_Client_Addr)); }

public:
	void			Init(void);
	int				Update(void);
	void			Release(void);

public:	//Data Communication Normal Fucntion
	int				Data_Recv(SOCKET* pSocket, int iRetval);
	void			Data_Render(int iRetval);
	int				Data_Send(int iClient_Sock, int iRetval, char* pString);

public: //Multiple Communication Function
	void			Listen_Client(SOCKET* pSocket, int iClient_Num);
	int				Client_Accept(SOCKET* pSocket);
	void			Client_Accept_Render(int iSeat);

public:
	void			JobType_SendTo_Client(int iClient_Sock, int iSeat);
	void			GameState_SendTo_Client(int iClient_Sock, int iSeat);
};