#include "stdinc.h"
#include "ObjectMethodFilter.h"
#include "ObjectMathodMap.h"
#include "MethodDataTypes.h"
ObjectMethodFilter::ObjectMethodFilter(void)
{
	m_OMMap = ObjectMathodMap::getInstance();
	m_bResult = false;
}

ObjectMethodFilter::~ObjectMethodFilter(void)
{

}

void ObjectMethodFilter::SetCapture()
{
	m_pAlgList = new CClArgList();
	m_bCapture =true;
}

void ObjectMethodFilter::PullResult(CClArg& Arg)
{
	if(m_pAlgList->GetLength())
	{
		Arg = m_pAlgList->GetArg(0);
	}
}


void ObjectMethodFilter::PullObject(char* ObjAddress, char* Object,char* Method, char* result , char* resulttype)
{
	sprintf(ObjAddress,"%lu",m_Address);
	memcpy((char*)Object,m_strObject.c_str(),m_strObject.length());
	memcpy((char*)Method,m_strMethod.c_str(),m_strMethod.length());
	
	char stype = *(m_strResultType.c_str());

	int nArg = 0;
	float fArg = 0.0f;
	string strArg;

	switch(stype)
	{
		case ARG_DATA_INT:
			*m_pAlgList<< nArg;
			sprintf(result,"%d",nArg);
			break;
		case ARG_DATA_FLOAT:
			*m_pAlgList<< fArg;
			gcvt((double)fArg,5,(char*)result);
			break;
		case ARG_DATA_STRING:
			*m_pAlgList<< strArg;
			memcpy((char*)result,strArg.c_str(),strArg.length());
			break;
	}
}

void ObjectMethodFilter::PutObject(const char* ObjAddress, const char* Object)
{
	m_Address = (unsigned long)atol((const char*)ObjAddress);
	m_strObject = string((char*)Object);
}

void ObjectMethodFilter::PutResult(const char* type)
{
	char stype = *type;

	m_strResultType = string(type);

	switch(stype)
	{
	case ARG_DATA_INT:
	case ARG_DATA_FLOAT:
	case ARG_DATA_STRING:
		m_bResult = true;
	default:
		m_bResult = false;
	}
}

void ObjectMethodFilter::PutArg(CClArg& Arg)
{
	m_pAlgList->AddArg(Arg);
}

bool ObjectMethodFilter::Excute(const char* Method)
{
	
	string m_strMethod = string((const char*)Method);

	return m_OMMap->ExcuteMethod(m_OMMap->GetMathodDelegator(m_strObject,m_Address),m_strMethod,*m_pAlgList,m_bResult);

}

void ObjectMethodFilter::ReleaseCapture()
{
	delete m_pAlgList;
	m_bCapture = false;
	m_bResult = false;
}

void ObjectMethodFilter::RequestObject(const char* ObjName)
{

}


/*to handling about array type arg and result, object filter provide string parsing and packaging method, later this logic should change*/
const char* ObjectMethodFilter::GetIntArrayBuffer(vector<int>& VecInt)
{
	string strtemp;

	char temp[16];

	memset(temp,0,16);

	vector<int>::iterator itor = VecInt.begin();

	int nNum;

	bool bFirst = true;
	for(;itor  != VecInt.end(); itor++)
	{
		if(!bFirst)
		{
			strtemp += ";";
		}
		bFirst = false;

		nNum = (*itor);
		sprintf(temp,"%d",nNum);
		strtemp += temp;

		memset(temp,0,16);
	}

	return strtemp.c_str();
}

const char* ObjectMethodFilter::GetStringMapArrayBuffer(map<string,string>& srtMap)
{

	map<string,string>::iterator itor = srtMap.begin();
	char temp[1024];
	memset(temp,0,1024);

	string strtemp;
	bool bFirst = true;
	for(;itor != srtMap.end() ; itor++)
	{
		if(!bFirst)
		{
			strtemp += ";";
		}
		bFirst = false;
		sprintf(temp,"%s[%s]",itor->first.c_str(),itor->second.c_str());

		strtemp += temp;
		memset(temp,0,1024);	
	}

	return strtemp.c_str();

}
char* ObjectMethodFilter::GetPrifixWithDelimiter(char* pBuffer,const char* cprefix)
{
	char* pResult;
	char* pPos1;
	pPos1 = strstr(pBuffer,cprefix);
	if(pPos1)
	{
		unsigned int nLen = (unsigned int)(pPos1 - pBuffer) + 1;
		pResult = new char[nLen];
		memset(pResult,0,nLen);
		memcpy(pResult,pBuffer,nLen-1);
	}
	else
	{
		return pBuffer;
	}
	return pResult;

}