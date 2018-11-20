#include "data_parse.h"

ParserDef parser;

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

}

//解析器线程
void ParserDef::parsingHandle()
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
