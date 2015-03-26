#include "StdAfx.h"
#include "AGuiSocketListen.h"


CAGuiSocketListen::CAGuiSocketListen(void)
{
}


CAGuiSocketListen::~CAGuiSocketListen(void)
{
}

void CAGuiSocketListen::OnRcvServerMsg(uint16 cmd,uint32 uin,CPacketDataIn &in)
{
	switch(cmd)
	{
	case UDP_LOGIN:
		OnRcvSvrLogin(in);
		break;
	default:
		break;
	}
}

void CAGuiSocketListen::OnConnect(bool success)
{
	if(success)
	{
		printf("login to server success!!!!!!!!!!!!!!!!!\n");
	}
	else
	{
		printf("login to server fail!!!!!!!!!!!!!!!!!\n");
	}
}

void CAGuiSocketListen::OnRcvSvrLogin(CPacketDataIn &in)
{
	uint32 a,b,c;
	in >> c >> a >> b;
	printf("login:a=%d,b=%d,c=%d\n",a,b,c);
}