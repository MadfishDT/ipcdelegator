#include "stdinc.h"
#include "ObjectBinderFactory.h"
#include "RPCObjectBinder.h"
#include "IPCDelegatorCore.h"
ObjectBinderFactory::ObjectBinderFactory(void)
{
	
}

ObjectBinderFactory::~ObjectBinderFactory(void)
{

}
RPCObjectBinder* ObjectBinderFactory::FindObject(unsigned long nAddress)
{
	list<RPCObjectBinder*>::iterator itor = m_ObjectList.begin();

	RPCObjectBinder* pTemp;

	for(;itor != m_ObjectList.end() ; itor++)
	{
		pTemp = (*itor);

		if(pTemp->GetAddress() == nAddress)
		{	
			return pTemp;
		}
	}
}

void ObjectBinderFactory::RemoveObject(string strObjectName , unsigned long nAddress)
{
	list<RPCObjectBinder*>::iterator itor = m_ObjectList.begin();
	RPCObjectBinder* pTemp;
	for(;itor != m_ObjectList.end() ; itor++)
	{
		pTemp = (*itor);

		if(pTemp->GetAddress() == nAddress)
		{	
			m_ObjectList.erase(itor);
			delete pTemp;
			return;
		}
	}
}

void ObjectBinderFactory::AddObject(string strObjectName , unsigned long nAddress)
{
	RPCObjectBinder* pObject = new RPCObjectBinder(strObjectName,nAddress);
	m_LastObjBinder = pObject;
	m_ObjectList.push_back(pObject);
}


RPCObjectBinder* ObjectBinderFactory::RequestObject(string strObjectName)
{	
	if(IPCDelegatorCore::getInstance()->PK_RequestObject(strObjectName))
	{
		return m_LastObjBinder;
	}
	return (RPCObjectBinder*)0;
}