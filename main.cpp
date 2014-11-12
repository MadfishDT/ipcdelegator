#include "stdinc.h"
#include "RootComm.h"
#include <iostream>

using namespace std;
int main()
{


	RootComm* pR = RootComm::getInstance();

	pR->StartServerType(false);

	int nRet =0;
	cin>>nRet;
	perror("main end");
	return 0;
}
