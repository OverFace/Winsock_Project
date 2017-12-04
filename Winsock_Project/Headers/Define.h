#ifndef define_h_
#define define_h_

#define SERVERIP	"127.0.0.1"
#define MULTICASTIP "235.7.8.9"
#define PORTNUMBER  9000
#define MAX_MEMCNT  10
#define BUFSIZE     512
#define MAX_PATH	256
#define PURE		=0

#define DECLARE_SINGLETON(ClassName)		\
	private:								\
static ClassName*	m_pInstance;			\
public:										\
	static ClassName*	GetInstance(void)	\
	{										\
		if(m_pInstance == NULL)				\
			m_pInstance = new ClassName;	\
		return m_pInstance;					\
	}										\
	void	DestroyInstance(void)			\
	{										\
		if(m_pInstance)						\
		{									\
			delete m_pInstance;				\
			m_pInstance = NULL;				\
		}									\
	}										\
private:									\
ClassName(void);							\
ClassName(ClassName& r){;}					\

#define IMPLEMENT_SINGLETON(ClassName)		\
ClassName*	ClassName::m_pInstance = NULL;	\

#define GETTIME	CTimeMgr::GetInstance()->GetTime()

#endif // !define_h_
