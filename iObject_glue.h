#ifndef  _iObject_glue_H
#define  _iObject_glue_H

#include "ClArgList.h"
#include "FastDelegate.h"
#include "MathodDelegator.h"

using namespace std;
using namespace fastdelegate;

#define MAKEMETHOD MakeDelegate

class MathodDelegator;

class iObject_glue
{
public:

	iObject_glue(void);

	~iObject_glue(void);

	void RegisterMethod(string strname,type_symbol_method fn);

	void SetName(string strname);
	string GetName();
	unsigned long GetAddress();
	MathodDelegator* m_Md;
private:
	string m_strName;
	unsigned long m_address;

};

#endif