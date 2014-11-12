#include "../../stdinc.h"

#include <fcntl.h>

#include "WebSock.h"
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>


void WebSocket::OnMessage(websocketpp::connection_hdl hdl, server::message_ptr msg) 
{
	perror("start onmessage");
    
    if(!m_pBuffer)
    {
    	delete[]  m_pBuffer;
    }	

    m_pBuffer = new char[WS_MAX_BUFFERSIZE];
	
	memset(m_pBuffer,0,WS_MAX_BUFFERSIZE);

	std::string strmsg = msg->get_payload();

	m_BufferLen = strmsg.length();

	memcpy(m_pBuffer,strmsg.c_str(),m_BufferLen);

	(*m_pReadProc)(m_pData);

	perror("end onmessage");

}

void WebSocket::OnOpen(websocketpp::connection_hdl hdl)
{
	m_HDL = hdl;

	perror("OnOpen start");

	(*m_pConnectProc)(m_pData);

	perror("OnOpen end");
	
}

void WebSocket::OnClose(websocketpp::connection_hdl hdl)
{
	(*m_pDisconnectProc)(m_pData);
}

bool WebSocket::SetProcRead(FnProc pFN)
{
	m_pReadProc = pFN;
}

bool WebSocket::SetProcConnect(FnProc pFN)
{
	m_pConnectProc = pFN;
}
	
bool WebSocket::SetProcDisconnect(FnProc pFN)
{
	m_pDisconnectProc = pFN;
}


WebSocket::WebSocket(void)
{
	m_BufferLen = 0;
	m_pBuffer = (char*)0;
}

WebSocket::~WebSocket(void)
{

}

bool WebSocket::Create()
{
	/*start server proc*/
	perror("WebSocket::Create");

	m_Server.init_asio();

	m_Server.set_open_handler(bind(&WebSocket::OnOpen,this,::_1));

    m_Server.set_close_handler(bind(&WebSocket::OnClose,this,::_1));

  	m_Server.set_message_handler(bind(&WebSocket::OnMessage,this,::_1,::_2));

}

bool WebSocket::Open()
{

}

bool WebSocket::ConnectClient()
{

	m_Server.listen(9002);

    m_Server.start_accept();
	
	m_Server.run();

	return true;
}

bool WebSocket::DisconnectClient()
{
	return true;
}

bool WebSocket::Write(char* lpBuffer, unsigned long nBufferLen)
{
	 std::string steSend = lpBuffer;
	 
	 m_Server.send(m_HDL, steSend,websocketpp::frame::opcode::text);

	 return true;
}

unsigned long WebSocket::Read(char* lpBuffer)
{

	perror("WebSocket::Read start");
	
	boost::unique_lock<boost::mutex> lock(m_mut);

	m_cond.wait(lock);

	memcpy(lpBuffer,m_pBuffer,m_BufferLen);

	delete[] m_pBuffer;

	perror("WebSocket::Read end");
	
	return 0;
}
