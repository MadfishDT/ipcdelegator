#ifndef  _ProcDataAdapter_H
#define  _ProcDataAdapter_H

#include "ClArgList.h"
#include "MethodDataTypes.h"
#include "ProcDefine.h"

class ProcDataAdapter
{
public:
	ProcDataAdapter(void);
	~ProcDataAdapter(void);
	bool ConvertArgListToString(CClArgList& Args,char* pResult);
	CClArg* ConvertStringToArg(const char* pType,const char* pValue);
	bool ConvertArgToString(CClArg& Arg,char* pResultType,char* pResult);

	bool is_base64(unsigned char c);
	string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
	string base64_decode(std::string const& encoded_string);

private:
	char* GetPrifixWithDelimiter(char* pBuffer,const char* cprefix);
	bool GetStringMapArray(const char* pBuffer,map<string,string>& vec);
	bool GetStringIntMapArray(const char* pBuffer,map<string,int>& vec);
	bool GetIntArray(const char* pBuffer,vector<int>& vec);
	
	char* GetIntArrayBuffer(vector<int> VecInt);

	char* GetStringMapArrayBuffer(map<string,string> srtMap);
	char* GetStringIntMapArrayBuffer(map<string,int> srtMap);


};
#endif