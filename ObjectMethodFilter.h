#ifndef  _ObjectMethodFilter_H
#define  _ObjectMethodFilter_H

#include <string>
#include "ClArgList.h"

using namespace std;

class ObjectMathodMap;

class ObjectMethodFilter
{
public:
	
	ObjectMethodFilter(void);

	~ObjectMethodFilter(void);

	void SetCapture();

	void PullObject(char* ObjAddress, char* Object,char* Method, char* result , char* resulttype);
	void PullResult(CClArg& Arg);

	void PutObject(const char* ObjAddress, const char* Object);

	/*Arg can be const char*, vector<int>, map<string,string>
	  ARG_DATA_INT
	  ARG_DATA_FLOAT
	  ARG_DATA_STRING
	  ARG_DATA_UINT are represented const char(string value)
	  ARG_DATA_VECTORINT is represented vector*
	  ARG_DATA_MAPSS is represented map*
	*/

	void PutArg(CClArg& Arg);

	void PutResult(const char* type);

	bool Excute(const char* Method);

	void ReleaseCapture();

	void RequestObject(const char* ObjName);

private:
	char* GetPrifixWithDelimiter(char* pBuffer,const char* cprefix);

	const char* GetIntArrayBuffer(vector<int>& VecInt);
	const char* GetStringMapArrayBuffer(map<string,string>& srtMap);



	bool m_bCapture;

	ObjectMathodMap* m_OMMap;

	string m_strObject;

	bool m_bResult;

	string m_strMethod;

	string m_strResultType;

	unsigned long m_Address;

	CClArgList* m_pAlgList;

};
#endif