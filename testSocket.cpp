// testSocket.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "testSocket.h"

#include "WinLib/WinLibQuote.h"
#include "WinLib/PacketData.h"
#include "AGuiSocketListen.h"

#include<winsock2.h>
#include<stdio.h>
#include<windows.h>


#pragma comment(lib,"WS2_32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

void MainFun();
void MainAGuiSocket();

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: 更改错误代码以符合您的需要
			_tprintf(_T("错误: MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			//MainFun();
			MainAGuiSocket();
		}
	}
	else
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("错误: GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}

CAGuiSocketListen aguiSockListen;

void MainAGuiSocket()
{
	GetAGuiSocketCore()->RegistListen(&aguiSockListen);
	GetAGuiSocketCore()->open("127.0.0.1",8000,10000);
	//GetAGuiSocketCore()->open("192.168.10.105",8000,10000);
	//GetAGuiSocketCore()->open("111.0.180.52",8000,10000);

	char sztext[]="hello";
	CPacketDataOut out;
	out<<(uint32)1 << (uint32)25;
	GetAGuiSocketCore()->SendToServer(UDP_LOGIN,out);

	GetAGuiSocketCore()->SendToServer(UDP_LOGOUT,out);

	if(getchar())						//如果有输入则关闭程序
	{
		CPacketDataOut outShutdown;
		outShutdown << "whg123456";
		GetAGuiSocketCore()->SendToServer(UDP_SHUTDOWN,outShutdown);

		GetAGuiSocketCore()->UnRegistAllListen();
		GetAGuiSocketCore()->close();
		DestroyAGuiSocketCore();

		return;						//正常结束程序
	}
	else
	{
		::Sleep(100);
	}
}

void MainFun()
{
	WSADATA data;
	WORD w=MAKEWORD(2,0);
	char sztext[]="hello";
	::WSAStartup(w,&data);
	SOCKET s;
	s=::socket(AF_INET,SOCK_DGRAM,0);
	sockaddr_in addr,addr2;
	int n=sizeof(addr2);
	char buff[10]={0};
	addr.sin_family=AF_INET;
	addr.sin_port=htons(8000);
	addr.sin_addr.S_un.S_addr=inet_addr("127.0.0.1");

	CPacketDataOut out;
	out<<(uint32)1 << sztext;
	printf("UDP客户端已经启动\r\n");
	if(::sendto(s,out.GetData(),out.GetSize(),0,(sockaddr*)&addr,n)!=0)
	//if(::sendto(s,sztext,sizeof(sztext),0,(sockaddr*)&addr,n)!=0)
	{
		::recvfrom(s,buff,10,0,(sockaddr*)&addr2,&n);
		printf("服务器说：%s\r\n",buff);
		::closesocket(s);
		::WSACleanup();
	} 
	if(getchar())						//如果有输入则关闭程序
	{
		return;						//正常结束程序
	}
	else
	{
		::Sleep(100);
	}
}