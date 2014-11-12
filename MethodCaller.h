#ifndef  _MethodCaller_H
#define  _MethodCaller_H

#include "ObjectMethodFilter.h"
class MethodCaller
{
public:
	
	MethodCaller(void);
	
	~MethodCaller(void);

	void SetCapture();
	void ReleaseCapture();

	void AddArg(CClArg* Arg);
	
	bool SyncCallMethod(const char* ObjAddress, const char* Object,const char* Method);

	bool AsyncCallMethod(const char* ObjAddress, const char* Object,const char* Method);

	CClArg* GetResult();

private:
	ObjectMethodFilter m_ObjMethodFilter;
	CClArg m_pResult;

};
#endif
