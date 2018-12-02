#include "data_parse.h"



void ParserDef::parserInit()
{
    socketBuffer.addIdx = 0;
    socketBuffer.getIdx = 0;

    addIdx = 0;
    getIdx = 0;

    isFrameAdd = false;
}

//获取socket缓冲区长度
int ParserDef::getSocketBufferLength()
{
    int length;

    length = socketBuffer.addIdx - socketBuffer.getIdx;


    if(length < 0)
    {
        length = SOCKET_BUFF_VAL_MAX - socketBuffer.getIdx + socketBuffer.addIdx;
    }

    return length;
}

void ParserDef::parserFrameAdd()
{
    char res;

    int length = getSocketBufferLength();

    if(length > 0)
    {
        //send(QString("%1").arg(length));

        for(int i = 0; i < length; i++)
        {
            if(socketBuffer.getIdx >= SOCKET_BUFF_VAL_MAX)
            {
                socketBuffer.getIdx = 0;
            }

            res = socketBuffer.buff[socketBuffer.getIdx++];

            if(isFrameAdd == false)
            {
                if(res == FRAME_HEAD_DEF)
                {
                    isFrameAdd = true;
                    frameBuffers[addIdx].idx = 0;
                    continue;
                }
            }

            if(isFrameAdd == true)
            {
                if(res == FRAME_END_DEF)
                {
                    isFrameAdd = false;

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

                frameBuffers[addIdx].buff[frameBuffers[addIdx].idx++] = res;
            }
        }
    }
}

//获取缓冲区帧数
int ParserDef::getFrameLength()
{
    int length;

    length = addIdx - getIdx;

    if(length < 0)
    {
        length = FRAME_NUM_MAX - getIdx + addIdx;
    }

    return length;
}

//执行帧解析
bool ParserDef::frameParse()
{

    //send(QString("%1").arg(addIdx));
    emit send(QString(frameBuffers[getIdx].buff));
    emit send(QString("%1").arg(strlen(frameBuffers[getIdx].buff)));

    return true;

}

void ParserDef::parserHandle()
{
    parserFrameAdd();

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

//解析器线程
void ParserDef::run()
{
    //emit send(QString("thread work"));
    parserInit();

    while(true)
    {
        parserHandle();
    }

}
