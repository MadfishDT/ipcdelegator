#ifndef _WebSocket_H
#define  _WebSocket_H

#include <unistd.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include "../IPCCom.h"



#define WS_MAX_BUFFERSIZE IPCCOM_MAX_BUFFERSIZE


#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>


typedef websocketpp::server<websocketpp::config::asio> server;


class WebSocket : public IPCCom
{

public:
	WebSocket(void);
	~WebSocket(void);

	virtual bool Create();

	virtual bool ConnectClient();

	virtual bool DisconnectClient();

	virtual bool Open();

	virtual bool Write(char* lpBuffer, unsigned long nBufferLen);

	virtual unsigned long Read(char* lpBuffer);

	void OnMessage(websocketpp::connection_hdl hdl, server::message_ptr msg);

	void OnOpen(websocketpp::connection_hdl hdl);

	void OnClose(websocketpp::connection_hdl hdl);

	virtual bool SetProcRead(FnProc pFN);

	virtual bool SetProcConnect(FnProc pFN);

	virtual bool SetProcDisconnect(FnProc pFN);

	virtual bool SetData(void* p){m_pData = p;}
	
	virtual char* GetLastBuffer(){return m_pBuffer;}
	virtual unsigned GetLastBufferLength(){return m_BufferLen;}

private:

	server m_Server;

	websocketpp::connection_hdl m_HDL;

	boost::condition_variable m_cond;
	
	boost::mutex m_mut;

	void *m_pData;

	char* m_pBuffer;

	unsigned int m_BufferLen;

	FnProc m_pReadProc;
	FnProc m_pConnectProc;
	FnProc m_pDisconnectProc;
	
	//HANDLE m_hPipe;

};
#endif
