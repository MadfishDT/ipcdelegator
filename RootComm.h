#ifndef  _RootComm_H
#define  _RootComm_H

#include "IPCRepresent.h"
#include "iObject_glue.h"
#include "ProcParser.h"
#include "ProcPackage.h"
#include "ObjectBinderFactory.h"
#include "IPCDelegatorCore.h"
#include <string>

using namespace std;

class RootComm
{
private:

	RootComm(void);
	~RootComm(void);

public:
	static RootComm* getInstance()
	{
		static RootComm* obj;

		if(!obj)
		{
			obj = new RootComm();
		}

		return obj;
	}


	iObject_glue* CreateCommObject(string strName);
	
	void StartServerType(bool bCreateNew);
	
	void StartClientType(bool bCreateNew);

	void Stop();
	ObjectBinderFactory* GetFactory();
private:
	
	IPCDelegatorCore* m_pCore;
};
#endif