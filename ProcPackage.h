#ifndef  _ProcPackage_H
#define  _ProcPackage_H

#include <string>
#include "ClArgList.h"
#include "ProcDefine.h"

using namespace std;

class ProcPackage
{
public:
	ProcPackage(void);
	~ProcPackage(void);

public:
	//bool GetReqMethodPackage(const char* strName, unsigned long strAddress,const char* strMethodName,CClArgList& Args, char* pOut, unsigned int& nLen/*in and out*/);
	bool GetReqMethodPackage(const char* strName, unsigned long nAddress,const char* strMethodName,char* strArgs, char* pOut, unsigned int& nLen/*in and out*/);
	bool GetResMethodPackage(const char* strName, const char* strAddress,const char* strMethodName, const char* strResultType,const char* strResult, char* pOut, unsigned int& nLen);
	bool GetReqObjectPackage(const char* strName,char* pOut,unsigned int& nLen);
	bool GetResObjectPackage(const char* strName, unsigned long nAddress,char* pOut, unsigned int& nLen);

	

};
#endif