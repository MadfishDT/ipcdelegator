#include "stdinc.h"
#include "IPCRepresent.h"

IPCRepresent::IPCRepresent(bool bClient, unsigned int nMode)
{
	m_bClient = bClient;
	
	m_nLastError = IPCR_ERROR_UKNOWN;

	if(nMode == IPCR_NAMEDPIPE)
	{
		m_ipc = new NamedPipe();
		m_nMode = IPCR_MODE_PROC;
	}
#ifdef IPCDELECATOR_OS_LINUX
	else if(nMode == IPCR_MESSAGEQUE)
	{  
		m_ipc = new MessageQue();
		m_nMode = IPCR_MODE_PROC;
	}
	else if(nMode == IPCR_WEBSOCKET)
	{
		m_ipc = new WebSocket();
		m_nMode = IPCR_MODE_OWNPROC;

		m_ipc->SetProcRead(ProcCallbacktypeRead);
		m_ipc->SetProcConnect(ProcCallbacktypeConnect);
		m_ipc->SetProcDisconnect(ProcCallbacktypeDisConnect);
	}
	m_ipc->SetData(this);
#endif
}

IPCRepresent::~IPCRepresent(void)
{
	delete m_ipc;
}
void IPCRepresent::RegisterIPCFunc(FnResp fa,FnResp fe)
{
	m_fnAcceptBuffer = fa;
	m_fnExport = fe;
}

FnResp IPCRepresent::GetReponseAcceptProc()
{ 
	return m_fnAcceptBuffer;
}

FnResp IPCRepresent::GetReponseExportProc()
{
	return m_fnExport;
}

void IPCRepresent::SetType(bool bClient)
{
	m_bClient = bClient;
}

/*****************************************************************************
procedure for Communication module that have own event procedure(own thread 
stack for read/write)
******************************************************************************/

void IPCRepresent::ProcCallbacktypeRead(void* pParam)
{
	IPCRepresent* pThis = (IPCRepresent*)pParam;
	pThis->PostOperationCallbackTypeRead();
}	

void IPCRepresent::PostOperationCallbackTypeRead()
{
	perror("IPCRepresent::PostOperationCallbackTypeRead start");

	unsigned char pReadBuffer[IPCR_MAX_BUFFER];

	memset(pReadBuffer,0,IPCR_MAX_BUFFER);

	unsigned int nReadSize = m_ipc->GetLastBufferLength();

	memcpy(pReadBuffer,m_ipc->GetLastBuffer(),nReadSize);

	FnResp Fn = GetReponseAcceptProc();

	(*Fn)(pReadBuffer,nReadSize);

	perror((char*)pReadBuffer);

	perror("IPCRepresent::PostOperationCallbackTypeRead end");
	
}	


void IPCRepresent::ProcCallbacktypeConnect(void* pParam)
{

	IPCRepresent* pThis = (IPCRepresent*)pParam;
}

void IPCRepresent::ProcCallbacktypeDisConnect(void* pParam)
{
	IPCRepresent* pThis = (IPCRepresent*)pParam;
}


unsigned long IPCRepresent::IPCProcReadFunc(void* pParam)
{

	perror("IPCProcFunc::IPCProcReadFunc end");      

	IPCRepresent* pThis = (IPCRepresent*)pParam;

	//pThis->ProcRead();

	return IPCR_SUCESS;
}

unsigned long IPCRepresent::IPCProcConnectFunc(void* pParam)
{

	perror("IPCProcFunc::run end");      

	IPCRepresent* pThis = (IPCRepresent*)pParam;

	if(pThis->GetMode() == IPCR_MODE_PROC)
	{
		pThis->ProcIPC();
	}
	else
	{
		pThis->OwnProcIPC();		
	}

	return IPCR_SUCESS;
}


void IPCRepresent::OwnProcIPC()
{
	/*Own Procedure Communication module have own Thread Running Demon module
	so, IPCRepresent should not care about connect, read thread management.
	IPCRepresent just get result from module*/

	if(m_ipc->Create())
	{
		Connect();
	}
}
/*****************************************************************************/

void IPCRepresent::ProcIPC()
{
	if(m_bClient)
	{	
		if(m_ipc->Open())
		{
			m_nLastError = ClientProc();	
		}
	}
	else
	{	
		if(m_ipc->Create())
		{
			m_nLastError = ServerProc();
		}
	}
	m_nLastError = IPCR_ERROR_UKNOWN;
}


unsigned long IPCRepresent::ServerProc()
{
	unsigned char pBuffer[IPCR_MAX_BUFFER];
	bool bConnected = false;
	bool bRead = true;
	int nReadSize = 0;

	int nConnectionCount = 0;
	

	while(true)
	{

		bConnected = Connect();

		if(bConnected)
		{
				
			while(bRead)
			{
				nReadSize = Read(pBuffer);
				if(nReadSize == 0)
				{
					bRead = false;

					bConnected = false;
					
					return IPCR_ERROR_LOST; 
				}
				else
				{
					(*m_fnAcceptBuffer)(pBuffer,nReadSize);
				}
				
			}
		}

		nConnectionCount ++;

		if(IPCR_MAX_CHANCE < nConnectionCount)
		{
			return IPCR_ERROR_TIMEOUT;
		}
	}	

	return IPCR_ERROR_UKNOWN;

}

unsigned long IPCRepresent::ClientProc()
{
	
	bool bConnected = false;

	bConnected = Connect();

	return 0;
}

unsigned long IPCRepresent::GetLastError()
{
	return m_nLastError;
}


bool IPCRepresent::Restore()
{

	return Init();
}

bool IPCRepresent::Init()
{
	m_ipc->DisconnectClient();

	m_TrdConnection.RegisterThreadFunc(IPCRepresent::IPCProcConnectFunc,(void*)this);
	m_TrdConnection.MakeThread();
	
	return true;
}

bool IPCRepresent::Connect()
{
	return m_ipc->ConnectClient();
}

bool IPCRepresent::Disconnect()
{
	return m_ipc->DisconnectClient();
}

int IPCRepresent::Read(unsigned char* pBuffer/*out param*/)
{
	return m_ipc->Read((char*)pBuffer);
}

bool IPCRepresent::Write(unsigned char* pBuffer/*in param*/,unsigned int nLen)
{
	m_ipc->Write((char*)pBuffer,nLen);
	
	if(GetMode() == IPCR_MODE_PROC)
	{
		bool bRead = true;
		int nReadSize = 0;
		unsigned char pReadBuffer[IPCR_MAX_BUFFER];
		/*client seq write->read, sync call*/
		if(m_bClient)
		{	
			nReadSize = m_ipc->Read((char*)pReadBuffer);
			if(nReadSize)
			{
				(*m_fnAcceptBuffer)(pReadBuffer,nReadSize);/*notification Read Data to Root*/
			}
			else
			{
				return false;
			}
		}
	}
	return true;
}

