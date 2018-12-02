#ifndef DATARECIVE_H
#define DATARECIVE_H

#include "socketConfig.h"

#define BUFFER_VAL_MAX 255        //一帧最大字节数
#define FRAME_NUM_MAX  255        //缓冲区最大帧数
#define SOCKET_BUFF_VAL_MAX 1024  //socket数据缓冲区最大字节数
#define SOCKET_ONCE_REC_MAX 255   //以此接收的最大字节数

#define FRAME_HEAD_DEF  ':'       //定义数据帧头字节
#define FRAME_END_DEF   ';'       //定义数据帧尾字节

//函数外部声明
DWORD WINAPI winRecvHandle(LPVOID lpParamter);
DWORD WINAPI winParserHandle(LPVOID lpParamter);

//socket缓冲区定义
class SocketBufferDef
{
    public:
        char buff[SOCKET_BUFF_VAL_MAX];
        int  addIdx;        //缓冲区添加索引
        int  getIdx;        //缓冲区取出索引
};

//数据帧定义
class FrameBufferDef
{
    public: 
        char buff[BUFFER_VAL_MAX];
        int idx;            //数据帧内数据索引

};

//解析器定义
class ParserDef
{
    public:
        void parserInit();
        void parserHandle();
        void socketBufferAdd();
        
    
    private:
        SocketBufferDef socketBuffer;
        FrameBufferDef frameBuffers[FRAME_NUM_MAX];
        int frameLength;                //数据帧长度
        int addIdx;                     //数据帧添加索引
        int getIdx;                     //数据帧取出索引
        bool isFrameAdd;                //解析器数据帧添加状态

        
        void frameAdd();                //数据帧添加函数
        bool frameParse();              //数据帧解析函数
        int getSocketBufferLength();    //socket缓冲区长度计算函数 
        int getFrameLength();           //帧数计算函数



};

#endif // DATARECIVE_H