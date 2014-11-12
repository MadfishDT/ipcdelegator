#ifndef _ThreadRepresent_H
#define  _ThreadRepresent_H

/*thread porting class, win linux etc...*/

 #include <pthread.h>
 
typedef unsigned long (*Fn)(void* p);

#define THREAD_STATE_NON 0X00
#define THREAD_STATE_CREATED 0X01
#define THREAD_STATE_RUNNING 0X02
#define THREAD_STATE_STOP 0X04

class ThreadRepresent
{
public:
	
	ThreadRepresent(void);

	~ThreadRepresent(void);

	bool MakeThread();

	void RegisterThreadFunc(Fn pFn, void* param);

	void SetState(unsigned int nState);

	bool Start();

	bool Stop();

//	static unsigned long  InnerThreadFunc(void* pParam);
	static void*  InnerThreadFunc(void* pParam);

	void* GetParam();
	Fn GetFunction();

private:

	unsigned int m_State;

	unsigned long m_nThreadID;
	pthread_t  m_hThreadHandle;
	Fn m_Fn;

	void * m_pParam;

};
#endif
