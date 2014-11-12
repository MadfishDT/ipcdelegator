
#include "stdinc.h"
#include "ClArgList.h"

CClArgList::CClArgList(void)
{

}

CClArgList::~CClArgList(void)
{
	m_ArgVec.clear();
}

void CClArgList::operator<<(int& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	int val = (*itor).GetiVal();

	t1 = val; 

	m_ArgVec.erase(itor);
}
void CClArgList::operator<<(float& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	float val = (*itor).GetfVal();

	t1 = val; 

	m_ArgVec.erase(itor);
}
void CClArgList::operator<<(string& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	string val = (*itor).GetsVal();

	t1 = val; 

	m_ArgVec.erase(itor);
}
void CClArgList::operator <<(vector<int>& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	t1 = (*itor).GetvI(); 

	m_ArgVec.erase(itor);
}

void CClArgList::operator <<(unsigned int& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	t1 = (*itor).GetUI(); 

	m_ArgVec.erase(itor);
}

void CClArgList::operator <<(unsigned long& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	t1 = (*itor).GetUL(); 

	m_ArgVec.erase(itor);
}

void CClArgList::operator <<(map<string,int>& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	t1 = (*itor).GetmSI(); 

	m_ArgVec.erase(itor);
}

void CClArgList::operator <<(map<string,string>& t1)
{
	vector<CClArg>::iterator itor;

	itor = m_ArgVec.begin();

	t1 = (*itor).GetmSS();

	m_ArgVec.erase(itor);
}

void CClArgList::operator>>(int t1)
{
	CClArg Arg(t1);	
	m_ArgVec.push_back(Arg);

}

void CClArgList::operator>>(float t1)
{
	CClArg Arg(t1);
	m_ArgVec.push_back(Arg);
}

void CClArgList::operator>>(string t1)
{
	CClArg Arg(t1);
	m_ArgVec.push_back(Arg);
}


void CClArgList::operator>>(unsigned int t1)
{
	CClArg Arg(t1);
	m_ArgVec.push_back(Arg);
}


void CClArgList::operator >>(unsigned long t1)
{
	CClArg Arg(t1);
	m_ArgVec.push_back(Arg);
}
void CClArgList::operator >>(map<string,int>& t1)
{
	CClArg Arg(t1);
	m_ArgVec.push_back(Arg);
}

void CClArgList::operator>>(vector<int>& t1)
{
	CClArg Arg(t1);
	m_ArgVec.push_back(Arg);
}

void CClArgList::operator>>(map<string,string>& t1)
{
	CClArg Arg(t1);
	m_ArgVec.push_back(Arg);
}

CClArg& CClArgList::GetArg(int index)
{
	return m_ArgVec[index];

}
int CClArgList::GetLength()
{
	return (int)m_ArgVec.size();
}

void CClArgList::ClearAll()
{
	m_ArgVec.clear();
}

void CClArgList::AddArg(CClArg& Arg)
{
	m_ArgVec.push_back(Arg);
}
