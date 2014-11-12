#include "stdinc.h"
#include "ProcPackage.h"


#define PACKAGE_TAG_OUT_FORMAT  "#out=\"%lu:%s\""
#define PACKAGE_TAG_OBJECTMETHODCALL_FORMAT  "#object=\"%lu:%s\"\n#method = \"%s\"\n%s\n"
#define PACKAGE_TAG_PARAM_FORMAT  "#param=\"%s:%s\"\n"
#define PACKAGE_TAG_OBJECTMETHOD_FORMAT  "#ret_object=\"%s:%s\"\n#method = \"%s\"\n#result=\"%s:%s\""
#define PACKAGE_TAG_REQOBJECT_FORMAT  "#request = \"%s\""



ProcPackage::ProcPackage(void)
{
	std::map<string,string> strMap;
	pair<std::string,std::string> A = pair<std::string,std::string>("SDASDFA","AWEFWEF");
	strMap.insert(A);
}

ProcPackage::~ProcPackage(void)
{

}


bool ProcPackage::GetReqMethodPackage(const char* strName, unsigned long nAddress,const char* strMethodName,char* strArgs, char* pOut, unsigned int& nLen/*in and out*/)
{

	memset(pOut,0,nLen);

	sprintf(pOut,PACKAGE_TAG_OBJECTMETHODCALL_FORMAT,nAddress,strName,strMethodName,strArgs);

	nLen = (int)strlen(pOut);

	return true;
}

bool ProcPackage::GetResMethodPackage(const char* strName, const char* strAddress,const char* strMethodName, const char* strResultType,const char* strResult, char* pOut, unsigned int& nLen/*in and out*/)
{

	memset(pOut,0,nLen);
	sprintf(pOut,PACKAGE_TAG_OBJECTMETHOD_FORMAT,strAddress,strName,strMethodName,strResultType,strResult);
	nLen = (int)strlen(pOut);
	return true;

}

bool ProcPackage::GetReqObjectPackage(const char* strName,char* pOut,unsigned int& nLen)
{

	memset(pOut,0,nLen);
	sprintf(pOut,PACKAGE_TAG_REQOBJECT_FORMAT,strName);
	nLen = (int)strlen(pOut);
	return true;

}

bool ProcPackage::GetResObjectPackage(const char* strName, unsigned long nAddress,char* pOut, unsigned int& nLen)
{

	memset(pOut,0,nLen);
	sprintf(pOut,PACKAGE_TAG_OUT_FORMAT,nAddress,strName);
	nLen = (int)strlen(pOut);
	return true;

}
