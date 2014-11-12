#ifndef _CClArg_H
#define  _CClArg_H

#include <string>
#include <vector>
#include <map>

using namespace std;


#define CLVT_I 0	 /*int*/
#define CLVT_UI 1    /*unsigned int*/
#define CLVT_UL 2 /*unsigned int 32*/
#define CLVT_UI_64 3 /*unsigned int 64*/
#define CLVT_F 4  /*float*/
#define CLVT_S 5  /*string*/
#define CLVT_B 6  /*bool*/
#define CLVT_VI 7 /*vector int*/
#define CLVT_MSS 8 /*map string,string*/
#define CLVT_MSI 9 /*map string,int*/

#define CLVT_NON 444 /*map string,string*/

class CClArg
{
public:

	CClArg();

	CClArg(int val);

	CClArg(float val);

	CClArg(string strval);

	CClArg(unsigned int val);

	CClArg(unsigned long val);

	CClArg(vector<int>& vecInt);

	CClArg(map<string,string>& mapSS);
	
	CClArg(map<string,int>& mapSI);

	~CClArg(void);

	int GetiVal(){return m_iVal;} 

	float GetfVal(){return m_fVal;}

	string GetsVal(){return m_strVal;}

	unsigned int GetUI(){return m_nUI;}

	unsigned long GetUL(){return m_UL;}

//	uint32_t GetUI32(){return m_nuI32;}

//	uint64_t GetUI64(){return m_nuI32;}

	vector<int> GetvI(){return m_vecInit;}

	map<string,string> GetmSS(){return m_mapSS;}

	map<string,int> GetmSI(){return m_mapSI;}

	int GetType();

	void operator=(CClArg p);
private:
	
	void InitVal();

	int m_iVal;

	float m_fVal;

	string m_strVal;

	unsigned int m_nUI;

	unsigned long m_UL;

//	uint32_t m_nuI32;

//	uint64_t m_nuI64;

	vector<int> m_vecInit;

	map<string,string> m_mapSS;

	map<string,int> m_mapSI;

	unsigned int m_nID;
};
typedef CClArg CLARG;
typedef vector<CClArg> CLARG_LIST;

#endif