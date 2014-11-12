#include "../../stdinc.h"
#include "ThreadRepresent.h"

ThreadRepresent::ThreadRepresent(void)
{
	m_State = THREAD_STATE_NON;
}

ThreadRepresent::~ThreadRepresent(void)
{

}

/*implementation thread create function by each platform OS*/
bool ThreadRepresent::MakeThread()
{
	
	/*test for window*/
	//m_hThreadHandle = (unsigned long)CreateThread(NULL,0,ThreadRepresent::InnerThreadFunc,(void*)this,0,&m_nThreadID);
	perror("ThreadRepresent::MakeThread start");
	int ret =0;
	int status = 0;
	ret = pthread_create(&m_hThreadHandle, NULL, &ThreadRepresent::InnerThreadFunc, (void *)this);
	
	if(ret >= 0)
	{
		perror("ThreadRepresent::MakeThread Make Success");
		m_State = THREAD_STATE_CREATED;
		
			
	}
	else
	{
		perror("ThreadRepresent::MakeThread Make fail");
		m_State = THREAD_STATE_STOP;
		return false;
	}
	return true;
	
}

void ThreadRepresent::RegisterThreadFunc(Fn pFn, void* param)
{
	m_Fn  = 	pFn;
	m_pParam = param;
}

bool ThreadRepresent::Start()
{
	return true;
}

bool ThreadRepresent::Stop()
{
	return true;
}

void* ThreadRepresent::GetParam()
{
	return m_pParam;
}

Fn ThreadRepresent::GetFunction()
{
	return m_Fn;
}


void ThreadRepresent::SetState(unsigned int nState)
{
	m_State = nState;
}

void*  ThreadRepresent::InnerThreadFunc(void* pParam)
{
	ThreadRepresent* pThis = (ThreadRepresent*)pParam;
	
	pThis->SetState(THREAD_STATE_RUNNING);

	Fn pfunc = pThis->GetFunction();

	(*pfunc)(pThis->GetParam());

	return 0;
}
