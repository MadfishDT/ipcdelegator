#include "stdinc.h"
#include "MethodCaller.h"

#define METHOD_MIN_BUFFERLEN 1024
#define METHOD_MIN_TYPEBUFFERLEN 4

MethodCaller::MethodCaller(void)
{

}

MethodCaller::~MethodCaller(void)
{
}
void MethodCaller::SetCapture()
{
	m_ObjMethodFilter.SetCapture();
}
void MethodCaller::ReleaseCapture()
{
	m_ObjMethodFilter.ReleaseCapture();
}

void MethodCaller::AddArg(CClArg* Arg)
{
	m_ObjMethodFilter.PutArg(*Arg);
}

CClArg* MethodCaller::GetResult()
{
	return &m_pResult;
}

bool MethodCaller::SyncCallMethod(const char* ObjAddress, const char* Object,const char* Method)
{
	m_ObjMethodFilter.PutObject(ObjAddress,Object);

	if(m_ObjMethodFilter.Excute(Method))
	{
	
		m_ObjMethodFilter.PullResult(m_pResult);

		return true;
	}

	return false;
}

bool MethodCaller::AsyncCallMethod(const char* ObjAddress,const  char* Object,const char* Method)
{
	return false;
}