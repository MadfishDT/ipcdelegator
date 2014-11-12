#include "stdinc.h"
#include "MathodDelegator.h"
#include "ObjectMathodMap.h"
MathodDelegator::MathodDelegator(void)
{
	ObjectMathodMap::getInstance()->AddMethodDelegator(this);
}

MathodDelegator::~MathodDelegator(void)
{

}

bool MathodDelegator::Operation(string strfnName, CClArgList& args, bool bResultVal)
{
	map<string,type_symbol_method>::iterator itor;
	
	CClArgList retArgs;

	itor = m_MethodMap.find(strfnName);

	if(itor != m_MethodMap.end())
	{
		type_symbol_method data = itor->second;
		
		data(args);
		
		if(bResultVal)
		{
			
		}
		
		return true;
	}
	return false;
}

void MathodDelegator::RegisterMethod(string strfnName,type_symbol_method MethodDelegator)
{
	m_MethodMap.insert(pair<string,type_symbol_method>(strfnName,MethodDelegator));
}

void MathodDelegator::SetID(unsigned long nID)
{
	m_ID = nID;
}
unsigned long MathodDelegator::GetID()
{
	return m_ID;
}
void MathodDelegator::SetName(string strName)
{
	m_strName = strName;
}
string MathodDelegator::GetName()
{
	return m_strName;
}
