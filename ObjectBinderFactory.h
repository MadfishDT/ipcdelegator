#ifndef  _ObjectBinderFactory_H
#define  _ObjectBinderFactory_H

class RPCObjectBinder;

#include "ProcPackage.h"
#include <list>
using namespace std;
/*this is client model process can be used*/
class IPCDelegatorCore;

class ObjectBinderFactory
{
public:
	static ObjectBinderFactory* getInstance()
	{
		static ObjectBinderFactory* pObj;
		if(!pObj)
		{
			pObj = new ObjectBinderFactory();
		}
		return pObj;
	}

	ObjectBinderFactory(void);

	~ObjectBinderFactory(void);

	RPCObjectBinder* RequestObject(string strObjectName);
	RPCObjectBinder* FindObject(unsigned long nAddress);

	void RemoveObject(string strObjectName , unsigned long nAddress);
	void AddObject(string strObjectName , unsigned long nAddress);

private:
	
	ProcPackage m_Package;

	RPCObjectBinder* m_LastObjBinder;

	list<RPCObjectBinder*> m_ObjectList;

	IPCDelegatorCore* m_pCore;
};
#endif