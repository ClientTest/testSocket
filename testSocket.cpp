// testSocket.cpp : �������̨Ӧ�ó������ڵ㡣
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


// Ψһ��Ӧ�ó������

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
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO: ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����: MFC ��ʼ��ʧ��\n"));
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
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����: GetModuleHandle ʧ��\n"));
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

	if(getchar())						//�����������رճ���
	{
		CPacketDataOut outShutdown;
		outShutdown << "whg123456";
		GetAGuiSocketCore()->SendToServer(UDP_SHUTDOWN,outShutdown);

		GetAGuiSocketCore()->UnRegistAllListen();
		GetAGuiSocketCore()->close();
		DestroyAGuiSocketCore();

		return;						//������������
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
	printf("UDP�ͻ����Ѿ�����\r\n");
	if(::sendto(s,out.GetData(),out.GetSize(),0,(sockaddr*)&addr,n)!=0)
	//if(::sendto(s,sztext,sizeof(sztext),0,(sockaddr*)&addr,n)!=0)
	{
		::recvfrom(s,buff,10,0,(sockaddr*)&addr2,&n);
		printf("������˵��%s\r\n",buff);
		::closesocket(s);
		::WSACleanup();
	} 
	if(getchar())						//�����������رճ���
	{
		return;						//������������
	}
	else
	{
		::Sleep(100);
	}
}