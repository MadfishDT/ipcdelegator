#include "stdinc.h"
#include "ObjectMathodMap.h"

ObjectMathodMap::ObjectMathodMap(void)
{
}

ObjectMathodMap::~ObjectMathodMap(void)
{
}

void ObjectMathodMap::AddMethodDelegator(MathodDelegator* pD)
{
	m_MathodDelegatorList.push_back(pD);
}

MathodDelegator* ObjectMathodMap::GetMathodDelegator(string strName, unsigned long unID)
{
	list<MathodDelegator*>::iterator itor;

	MathodDelegator* pMD;

	itor = m_MathodDelegatorList.begin();

	for(;itor != m_MathodDelegatorList.end();itor++)
	{
		pMD = *itor;
		if(!unID)
		{
			if(pMD->GetName() == strName)
			{
				return pMD;
			}
		}
		else
		{
			if(pMD->GetName() == strName && pMD->GetID() == unID)
			{
				return pMD;
			}

		}
	}

	return (MathodDelegator*)0;
}

bool ObjectMathodMap::ExcuteMethod(MathodDelegator* pDg, string strMethod, CClArgList& Args , bool bResultVal)
{
	return pDg->Operation(strMethod,Args,bResultVal);
}


