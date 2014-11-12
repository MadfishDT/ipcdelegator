#include "../../stdinc.h"
#include "NamedPipe.h"

NamedPipe::NamedPipe(void)
{

}

NamedPipe::~NamedPipe(void)
{

}



bool NamedPipe::Create()
{

	m_hPipe = ::CreateNamedPipe(_T("\\\\.\\PIPE\\methoddelegator"),PIPE_ACCESS_DUPLEX,PIPE_TYPE_MESSAGE | PIPE_WAIT,PIPE_UNLIMITED_INSTANCES,NP_MAX_BUFFERSIZE,NP_MAX_BUFFERSIZE,0,NULL);

	if(m_hPipe == INVALID_HANDLE_VALUE )
	{
		return false;
	}
	return true;
}

bool NamedPipe::Open()
{

	m_hPipe = CreateFile(_T("\\\\.\\PIPE\\methoddelegator"), PIPE_ACCESS_DUPLEX, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (m_hPipe == INVALID_HANDLE_VALUE)
	{
		return false;
	}
	return true;
}

bool NamedPipe::ConnectClient()
{

	if (!ConnectNamedPipe(m_hPipe, NULL))
	{
		return false;
	}

	return true;
}

bool NamedPipe::DisconnectClient()
{


	if (!::DisconnectNamedPipe(m_hPipe))
	{
		return false;
	}

	CloseHandle(m_hPipe);

	return true;
}


bool NamedPipe::Write(char* lpBuffer, unsigned long nBufferLen)
{
	
	if (!::WriteFile(m_hPipe, lpBuffer, nBufferLen,&nBufferLen, NULL))
	{
		return false;	
	}
	
	return true;
}

unsigned long NamedPipe::Read(char* lpBuffer)
{
	
	unsigned long  nReadSize = 0;
	if (!::ReadFile(m_hPipe, lpBuffer, NP_MAX_BUFFERSIZE, &nReadSize, NULL))
	{
		return 0;
	}

	return nReadSize;
}