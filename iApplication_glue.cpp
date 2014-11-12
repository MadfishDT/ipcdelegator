#include "stdinc.h"
#include "iApplication_glue.h"
#include <iostream>
iApplication_glue::iApplication_glue(void)
{

	RegisterMethod("CreateApplication",MAKEMETHOD(this,&iApplication_glue::iCreateApplication));
	RegisterMethod("Show",MAKEMETHOD(this,&iApplication_glue::iShow));
	RegisterMethod("GetID",MAKEMETHOD(this,&iApplication_glue::iGetID));
	RegisterMethod("UIntParam",MAKEMETHOD(this,&iApplication_glue::UIntParam));
	RegisterMethod("ULongParam",MAKEMETHOD(this,&iApplication_glue::ULongParam));
	RegisterMethod("MapIntStringParam",MAKEMETHOD(this,&iApplication_glue::MapIntStringParam));
	RegisterMethod("NoParamNoReturn",MAKEMETHOD(this,&iApplication_glue::NoParamNoReturn));

	SetName("application");
}

iApplication_glue::~iApplication_glue(void)
{

}


void iApplication_glue::iCreateApplication(CClArgList& Args)
{
	int arg1;
	float arg2;
	string arg3;
	vector<int> arg4;
	unsigned int arg5;
	unsigned long arg6;

	Args<<arg1;
	Args<<arg2;
	Args<<arg3;
	Args<<arg4;
	Args<<arg5;
	Args<<arg6;

	cout<<"iCreateApplication argument 1 "<<arg1<<endl;
	cout<<"iCreateApplication argument 2"<<arg2<<endl;
	cout<<"iCreateApplication argument 3"<<arg3<<endl;
	
	//CreateApplication();
	cout<<"iApplication_glue::iCreateApplication called"<<endl;
	for(int index = 0 ;  index < (int)arg4.size() ; index++)
	{
		cout<<"iCreateApplication argument Vector Val "<<arg4[index]<<endl;
	}

	cout<<"iCreateApplication argument 5"<<arg5<<endl;
	cout<<"iCreateApplication argument 6"<<arg6<<endl;

	//Args>>string("iCreateApplication return");/*return value*/
	Args>>(int)123456;/*return value*/

}

void iApplication_glue::iShow(CClArgList& Args)
{
	int arg1;
	float arg2;
	string arg3;
	
	vector<int> ret4;
	ret4.push_back(1);
	ret4.push_back(2);
	ret4.push_back(3);
	ret4.push_back(4);
	ret4.push_back(5);
	ret4.push_back(6);


	Args<<arg1;
	Args<<arg2;
	Args<<arg3;
	cout<<"iApplication_glue::iShow called"<<endl;
	Args>>ret4;/*return value*/
}

void iApplication_glue::iGetID(CClArgList& Args)
{
	
	cout<<"iGetID::iShow called"<<endl;
	Args>>(float)0.23f;/*return value*/
}

void iApplication_glue::UIntParam(CClArgList& Args)
{
	unsigned int arg;
	Args<<arg;

	cout<<"iApplication_glue::UIntParam called : "<< arg <<endl;
}

void iApplication_glue::ULongParam(CClArgList& Args)
{
	unsigned long arg;
	Args<<arg;

	cout<<"iApplication_glue::ULongParam called : "<< arg <<endl;

}

void iApplication_glue::MapIntStringParam(CClArgList& Args)
{
	map<string,int> arg;
	Args<<arg;

	cout<<"iApplication_glue::MapIntStringParam called : "<< arg.size() <<endl;
}

void iApplication_glue::NoParamNoReturn(CClArgList& Args)
{

	map<string,int> arg;
	arg.insert(pair<string,int>(string("ABC"),1));
	arg.insert(pair<string,int>(string("B"),2));
	arg.insert(pair<string,int>(string("C"),3));
	arg.insert(pair<string,int>(string("D"),4));

	cout<<"iApplication_glue::NoParamNoReturn called : "<<endl;

	Args>>arg;
}
