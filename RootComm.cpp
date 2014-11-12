#include "stdinc.h"
#include "RootComm.h"
#include "iApplication_glue.h"

RootComm::RootComm(void)
{
	
}

RootComm::~RootComm(void)
{
	
}



iObject_glue* RootComm::CreateCommObject(string strName)
{
	/*add create object code*/
	perror("RootComm::CreateCommObject end");
	if(strName == "application")
	{
		return new iApplication_glue();
	}
	return new iObject_glue();
}

void RootComm::StartServerType(bool bCreateNew)
{
	IPCDelegatorCore::getInstance()->StartIPCDelegator(false,bCreateNew);
}

void RootComm::StartClientType(bool bCreateNew)
{
	IPCDelegatorCore::getInstance()->StartIPCDelegator(true,bCreateNew);
}

void RootComm::Stop()
{
	
}

ObjectBinderFactory* RootComm::GetFactory()
{
	return IPCDelegatorCore::getInstance()->GetFactory();
}

