#ifndef  _RPCObjectBinder_H
#define  _RPCObjectBinder_H

#include <string>
#include "ClArgList.h"
#include "ProcPackage.h"
using namespace std;

class RPCObjectBinder
{
public:
	
	RPCObjectBinder(string name, unsigned long address);
	RPCObjectBinder(void);


	~RPCObjectBinder(void);

	string GetName();

	unsigned long GetAddress();

	void InvokeCall(string strMethod,CClArgList& args);
	void InvokeCall(string strMethod);
	CClArgList& GetResult();

	void SetResult(CClArg Args);
private:

	string m_strName;

	unsigned long m_nAddress;
	
	ProcPackage m_Package;

	CClArgList m_argRes;
	CClArgList* m_pargRes;

};
#endif