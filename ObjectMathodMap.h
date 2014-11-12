#ifndef  _ObjectMathodMap_H
#define  _ObjectMathodMap_H

#include <map>
#include <list>
#include <string>

#include "MathodDelegator.h"

using namespace std;

class ObjectMathodMap
{
public:

	static ObjectMathodMap* getInstance()
	{
		static ObjectMathodMap* pObj;
		if(!pObj)
		{
			pObj = new 	ObjectMathodMap();
		}


		return pObj;
	}

	ObjectMathodMap(void);

	~ObjectMathodMap(void);

	void AddMethodDelegator(MathodDelegator* pD);
	
	MathodDelegator* GetMathodDelegator(string strName, unsigned long unID);

	bool ExcuteMethod(MathodDelegator* pDg, string strMethod, CClArgList& Args,bool bResultVal);


private:

	list<MathodDelegator*> m_MathodDelegatorList;
};
#endif