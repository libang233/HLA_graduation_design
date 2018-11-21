#include "ExampleCPPFederate.h"

#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include<WINSOCK2.H>
#include "windows.h"

#include<string>

#include<iostream>
#include<cstring>
using namespace std;
#pragma comment(lib, "ws2_32.lib")

bool connectFlag;
SOCKET sclient;

DWORD WINAPI recvHandle(LPVOID lpParamter)
{
	while(true)
	{
		while(connectFlag)
		{
			char recData[255];
			int ret = recv(sclient, recData, 255, 0);
			if(ret>0)
			{
				recData[ret] = 0x00;
				printf(recData);
				printf("\n");
			}
		}
	}

	return 0L;//必须返回一个值
}

void socketHandle()
{
		connectFlag = false;

	//创建接收线程
	HANDLE hThread = CreateThread(NULL, 0, recvHandle, NULL, 0, NULL);
	CloseHandle(hThread);

	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;

	if(WSAStartup(sockVersion, &data)!=0)
	{
		return;
	}

	sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	while(true)
	{
		
		if(sclient == INVALID_SOCKET)
		{
			printf("invalid socket!\n");
			
		}
		else
		{
			printf("valid sokcet!\n");
		}
		
		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(5550);
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		if(connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  //连接失败 
			printf("connect error !\n");
			closesocket(sclient);
		}
		else
		{
			printf("connect successd!\n");
			connectFlag = true;
			break;
		}
	}

	while(true)
	{	
		string data;
		getline(cin,data);
		
		const char * sendData;
		sendData = data.c_str();   
		if(sendData == "shutdown")
		{
			break;
		}

		//char * sendData = "你好，TCP服务端，我是客户端\n";

		send(sclient, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 
		
	}
	
	closesocket(sclient);
	WSACleanup();
}

int main( int argc, char *argv[] )
{
	// check to see if we have a federate name
	char* federateName = "exampleFederate";
	if( argc > 1 )
		federateName = argv[1];

	// create and run the federate
	ExampleCPPFederate *federate;
	federate = new ExampleCPPFederate();
	//federate->runFederate( federateName );
	
    socketHandle();

	// clean up
	delete federate;
	return 0;
}
