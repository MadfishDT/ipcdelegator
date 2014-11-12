#include "../../stdinc.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "MessageQue.h"



	
MessageQue::MessageQue(void)
{

}

MessageQue::~MessageQue(void)
{

}

bool MessageQue::Create()
{

	key_t rkey;

	rkey = MESSAGE_F_KEY;
	m_nSendType = MESSAGE_F_TYPE;
	m_nReceiveType = MESSAGE_W_TYPE;

	m_nMessageQID = msgget(rkey,  IPC_CREAT | 0666);

	perror("MessageQue::Create start");
	if(m_nMessageQID < 0)
	{
		perror("MessageQue::Create fail");
		return false;
	}
	return true;
}

bool MessageQue::Open()
{
	key_t rkey;

	rkey = MESSAGE_F_KEY;
	m_nSendType = MESSAGE_W_TYPE;
	m_nReceiveType = MESSAGE_F_TYPE;

	m_nMessageQID = msgget(rkey,  IPC_CREAT | 0666);
	
	if(m_nMessageQID < 0)
	{
		perror("MessageQue::Open Error");
		return false;
	}
	perror("MessageQue::Open success");
	return true;
}

bool MessageQue::ConnectClient()
{
	return true;
}

bool MessageQue::DisconnectClient()
{

	return true;
}


bool MessageQue::Write(char* lpBuffer, unsigned long nBufferLen)
{

	MsgType msg;
	msg.mtype = m_nSendType;
	
	int msg_size = sizeof(msg) - sizeof(msg.mtype);

	memset(msg.mtext,0,MESAGEQ_MAX_BUFFERSIZE);	
	memcpy(msg.mtext, lpBuffer,nBufferLen);
	
	 if(msgsnd(m_nMessageQID,&msg,msg_size,0)==-1)
	{
		return false;
         }
	return true;
}

unsigned long MessageQue::Read(char* lpBuffer)
{

	MsgType msg;
	
	int msg_size = sizeof(msg) - sizeof(msg.mtype);
	
	int nbytes =  msgrcv(m_nMessageQID, &msg, msg_size, m_nReceiveType, MSG_NOERROR);

	if(nbytes < 0)
	{
		perror("MessageQue::ReadData fail");
		return 0;
        }
	
	memcpy(lpBuffer,msg.mtext,nbytes);

	
	return (unsigned long)nbytes;

}
