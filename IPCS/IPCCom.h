#ifndef _IPCCom_H
#define  _IPCCom_H


#define IPCCOM_MAX_BUFFERSIZE 4096

typedef void (*FnProc)(void* p);

class IPCCom
{
public:
	
	IPCCom(void);
	~IPCCom(void);

	virtual bool Create() = 0;
	virtual bool ConnectClient() = 0;

	virtual bool DisconnectClient() = 0;

	virtual bool Open() = 0;

	virtual bool Write(char* lpBuffer, unsigned long nBufferLen) = 0;

	virtual unsigned long Read(char* lpBuffer) = 0;

	virtual bool SetData(void* p) = 0;

	virtual bool SetProcRead(FnProc pFN) = 0;
	virtual bool SetProcConnect(FnProc pFN) = 0;
	virtual bool SetProcDisconnect(FnProc pFN) = 0;
	
	virtual char* GetLastBuffer() = 0;
	virtual unsigned GetLastBufferLength() = 0;

};
#endif
