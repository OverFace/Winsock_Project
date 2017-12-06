#pragma once

class CObj;
class CMainGame_Client
{
public:
	CMainGame_Client(void);
	~CMainGame_Client(void);

private:
	eJobType			m_eJobType;
	CObj*				m_pPlayer;
	SOCKADDR_IN			m_Peer_Addr;				//SOCKADDR_IN Struct
	char				m_szBuf[BUFSIZE + 1];		//Data Container
	int					m_iLen;						//Buf Length
	int					m_iAddr_Len;				//Addr Length

public: //Getter
	inline CObj*		Get_Player(void) { return m_pPlayer; }

public: //Setter
	inline void			Set_JobType(eJobType _eType) { m_eJobType = _eType; }

public:
	void				Init(void);
	int					Update(void);
	void				Render(void);
	void				Release(void);

public:
	void				Data_Input(void);
	int					Data_Send(SOCKET* pSocket, SOCKADDR_IN* pServer_Addr, int iRetval);
	int					Data_Recv(SOCKET* pSocket, SOCKADDR_IN* pServer_Addr, int iRetval);
	void				Data_Render(int iRetval);
};