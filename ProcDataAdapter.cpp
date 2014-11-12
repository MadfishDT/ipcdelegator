
#include "ProcDataAdapter.h"
#include "stdinc.h"


#define ADAPTER_PARAM_FORMAT  "#param=\"%s:%s\"\n"

static const std::string base64_chars = 
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";

using namespace std;

ProcDataAdapter::ProcDataAdapter(void)
{

}

ProcDataAdapter::~ProcDataAdapter(void)
{

}

bool ProcDataAdapter::is_base64(unsigned char c) 
{
	return (isalnum(c) || (c == '+') || (c == '/'));
}


std::string ProcDataAdapter::base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) 
{
	std::string ret;
	int i = 0;
	int j = 0;
	unsigned char char_array_3[3];
	unsigned char char_array_4[4];

	while (in_len--) {
		char_array_3[i++] = *(bytes_to_encode++);
		if (i == 3) {
			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for(i = 0; (i <4) ; i++)
				ret += base64_chars[char_array_4[i]];
			i = 0;
		}
	}

	if (i)
	{
		for(j = i; j < 3; j++)
			char_array_3[j] = '\0';

		char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
		char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
		char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
		char_array_4[3] = char_array_3[2] & 0x3f;

		for (j = 0; (j < i + 1); j++)
			ret += base64_chars[char_array_4[j]];

		while((i++ < 3))
			ret += '=';

	}

	return ret;

}

std::string ProcDataAdapter::base64_decode(std::string const& encoded_string) {
	int in_len = encoded_string.size();
	int i = 0;
	int j = 0;
	int in_ = 0;
	unsigned char char_array_4[4], char_array_3[3];
	std::string ret;

	while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
		char_array_4[i++] = encoded_string[in_]; in_++;
		if (i ==4) {
			for (i = 0; i <4; i++)
				char_array_4[i] = base64_chars.find(char_array_4[i]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (i = 0; (i < 3); i++)
				ret += char_array_3[i];
			i = 0;
		}
	}

	if (i) {
		for (j = i; j <4; j++)
			char_array_4[j] = 0;

		for (j = 0; j <4; j++)
			char_array_4[j] = base64_chars.find(char_array_4[j]);

		char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
		char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
		char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

		for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
	}

	return ret;
}

bool ProcDataAdapter::ConvertArgListToString(CClArgList& Args,char* pResult)
{
	char pParamBuffer[PROC_BUFFER_PARAM_SIZE];
	char pParamVal[PROC_BUFFER_PARAM_SIZE];
	char pParamType[PROC_BUFFER_PARAMMIN_SIZE];

	char* pResultParam;

	string strParams;
	
	int nArgLen = Args.GetLength();

	int nType = 0;
	
	if(nArgLen <=0)/*no argment*/
	{	
		memset(pParamBuffer,0,PROC_BUFFER_PARAM_SIZE);
		sprintf(pParamBuffer,ADAPTER_PARAM_FORMAT,"o","0");
		return true;
	}

	for(int index =0 ;  index < nArgLen ; index++)
	{
		CClArg ar = Args.GetArg(index);
	

		memset(pParamVal,0,PROC_BUFFER_PARAM_SIZE);
		memset(pParamType,0,PROC_BUFFER_PARAMMIN_SIZE);
		ConvertArgToString(ar,pParamType,pParamVal);

		memset(pParamBuffer,0,PROC_BUFFER_PARAM_SIZE);

		sprintf(pParamBuffer,ADAPTER_PARAM_FORMAT,pParamType,pParamVal);

		strParams += string(pParamBuffer);
	}

	memcpy(pResult,strParams.c_str(),strParams.length());

	return true;
}
bool ProcDataAdapter::ConvertArgToString(CClArg& Arg,char* pResultType,char* pResult)
{
	
	int nParamType =Arg.GetType();
	char* pBu = (char*)0x00;

	string strRet;
	switch(nParamType)
	{
	case CLVT_I:
		sprintf(pResult,"%d",Arg.GetiVal());
		pResultType[0] = (unsigned char)ARG_DATA_INT;
		break;
	case CLVT_UI:
		sprintf(pResult,"%u",(int)Arg.GetUI());
		pResultType[0] = (unsigned char)ARG_DATA_UINT;
		break;
	case CLVT_UL:
		sprintf(pResult,"%lu",(long)Arg.GetUL());
		pResultType[0] = (unsigned char)ARG_DATA_ULONG;
		break;
	case CLVT_F:
		gcvt((double)Arg.GetfVal(),5,(char*)pResult);
		pResultType[0] = (unsigned char)ARG_DATA_FLOAT;
		break;
	case CLVT_S:
		strRet = base64_encode((unsigned char*)Arg.GetsVal().c_str(),Arg.GetsVal().length());
		memcpy((char*)pResult,strRet.c_str(),strRet.length());
		pResultType[0] = (unsigned char)ARG_DATA_STRING;
		break;
	case CLVT_VI:
		pBu = GetIntArrayBuffer(Arg.GetvI());
		memcpy((char*)pResult,pBu,strlen(pBu));
		delete[] pBu;
		pResultType[0] = (unsigned char)ARG_DATA_VECTORINT;
		break;
	case CLVT_MSS:
		pBu = GetStringMapArrayBuffer(Arg.GetmSS());
		memcpy((char*)pResult,pBu,strlen(pBu));
		pResultType[0] = (unsigned char)ARG_DATA_MAPSS;
		break;
	case CLVT_MSI:
		pBu = GetStringIntMapArrayBuffer(Arg.GetmSI());
		memcpy((char*)pResult,pBu,strlen(pBu));
		pResultType[0] = (unsigned char)ARG_DATA_MAPSI;
		break;
	case CLVT_NON:
		sprintf(pResult,"%d",0);
		pResultType[0] = (unsigned char)ARG_DATA_EMPTY;
		break;
	default:
		return false;
	}

	return true;
}
CClArg* ProcDataAdapter::ConvertStringToArg(const char* pType,const char* Arg)
{

	CClArg* pArg;

	char stype = *pType;

	int nArg = 0;

	float fArg = 0.0f;

	string strArg;

	unsigned int unI = 0;

	unsigned long uL = 0;

	vector<int> vVec;

	map<string,string> vMap;

	map<string,int> viMap;

	string strTemp;
	switch(stype)
	{
	case ARG_DATA_INT:
		nArg = atoi((const char*)Arg);
		pArg = new CClArg(nArg);
		break;
	case ARG_DATA_FLOAT:
		fArg = (float)atof((const char*)Arg);
		pArg = new CClArg(fArg);
		break;
	case ARG_DATA_STRING:
		strArg = string((char*)Arg);
		pArg = new CClArg(base64_decode(strArg));
		break;
	case ARG_DATA_UINT:
		unI = (unsigned int)atoi((const char*)Arg);
		pArg = new CClArg(unI);
		break;
	case ARG_DATA_VECTORINT:
		GetIntArray((const char*)Arg,vVec);
		pArg = new CClArg(vVec);
		break;
	case ARG_DATA_MAPSS:
		GetStringMapArray((const char*)Arg,vMap);
		pArg = new CClArg(vMap);
		break;
	case ARG_DATA_ULONG:
		uL = (unsigned long)atol((const char*)Arg);
		pArg = new CClArg(uL);
		break;
	case ARG_DATA_MAPSI:
		GetStringIntMapArray((const char*)Arg,viMap);
		pArg = new CClArg(viMap);
		break;
	case ARG_DATA_EMPTY:
		pArg = new CClArg();
		break;
	default:
		pArg = (CClArg*)0;
	}

	return pArg;
}

char* ProcDataAdapter::GetPrifixWithDelimiter(char* pBuffer,const char* cprefix)
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

bool ProcDataAdapter::GetStringIntMapArray(const char* pBuffer,map<string,int>& vmap)
{

	char* pB = (char*)pBuffer;

	bool bEnd = false;

	int nMax =strlen(pBuffer);

	int nIndex = 0;

	char* pPos1;
	char* pPos2;

	char sFirst[255];
	char sSecond[1024];

	int nCurrentLen =0;
	while(!bEnd)
	{
		char* r = GetPrifixWithDelimiter(pB,";");

		nCurrentLen += strlen(r) +1;

		memset(sFirst,0,255);
		memset(sSecond,0,1024);

		pPos1 = strstr(r ,"[");

		pPos2 = strstr(r ,"]");

		int nLenFirst = (pPos1 - r);
		int nLenSecond = (pPos2 - pPos1) -1;

		memcpy(sFirst,r,nLenFirst);
		memcpy(sSecond,pPos1+1,nLenSecond);

		pair<std::string,int> paireData = pair<std::string,int>(base64_decode(string(sFirst)),atoi(sSecond));

		vmap.insert(paireData);

		pB = pB+(nLenFirst + nLenSecond + 3);

		if(nCurrentLen >=nMax)
		{
			bEnd = true;
		}
	}
	return true;
}

bool ProcDataAdapter::GetStringMapArray(const char* pBuffer,map<string,string>& vmap)
{

	char* pB = (char*)pBuffer;

	bool bEnd = false;

	int nMax =strlen(pBuffer);

	int nIndex = 0;

	char* pPos1;
	char* pPos2;

	char sFirst[255];
	char sSecond[1024];

	int nCurrentLen =0;
	while(!bEnd)
	{
		char* r = GetPrifixWithDelimiter(pB,";");

		nCurrentLen += strlen(r) +1;

		memset(sFirst,0,255);
		memset(sSecond,0,1024);

		pPos1 = strstr(r ,"[");

		pPos2 = strstr(r ,"]");

		int nLenFirst = (pPos1 - r);
		int nLenSecond = (pPos2 - pPos1) -1;

		memcpy(sFirst,r,nLenFirst);
		memcpy(sSecond,pPos1+1,nLenSecond);

		pair<std::string,std::string> paireData = pair<std::string,std::string>(base64_decode(string(sFirst)),base64_decode(string(sSecond)));

		vmap.insert(paireData);

		pB = pB+(nLenFirst + nLenSecond + 3);

		if(nCurrentLen >=nMax)
		{
			bEnd = true;
		}
	}
	return true;
}

bool ProcDataAdapter::GetIntArray(const char* pBuffer,vector<int>& vec)
{
	char* pB = (char*)pBuffer;

	bool bEnd = false;

	int nMax =(int)strlen(pBuffer);

	int nIndex = 0;

	while(!bEnd)
	{
		char* r = GetPrifixWithDelimiter(pB,";");

		int nVal = atoi(r);

		int nLen = (int)strlen(r);

		int nRemainLen =(int)strlen(pB + nLen);

		if(nRemainLen <= 0)
		{
			bEnd = true;	
		}
		else
		{
			pB = pB + (nLen+1);
		}

		if(r)
		{
			vec.push_back(nVal);
		}
	}

	return true;
}

char* ProcDataAdapter::GetIntArrayBuffer(vector<int> VecInt)
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

	char* cResult = new char[strtemp.length()+1];

	memset(cResult,0,strtemp.length()+1);

	memcpy(cResult,strtemp.c_str(),strtemp.length());

	return cResult;
}

char* ProcDataAdapter::GetStringIntMapArrayBuffer(map<string,int> srtMap)
{

	map<string,int>::iterator itor = srtMap.begin();
	char temp[1024];
	memset(temp,0,1024);

	string strtemp;
	string strftemp;

	bool bFirst = true;
	for(;itor != srtMap.end() ; itor++)
	{
		if(!bFirst)
		{
			strtemp += ";";
		}
		bFirst = false;

		strftemp = base64_encode((unsigned char*)itor->first.c_str(),itor->first.length());
		sprintf(temp,"%s[%d]",strftemp.c_str(),itor->second);

		strtemp += temp;
		memset(temp,0,1024);	
	}
	
	char* cResult = new char[strtemp.length()+1];

	memset(cResult,0,strtemp.length()+1);

	memcpy(cResult,strtemp.c_str(),strtemp.length());

	return cResult;
}

char* ProcDataAdapter::GetStringMapArrayBuffer(map<string,string> srtMap)
{

	map<string,string>::iterator itor = srtMap.begin();
	char temp[1024];
	memset(temp,0,1024);

	string strtemp;
	string strFirsttemp;
	string strSecondtemp;


	bool bFirst = true;
	for(;itor != srtMap.end() ; itor++)
	{
		if(!bFirst)
		{
			strtemp += ";";
		}
		bFirst = false;
		strFirsttemp = base64_encode((unsigned char*)itor->first.c_str(),itor->first.length());
		strSecondtemp = base64_encode((unsigned char*)itor->second.c_str(),itor->second.length());

		sprintf(temp,"%s[%s]",strFirsttemp.c_str(),strSecondtemp.c_str());

		strtemp += temp;
		memset(temp,0,1024);	
	}

	char* cResult = new char[strtemp.length()+1];

	memset(cResult,0,strtemp.length()+1);

	memcpy(cResult,strtemp.c_str(),strtemp.length());

	return cResult;
}
