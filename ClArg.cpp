
#include "stdinc.h"
#include "ClArg.h"


void CClArg::InitVal()
{
	m_iVal = 0;

	m_fVal = 0.0f;

	m_nUI = 0;

	m_UL = 0;

	m_nID = CLVT_NON;
}
CClArg::~CClArg(void)
{
}
CClArg::CClArg()
{
	InitVal();
}
CClArg::CClArg(int val)
{
	InitVal();
	m_iVal = val;
	m_nID = CLVT_I;
}

CClArg::CClArg(float val)
{
	InitVal();
	m_fVal = val;
	m_nID = CLVT_F;
}

CClArg::CClArg(string strval)
{
	InitVal();
	m_strVal = strval;
	m_nID = CLVT_S;
}

CClArg::CClArg(unsigned int val)
{
	InitVal();
	m_nUI = val;
	m_nID = CLVT_UI;
}

CClArg::CClArg(vector<int>& vecInt)
{
	InitVal();
	m_vecInit = vecInt;
	m_nID = CLVT_VI;
}

CClArg::CClArg(map<string,string>& mapSS)
{
	InitVal();
	m_mapSS = mapSS;
	m_nID = CLVT_MSS;
}

CClArg::CClArg(map<string,int>& mapSI)
{
	InitVal();
	m_mapSI = mapSI;
	m_nID = CLVT_MSI;
}

CClArg::CClArg(unsigned long val)
{
	InitVal();
	m_UL = val;
	m_nID = CLVT_UL;

}

void CClArg::operator=(CClArg p)
{
	m_iVal = p.GetiVal();

	m_fVal = p.GetfVal();

	m_strVal = p.GetsVal();

	m_nUI = p.GetUI();

	m_vecInit = p.GetvI();

	m_mapSS = p.GetmSS();

	m_nID = p.GetType();

	m_UL = p.GetUL();

	m_mapSI = p.GetmSI();
}

int CClArg::GetType()
{
	return m_nID;
}

