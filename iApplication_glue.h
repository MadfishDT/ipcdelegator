#pragma once

#include "ClArgList.h"
#include "iObject_glue.h"
class iApplication_glue : public iObject_glue
{
public:

	iApplication_glue(void);

	~iApplication_glue(void);

public:
	void iCreateApplication(CClArgList& Arg);
	
	void iShow(CClArgList& Arg);
	
	void iGetID(CClArgList& Arg);

	void UIntParam(CClArgList& Args);

	void ULongParam(CClArgList& Args);

	void MapIntStringParam(CClArgList& Args);

	void NoParamNoReturn(CClArgList& Args);
};
