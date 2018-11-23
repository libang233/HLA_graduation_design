#include "socketConfig.h"

using namespace std;

bool connectFlag;
SOCKET socketSclient;


DWORD WINAPI recvHandle(LPVOID lpParamter)
{
	while(true)
	{
		while(connectFlag)
		{
			char recData[255];
			int ret = recv(socketSclient, recData, 255, 0);
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

void socketInit()
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

	socketSclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	while(true)
	{
		
		if(socketSclient == INVALID_SOCKET)
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
		if(connect(socketSclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  //连接失败 
			printf("connect error !\n");
			closesocket(socketSclient);
		}
		else
		{
			printf("connect successd!\n");
			connectFlag = true;
			break;
		}
	}

    /*
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

		send(socketSclient, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 
		
	}
	*/

}

void socketClose()
{
	closesocket(socketSclient);
	WSACleanup();
}