#include "../../stdinc.h"
#include <fcntl.h>
#include "NamedPipe.h"


#define FIFO_FILE_FNAME  "//opt/fifo/methoddelegatorf"
#define FIFO_FILE_WNAME  "//opt/fifo/methoddelegatorw"

NamedPipe::NamedPipe(void)
{

}

NamedPipe::~NamedPipe(void)
{

}

bool NamedPipe::Create()
{
	perror("NamedPipe::Create");
	
	mkfifo(FIFO_FILE_FNAME, 0666) ;/*read only*/
	mkfifo(FIFO_FILE_WNAME, 0666) ;/*write only*/
	
	m_nfFile = open(FIFO_FILE_FNAME,O_RDWR);
	m_nwFile = open(FIFO_FILE_WNAME,O_RDWR);

	perror("NamedPipe::open");

	if(m_nfFile < 0 || m_nwFile < 0)
	{
		return false;
	}
	return true;
}

bool NamedPipe::Open()
{
	m_nwFile = open(FIFO_FILE_FNAME,O_RDWR);
	m_nfFile = open(FIFO_FILE_WNAME,O_RDWR);
		
	if(m_nfFile < 0 || m_nwFile < 0)
	{
	
		return false;
	}
	return true;
}

bool NamedPipe::ConnectClient()
{
	return true;
}

bool NamedPipe::DisconnectClient()
{
	close(m_nwFile);
	close(m_nfFile);
	return true;
}


bool NamedPipe::Write(char* lpBuffer, unsigned long nBufferLen)
{
	 if(write(m_nwFile, lpBuffer, nBufferLen)==-1)
	{
		return false;
         }
	return true;
}

unsigned long NamedPipe::Read(char* lpBuffer)
{

	unsigned long  nReadSize = 0;
	if((nReadSize = read(m_nfFile, lpBuffer, NP_MAX_BUFFERSIZE)) < 0 )
	{
		return 0;
        }
	return nReadSize;

}
