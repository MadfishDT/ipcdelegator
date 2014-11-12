#ifndef  _ProcParser_H
#define  _ProcParser_H
/*object = "0x0002342:application"
  method =	"CreateApplication"
  Param ="i:1"
  Param ="f:2"
  Param ="s:index.html"
*/

#include "ObjectMethodFilter.h"
#include "MethodDataTypes.h"

#include "ProcDefine.h"


class ProcParser
{
public:

	ProcParser(void);

	~ProcParser(void);

	void AcceptBuffer(unsigned char* pBuffer,int nLen);	
	unsigned int DoParsing();

	const char* C_Str_GetParsedObjectName();
	const char* C_Str_GetParsedObjectAddress();
	const char* C_Str_GetParsedMethod();
	const char* C_Str_GetParsedResultType();
	const char* C_Str_GetParsedResult();
	const char* C_Str_GetParamtype(int index);
	const char* C_Str_GetParamValue(int index);

	string GetParsedObjectName();
	string GetParsedObjectAddress();
	string GetParsedMethod();
	string GetParsedResultType();
	string GetParsedResult();

	string GetParamtype(int index);
	string GetParamValue(int index);

	unsigned int GetParamSize();
	void ClearBuffer();

private:

	bool ParsingExcutionOperation();
	bool ParsingRequestObject();
	bool ParsingOutObject();
	bool ParsingRetObject();

	char* GetAttribute(char** ppBuffer,const char* pTag);

	char* GetPrifix(char* pBuffer);
	char* GetPrifixWithDelimiter(char* pBuffer,const char* cprefix);
	char* GetPostfixWithDelimiter(char* pBuffer,const char* cprefix);
	char* GetPostfix(char* pBuffer);

	
	unsigned char* m_pBuffer;

	unsigned int m_nLength;

	ObjectMethodFilter m_ObjMethodFilter;

	string m_strObjectName;
	string m_strAddress;
	string m_strMethod;
	string m_strResultType;
	string m_strResult;
	vector<int> m_VecIntArg;
	map<string,string> m_mapStrArg;

	/*type,value*/
	vector<string> m_vecParamTypes;
	vector<string> m_vecParamValues;

};
#endif
