#ifndef FUNCTION_H
#define FUNCTION_H
/***此文件用于实现所有要求的功能***/

#include "algraph.h"
#include "mgraph.h"

typedef struct Path
{
    int TraceLen; //路径长度，指路径上包含几个机场
    int TraceID[80];//最多79个机场,存储航班ID
    int TraceAirport[80]; //存储路径中的机场信息
    int CurTime; //当前时间
    int StartTime; //起始时间
    int SumTime; //此路径下的总时间
    int SumFare; //此路径下的总费用
}Path;

typedef struct Req
{
    int FirstDepTime;//存储用户希望的最早起飞时间
    int LastDepTime;//存储用户希望的最晚起飞时间
    int FirstArrTime;//存储用户希望的最早抵达时间
    int LastArrTime;//存储用户希望的最晚抵达时间
    int AirplaneModel[10];//机型,存储用户想要的所有机型
}Req;

//初始条件：str为csv文件的存储位置
//操作结果：读取并存储相应存储位置的csv文件的所有信息
void ReadFile(string str);

//初始条件：str为表示日期的字符串
//操作结果：将str中的信息转换为结构体类型存储，并返回结果
Date StrToDate(string str); //已检测

//初始条件：dt为表示日期的结构体
//操作结果：将dt中的信息转换为以分钟为单位的时间，并返回
int DateToMin(Date dt);

//初始条件：r为空的结构体，用以存储用户所有需求
//操作结果：通过用户的输入将用户的所有需求存入r中，并得到其值
void Request(Req &r);

//初始条件：r存储了用户输入的所有需求，ReqType指用户需求种类（0表示对起飞时段有要求，1表示对抵达时段有要求，2表示对机型有要求），p为传入的当前航线结点
//操作结果：根据不同的ReqType来确定该航线是否符合用户需求，若符合则返回true，否则返回false
bool IsMatchReq(Req r, int ReqType, ArcCell* p);

//初始条件：dt1,dt2为两个时间，包含年、月、日、小时、分钟
//操作结果：若dt1的时间在dt2时间之后则返回1，若二者相同则返回0，否则返回-1
int CompareDate(Date dt1, Date dt2);

//初始条件：G为用邻接矩阵存储的图
//操作结果：释放所有malloc空间
void FreeGraph(MGraph &G);

//初始条件：图G存在且用邻接表存储
//操作结果：打印输出从任意机场出发的遍历,包括深度优先遍历和广度优先遍历
void Mission1(ALGraph &G); //已检测

//初始条件：图G存在且用邻接矩阵存储
//操作结果：使用邻接矩阵表来完成任意两个机场的可连通性，包括是否可以直飞、1次中转、2次中转等
void Mission2(MGraph &G);

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：使用邻接矩阵表来完成求任意两个机场之间的最短飞行时间（含转机停留时间）
void Mission3(MGraph &G);

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：仅限直飞或1次中转，打印输出任意两个机场的航线（航班ID顺序表）
void Mission4(MGraph G);

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：给定起飞时段或者降落时段或者机型要求, 打印输出任意两个机场的多个备选航线（航班ID顺序表）
void Mission5(MGraph G);

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：给定起飞时段或者降落时段或者机型要求，打印输出任意两个机场之间的航费（机票价格）最低的路径
void Mission6(MGraph G);

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：给定飞行时长或者中转时间限制，打印输出任意两个机场的多个备选航线（航班ID顺序表）
void Mission7(MGraph G);

#endif // FUNCTION_H
