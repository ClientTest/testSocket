#pragma once
#include "AGuiSocket2_0/AGuiSocketQuote2_0.h"
#include "AGuiSocket2_0/IAGuiSocketCoreBase2_0.h"

enum {
	UDP_ACK = 1,
	UDP_NEW_UIN,
	UDP_GET_CONTACTLIST,
	UDP_LOGIN,
	UDP_LOGOUT,
	UDP_KEEPALIVE,
	UDP_SHUTDOWN,
};

class CAGuiSocketListen:public IAGuiSocketCoreListen
{
public:
	CAGuiSocketListen(void);
	~CAGuiSocketListen(void);

private:
	void OnRcvSvrLogin(CPacketDataIn &in);

public:
	virtual void OnRcvServerMsg(uint16 cmd,uint32 uin,CPacketDataIn &in);
	virtual void OnConnect(bool success);
};

