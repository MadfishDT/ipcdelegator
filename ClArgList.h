#ifndef _CClArgList_H
#define  _CClArgList_H

#include "ClArg.h"
#include <string>

using namespace std;

class CClArgList
{
public:
	CClArgList(void);

	~CClArgList(void);

	void operator <<(int& t1);
	void operator <<(float& t1);
	void operator <<(string& t1);
	void operator <<(vector<int>& t1);
	void operator <<(unsigned int& t1);
	void operator <<(unsigned long& t1);
	void operator <<(map<string,int>& t1);
	void operator <<(map<string,string>& t1);

	void operator >>(int t1);
	void operator >>(float t1);
	void operator >>(string t1);
	void operator >>(unsigned int t1);
	void operator >>(unsigned long t1);
	void operator >>(vector<int>& t1);
	void operator >>(map<string,int>& t1);
	void operator >>(map<string,string>& t1);

	CClArg& GetArg(int index);
	void AddArg(CClArg& Arg);

	int GetLength();
	
	void ClearAll();

private:
	vector<CClArg> m_ArgVec;

};
#endif