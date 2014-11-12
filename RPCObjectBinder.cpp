#include "stdinc.h"
#include "RPCObjectBinder.h"
#include "RootComm.h"
RPCObjectBinder::RPCObjectBinder(void)
{

}
RPCObjectBinder::RPCObjectBinder(string strName, unsigned long address)
{
	m_strName =  strName;
	m_nAddress = address;
}

RPCObjectBinder::~RPCObjectBinder(void)
{

}

string RPCObjectBinder::GetName()
{
	return m_strName;
}

unsigned long RPCObjectBinder::GetAddress()
{
	return m_nAddress;
}

void RPCObjectBinder::SetResult(CClArg Args)
{
	
	m_pargRes->ClearAll();
	m_argRes.ClearAll();
	
	m_pargRes->AddArg(Args);
	m_argRes.AddArg(Args);	
}

CClArgList& RPCObjectBinder::GetResult()
{
	return m_argRes;
}

void RPCObjectBinder::InvokeCall(string strMethod)
{
	IPCDelegatorCore::getInstance()->PK_RequestMedhodCall(GetName(),GetAddress(),strMethod,m_argRes);	
}

void RPCObjectBinder::InvokeCall(string strMethod,CClArgList& args)
{
	m_pargRes = &args;

	IPCDelegatorCore::getInstance()->PK_RequestMedhodCall(GetName(),GetAddress(),strMethod,args);
//	RootComm::getInstance()->Packaging(pBuffer,nLength);
}


