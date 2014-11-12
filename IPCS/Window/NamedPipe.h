#ifndef _NamedPipe_H
#define  _NamedPipe_H

#define NP_MAX_BUFFERSIZE 1024
#include "windows.h"
#include "../IPCCom.h"
class NamedPipe : public IPCCom
{
public:
	NamedPipe(void);
	~NamedPipe(void);

	virtual bool Create();
	virtual bool ConnectClient();
	virtual bool DisconnectClient();

	virtual bool Open();

	virtual bool Write(char* lpBuffer, unsigned long nBufferLen);

	virtual unsigned long Read(char* lpBuffer);

private:
	HANDLE m_hPipe;
};
#endif