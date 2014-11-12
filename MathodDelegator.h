#ifndef _MathodDelegator_H
#define  _MathodDelegator_H

#include <map>
#include "FastDelegate.h"
#include "ClArgList.h"
using namespace std;
using namespace fastdelegate;

typedef FastDelegate1<CClArgList&> type_symbol_method;

class MathodDelegator
{
public:
	MathodDelegator(void);

	~MathodDelegator(void);

	void RegisterMethod(string strfnName,type_symbol_method MethodDelegator);

	void SetID(unsigned long ID);

	unsigned long GetID();

	void SetName(string strName);

	string GetName();

	bool Operation(string strfnName, CClArgList& args, bool bResultVal);

private:

	map<string,type_symbol_method> m_MethodMap;

	unsigned long m_ID;/*instance method id*/

	string m_strName;


};
#endif