#include "stdinc.h"
#include "iObject_glue.h"


iObject_glue::iObject_glue(void)
{
	m_Md = new MathodDelegator();
	m_address = (unsigned long)(void*)this;
	m_Md->SetID(m_address);
}

iObject_glue::~iObject_glue(void)
{
	delete m_Md;
}
void iObject_glue::SetName(string strname)
{
	m_strName = strname;
	m_Md->SetName(m_strName);
}

void iObject_glue::RegisterMethod(string strname,type_symbol_method fn)
{
	m_Md->RegisterMethod(strname,fn);
}
string iObject_glue::GetName()
{
	return m_strName;

}
unsigned long iObject_glue::GetAddress()
{
	return m_address;

}


