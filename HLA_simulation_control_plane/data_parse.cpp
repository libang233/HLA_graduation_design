#include "data_parse.h"



void ParserDef::parserInit()
{
    addIdx = 0;
    getIdx = 0;
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
   emit send(QString(frameBuffers[getIdx].buff));
  if(frameBuffers[getIdx].buff[0] == '2')
  {
        emit send(QString("get 2"));
  }
}

//解析器线程
void ParserDef::run()
{
    //emit send(QString("thread work"));

    while(true)
    {
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

}
