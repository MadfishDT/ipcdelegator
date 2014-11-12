#include "stdinc.h"
#include "ProcParser.h"

#include <vector>


ProcParser::ProcParser(void)
{
	m_pBuffer = new unsigned char[PROC_BUFFER_MAX_SIZE];
	memset(m_pBuffer,0,PROC_BUFFER_MAX_SIZE);
}

ProcParser::~ProcParser(void)
{
	delete[] m_pBuffer; 
}
void ProcParser::ClearBuffer()
{
	memset(m_pBuffer,0,PROC_BUFFER_MAX_SIZE);
}
void ProcParser::AcceptBuffer(unsigned char* pBuffer,int nLen)
{
	memcpy(m_pBuffer,pBuffer,nLen);
}

unsigned int  ProcParser::DoParsing()
{
	char* pBuffer = (char*)m_pBuffer;

	char* pObject = GetAttribute(&pBuffer,TAG_OBJECT);
	if(pObject)
	{
		if(ParsingExcutionOperation())
		{
			return PP_TYPE_METHODCALL;
		}
	}

	char* pReqObject = GetAttribute(&pBuffer,TAG_REQOBJECT);
	if(pReqObject)
	{
		if(ParsingRequestObject())
		{
			return PP_TYPE_REQOBJECT;
		}
	}

	char* pOutObject = GetAttribute(&pBuffer,TAG_OUT);
	if(pOutObject)
	{
		if(ParsingOutObject())
		{
			return PP_TYPE_RECEIVEOBJECT;
		}
	}
	char* pRetObject = GetAttribute(&pBuffer,TAG_RETOBJECT);
	if(pRetObject)
	{
		if(ParsingRetObject())
		{
			return PP_TYPE_RETOBJECT;
		}
	}
	return PP_TYPE_ERROR;
}

bool ProcParser::ParsingRetObject()
{
	char* pBuffer = (char*)m_pBuffer;
	char* pObject = GetAttribute(&pBuffer,TAG_RETOBJECT);
	char* ObjectAddress = GetPrifix(pObject);
	char* ObjectName = GetPostfix(pObject);

	m_strObjectName = string(ObjectName);
	m_strAddress = string(ObjectAddress);

	char* pMethodt = GetAttribute(&pBuffer,TAG_METHOD);
	m_strMethod = string(pMethodt);

	char* pReturn = GetAttribute(&pBuffer,TAG_RESULT);
	char* pReturnType = GetPrifix(pReturn);
	char* pReturnVal = GetPostfix(pReturn);
	m_strResultType = string(pReturnType);
	m_strResult = string(pReturnVal);

	delete[]  pObject;
	delete[]  ObjectAddress;
	delete[]  ObjectName;
	delete[] pMethodt;

	return true;
}

bool ProcParser::ParsingExcutionOperation()
{
	
	char* pBuffer = (char*)m_pBuffer;

	char* pObject = GetAttribute(&pBuffer,TAG_OBJECT);
	char* ObjectAddress = GetPrifix(pObject);
	char* ObjectName = GetPostfix(pObject);
	
	m_strObjectName = string(ObjectName);
	m_strAddress = string(ObjectAddress);
	
	char* pMethodt = GetAttribute(&pBuffer,TAG_METHOD);
	m_strMethod = string(pMethodt);

	bool bNothingParam = false;

	while(!bNothingParam)
	{
		char* pParam = GetAttribute(&pBuffer,TAG_PARAM);

		if(!pParam)
		{
			bNothingParam = true;
		}
		else
		{
			char* ParamType = GetPrifix(pParam);
			char* ParamValue = GetPostfix(pParam);

			m_vecParamTypes.push_back(string(ParamType));
			m_vecParamValues.push_back(string(ParamValue));
		
			delete[] ParamType;
			delete[] ParamValue;
			delete[] pParam;
		}
	}

	delete[]  pObject;
	delete[]  ObjectAddress;
	delete[]  ObjectName;
	delete[] pMethodt;
	return true;
}

bool ProcParser::ParsingOutObject()
{
	char* pBuffer = (char*)m_pBuffer;

	char* pObject = GetAttribute(&pBuffer,TAG_OUT);

	char* ObjectAddress = GetPrifix(pObject);

	char* ObjectName = GetPostfix(pObject);

	m_strObjectName = string(ObjectName);
	m_strAddress = string(ObjectAddress);

	delete[]  pObject;
	delete[]  ObjectAddress;
	delete[]  ObjectName;

	return true;
}

bool ProcParser::ParsingRequestObject()
{
	char* pBuffer = (char*)m_pBuffer;

	char* pObject = GetAttribute(&pBuffer,TAG_REQOBJECT);

	m_strObjectName = pObject;

	delete[]  pObject;
	return true;
}
char* ProcParser::GetPrifixWithDelimiter(char* pBuffer,const char* cprefix)
{
	char* pResult;
	char* pPos1;
	pPos1 = strstr(pBuffer,cprefix);
	unsigned int nLen = (unsigned int)(pPos1 - pBuffer) + 1;
	pResult = new char[nLen];
	memset(pResult,0,nLen);
	memcpy(pResult,pBuffer,nLen-1);

	return pResult;

}
char* ProcParser::GetPostfixWithDelimiter(char* pBuffer,const char* cprefix)
{
	char* pResult;
	char* pPos1;

	pPos1 = strstr(pBuffer,cprefix);

	pPos1 = pPos1 +1;

	int nLen = (int)strlen(pPos1)+1;
	pResult = new char[nLen];
	memset(pResult,0,nLen);
	memcpy(pResult,pPos1,nLen-1);

	return pResult;
}

char* ProcParser::GetPrifix(char* pBuffer)
{
	char* pResult;
	char* pPos1;
	pPos1 = strstr(pBuffer,":");
	unsigned int nLen = (unsigned int)(pPos1 - pBuffer) + 1;
	pResult = new char[nLen];
	memset(pResult,0,nLen);
	memcpy(pResult,pBuffer,nLen-1);

	return pResult;

}
char* ProcParser::GetPostfix(char* pBuffer)
{
	char* pResult;
	char* pPos1;

	pPos1 = strstr(pBuffer,":");

	pPos1 = pPos1 +1;

	int nLen = (int)strlen(pPos1)+1;
	pResult = new char[nLen];
	memset(pResult,0,nLen);
	memcpy(pResult,pPos1,nLen-1);

	return pResult;
}

char* ProcParser::GetAttribute(char** ppBuffer,const char* pTag)
{
	char* pBuffer = *ppBuffer;

	char* pPos1;
	char* pPos2;

	/*object tag parsing*/
	pPos1 = strstr(pBuffer,pTag); /*object tag find*/
	if(!pPos1)
	{
		return (char*)0;
	}
	pPos1 += strlen(pTag);
	pPos1 += 1;
	pBuffer = pPos1;


	pPos1 = strstr(pBuffer,"\"");/*start "*/
	pPos2 = strstr(pPos1+1,"\"");/*end "*/

	unsigned int nLen = (int)(pPos2 - pPos1) -1;
	char* pObjectAttribute = new char[nLen+1];
	memset(pObjectAttribute,0,nLen+1);
	memcpy(pObjectAttribute,pPos1 + 1,nLen);

	(*ppBuffer) = pPos2;
	return pObjectAttribute;
}


string ProcParser::GetParsedObjectName()
{
	return m_strObjectName;
}

string ProcParser::GetParsedObjectAddress()
{
	return m_strAddress;
}

string ProcParser::GetParsedMethod()
{
	return m_strMethod;
}

string ProcParser::GetParsedResultType()
{
	return m_strResultType;
}

string ProcParser::GetParsedResult()
{
	return m_strResult;
}
string ProcParser::GetParamtype(int index)
{
	return m_vecParamTypes[index].c_str();
}
string ProcParser::GetParamValue(int index)
{
	return m_vecParamValues[index].c_str();
}

const char* ProcParser::C_Str_GetParsedObjectName()
{
	return m_strObjectName.c_str();
}

const char* ProcParser::C_Str_GetParsedObjectAddress()
{
	return m_strAddress.c_str();
}

const char* ProcParser::C_Str_GetParsedMethod()
{
	return m_strMethod.c_str();
}

const char* ProcParser::C_Str_GetParsedResultType()
{
	return m_strResultType.c_str();
}

const char* ProcParser::C_Str_GetParsedResult()
{
	return m_strResult.c_str();
}

const char* ProcParser::C_Str_GetParamtype(int index)
{
	return m_vecParamTypes[index].c_str();
}

const char* ProcParser::C_Str_GetParamValue(int index)
{
	return m_vecParamValues[index].c_str();
}

unsigned int ProcParser::GetParamSize()
{
	return (unsigned int)m_vecParamValues.size();
}
