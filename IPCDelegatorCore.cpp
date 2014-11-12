#include "stdinc.h"
#include "IPCDelegatorCore.h"
#include "RootComm.h"
#include "ProcDataAdapter.h"
#include "RPCObjectBinder.h"
IPCDelegatorCore::IPCDelegatorCore(void)
{
	m_pIPC = (IPCRepresent*)0;

}

IPCDelegatorCore::~IPCDelegatorCore(void)
{

}

void IPCDelegatorCore::Packaging(char* pBuffer,unsigned int nLen)
{
	m_pIPC->Write((unsigned char*)pBuffer,nLen);
}

bool IPCDelegatorCore::P_CallMethod(ProcParser* pParser)
{

	ProcDataAdapter ArgAdapter;
	int nSize = pParser->GetParamSize();
	m_Caller.SetCapture();

	for(int index = 0; index < nSize ; index++)
	{
		/*parser always return just string param value, parser can not covert data type, parser just parsing protocol string and separate each attribute as string*/
		CClArg* arg = ArgAdapter.ConvertStringToArg(pParser->C_Str_GetParamtype(index),pParser->C_Str_GetParamValue(index));

		if(arg->GetType() != ARG_DATA_EMPTY)
		{
			m_Caller.AddArg(arg);
		}

		delete arg;
	}
	
	if(m_Caller.SyncCallMethod(pParser->C_Str_GetParsedObjectAddress(),pParser->C_Str_GetParsedObjectName(),pParser->C_Str_GetParsedMethod()))
	{
		char cTempResultType[PROC_BUFFER_PARAMMIN_SIZE];
		char cTempResult[PROC_BUFFER_PARAM_SIZE];
		memset(cTempResultType,0,PROC_BUFFER_PARAMMIN_SIZE);
		memset(cTempResult,0,PROC_BUFFER_PARAM_SIZE);

		CClArg* pResultArg = m_Caller.GetResult();

		ArgAdapter.ConvertArgToString(*pResultArg,cTempResultType,cTempResult);

		PK_RequestMethodRes(pParser->GetParsedObjectName(),pParser->GetParsedObjectAddress(),pParser->GetParsedMethod(),cTempResultType,cTempResult);
	}
	m_Caller.ReleaseCapture();

	return true;
}

bool IPCDelegatorCore::P_AddBinderObject(ProcParser* pParser)
{
	m_Factory.AddObject(pParser->GetParsedObjectName(),atol(pParser->GetParsedObjectAddress().c_str()));
	return false;
}

bool IPCDelegatorCore::P_ResultObject(ProcParser* pParser)
{

	pRoot = RootComm::getInstance();	

	
	unsigned int nLength = BUFFER_PIPE_DELEGATOR;
	
	RPCObjectBinder* pObj = m_Factory.FindObject((unsigned long)atol(pParser->C_Str_GetParsedObjectAddress()));

	//pObj->SetResult()
	ProcDataAdapter ArgAdapter;

	CClArg* arg = ArgAdapter.ConvertStringToArg(pParser->C_Str_GetParsedResultType(),pParser->C_Str_GetParsedResult());
	if(arg)
	{
		pObj->SetResult(*arg);
	}
	
	return true;
}

bool IPCDelegatorCore::P_RequestObject(ProcParser* pParser)
{
	ProcPackage m_Package;
	
	pRoot = RootComm::getInstance();	

	char cTempBuffer[PROC_BUFFER_MIN_SIZE];
	unsigned int nLength = PROC_BUFFER_MIN_SIZE;
	
	iObject_glue* pObj = pRoot->CreateCommObject(pParser->GetParsedObjectName());

	m_Package.GetResObjectPackage(pObj->GetName().c_str(),pObj->GetAddress(),cTempBuffer,nLength);

	return m_pIPC->Write((unsigned char*)cTempBuffer,nLength);
}

bool IPCDelegatorCore::PK_RequestMethodRes(string strObjectName,string strAddress,string strMethod,string strResType,string strResVal)
{
	char cTempBuffer[PROC_BUFFER_MAX_SIZE];
	unsigned int nLength = PROC_BUFFER_MAX_SIZE;


	if(m_Package.GetResMethodPackage(strObjectName.c_str(),strAddress.c_str(),strMethod.c_str(),strResType.c_str(),strResVal.c_str(),cTempBuffer,nLength))
	{
		Packaging(cTempBuffer,nLength);
		return true;
	}

	return false;
}

bool IPCDelegatorCore::PK_RequestObject(string strObjectName)
{
	char cBuffer[PROC_BUFFER_MIN_SIZE];
	unsigned int nLen = PROC_BUFFER_MIN_SIZE;
	if(m_Package.GetReqObjectPackage(strObjectName.c_str(),cBuffer,nLen))
	{
		Packaging(cBuffer,nLen);
		return true;
	}

	return false;

}

bool IPCDelegatorCore::PK_RequestMedhodCall(string strObjectName,unsigned long uObjectAddress,string strMethod,CClArgList& args)
{
	char cBuffer[PROC_BUFFER_MAX_SIZE];
	char cParamBuffer[PROC_BUFFER_PARAM_SIZE];

	unsigned int nLen = PROC_BUFFER_MAX_SIZE;

	ProcDataAdapter ArgAdapter;

	memset(cParamBuffer,0,PROC_BUFFER_PARAM_SIZE);

	ArgAdapter.ConvertArgListToString(args,cParamBuffer);

	if(m_Package.GetReqMethodPackage(strObjectName.c_str(),uObjectAddress,strMethod.c_str(),cParamBuffer,cBuffer,nLen))
	{
		Packaging(cBuffer,nLen);
		return false;
	}

	return true;
}


void IPCDelegatorCore::Parsing(char* pBuffer,unsigned int nLen)
{

	ProcParser Parser;

	Parser.AcceptBuffer((unsigned char*)pBuffer,nLen);

	unsigned int nRet = Parser.DoParsing();

	switch(nRet)
	{
	case PP_TYPE_METHODCALL:
		P_CallMethod(&Parser);
		break;
	case PP_TYPE_RECEIVEOBJECT:
		P_AddBinderObject(&Parser);	
		break;
	case PP_TYPE_REQOBJECT:
		P_RequestObject(&Parser);	
		break;
	case PP_TYPE_RETOBJECT:
		P_ResultObject(&Parser);	
	default:
		return;
	}

}

void IPCDelegatorCore::AcceptBuffer(void* pParam, unsigned int nParam)
{
	IPCDelegatorCore* pThis = IPCDelegatorCore::getInstance();
	pThis->Parsing((char*)pParam,nParam);
}	

void IPCDelegatorCore::ExportBuffer(void* pParam, unsigned int nParam)
{
	IPCDelegatorCore* pThis = IPCDelegatorCore::getInstance();
	pThis->Packaging((char*)pParam,nParam);

}

bool IPCDelegatorCore::StartIPCDelegator(bool bClient,bool bCreateNew)
{
	if(!bCreateNew && m_pIPC)
	{
		return false;
	}

	m_pIPC = new IPCRepresent(bClient);

	m_pIPC->RegisterIPCFunc(IPCDelegatorCore::AcceptBuffer,IPCDelegatorCore::ExportBuffer);

	return m_pIPC->Init();

}

ObjectBinderFactory* IPCDelegatorCore::GetFactory()
{
	return &m_Factory;
}
