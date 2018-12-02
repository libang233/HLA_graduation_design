#include "dataReceive.h"
#include "simType.h"

//实例化解析器
ParserDef parser;

//
//调用windows API的缓冲区填充线程
//
DWORD WINAPI winRecvHandle(LPVOID lpParamter)
{
	parser.parserInit();

	while(true)
	{
		while(globleSimData.connectFlag)
		{
			parser.socketBufferAdd();     	
		}
	}

	return 0L;//必须返回一个值
}

//
//调用Windows API的解析器线程
//
DWORD WINAPI winParserHandle(LPVOID lpParamter)
{
	while(true)
	{
		parser.parserHandle();		
	}			

	return 0L;//必须返回一个值
}

//
//解析器初始化
//
void ParserDef::parserInit()
{
	//缓冲区索引初始化
	socketBuffer.getIdx = 0;
	socketBuffer.addIdx = 0;
    addIdx = 0;
    getIdx = 0;
}

//
//解析器中socket通信数据缓存
//
void ParserDef::socketBufferAdd()
{
	char recData[SOCKET_ONCE_REC_MAX];

	//赋值数据和数据长度
	int ret = recv(socketSclient, recData, SOCKET_ONCE_REC_MAX, 0);

	//判断是否接收到数据
	if (ret > 0)
	{
		//接收到的数据超出一次允许接收的字节数，丢弃剩下数据
		if(ret >= SOCKET_ONCE_REC_MAX)
		{
			ret = SOCKET_ONCE_REC_MAX;
		}
		//循环赋值数据到socket数据缓冲区
		for (int i = 0; i < ret; i++)
		{
			//判断添加索引是否大于最大缓冲长度，若大于添加索引置零，形成环形缓冲
			if (socketBuffer.addIdx >= SOCKET_BUFF_VAL_MAX)
			{
				socketBuffer.addIdx = 0;
			}

			socketBuffer.buff[socketBuffer.addIdx++] = recData[i];
		}
	}
}

//
//获取socket缓冲区长度
//
int ParserDef::getSocketBufferLength()
{
	int length;

	length = socketBuffer.addIdx - socketBuffer.getIdx;

    if(length < 0)
    {
		//环形缓冲的数据长度计算
        length = SOCKET_BUFF_VAL_MAX - socketBuffer.getIdx + socketBuffer.addIdx;
    }

    return length;
}

//
//获取缓冲区帧数
//
int ParserDef::getFrameLength()
{
    int length;

    length = addIdx - getIdx;

    if(length < 0)
    {
		//环形缓冲的数据长度计算
        length = FRAME_NUM_MAX - getIdx + addIdx;
    }

    return length;
}

//
//数据帧缓冲填充
//
void ParserDef::frameAdd()
{
    char res;

    int length = getSocketBufferLength();

    if(length > 0)
    {
        for(int i = 0; i < length; i++)
        {
			//若读索引大于最大缓冲长度，读索引置零，形成环形缓冲
            if(socketBuffer.getIdx >= SOCKET_BUFF_VAL_MAX)
            {
                socketBuffer.getIdx = 0;
            }

            res = socketBuffer.buff[socketBuffer.getIdx++];

            if(isFrameAdd == false)
            {
                if(res == FRAME_HEAD_DEF)
                {
					//未在数据帧添加状态下，接收到数据帧头，说明得到一帧数据
					//将数据帧添加状态置位
                    isFrameAdd = true;
					//初始化数据帧缓冲区帧内添加索引
                    frameBuffers[addIdx].idx = 0;
					//执行下一次循环
                    continue;
                }
            }

            if(isFrameAdd == true)
            {
                if(res == FRAME_END_DEF)
                {
					//在数据帧添加状态下，接收到数据帧结尾，说明一帧数据添加完毕
					//将数据帧添加状态复位
                    isFrameAdd = false;

					//更新数据帧索引，同样时环形缓冲
                    if(addIdx < FRAME_NUM_MAX - 1)
                    {
                        addIdx++;
                    }
                    else
                    {
                        addIdx = 0;
                    }

                    continue;
                }

				//数据字节循环赋值
                frameBuffers[addIdx].buff[frameBuffers[addIdx].idx++] = res;
            }
        }
    }
}

//
//数据帧解析
//
bool ParserDef::frameParse()
{
	printf(frameBuffers[getIdx].buff);

	if(frameBuffers[getIdx].buff[0] == 's')
	{
		globleSimData.simStartFlag = true;
	}

	return true;
}


//
//解析器线程
//
void ParserDef::parserHandle()
{
	//添加帧
	frameAdd();

	//数据解析
	if(getFrameLength() > 0)
	{
		if(frameParse() == true)
		{
			getIdx++;
		}
		else
		{
			getIdx++;
		}

		if(getIdx >= FRAME_NUM_MAX)
		{
			getIdx = 0;
		}
	}
}



