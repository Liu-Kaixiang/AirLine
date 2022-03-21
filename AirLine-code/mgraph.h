#ifndef MGRAPH_H
#define MGRAPH_H

/***此文件实现邻接矩阵的存储和基本操作函数***/

#include "datadefine.h"

//有向网
//邻接矩阵
typedef struct ArcCell{
    AirLine LineInfo; //存储航线信息的结构体：航班ID，起飞日期，国际/国内航班，航班号，起飞时间，抵达时间，飞机号，机型，机票价格等
    ArcCell* next; //指向下一个结点的指针
}ArcCell, *AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct VexNode
{
    int data;//顶点信息
    bool IsVisited;//是否被访问过
}VexNode;

typedef struct{
    VexNode vexs[MAX_VERTEX_NUM]; //顶点向量，存储机场
    AdjMatrix arcs; //邻接矩阵,但每一个点上存储的是一个指针，用以指向一个单链表，此链表存储的为以该机场为起飞机场的航线。
    int vexnum, arcnum; //图的当前顶点数和弧数
}MGraph;

//初始条件：传入空图G
//操作结果：构造图G，用邻接矩阵存储
void CreateGraph(MGraph &G); //已检测

//初始条件：图G存在且用邻接矩阵存储，v是G中某个顶点的下标
//操作结果：返回v的第一个邻接顶点位置，若顶点在G中没有邻接点，则返回-1
int FirstAdjVex(MGraph G,int v);

//初始条件：图G存在且用邻接矩阵存储，v是G中某个顶点的下标，w是v的邻接顶点的下标
//操作结果：返回v的（相对于w）的下一个邻接顶点位置，若w是v的最后一个邻接点，则返回-1
int NextAdjVex(MGraph G, int v, int w);

//初始条件：图G存在且用邻接矩阵存储，vertex为顶点中的机场信息
//操作结果：若G中存在顶点vertex，则返回其在图中的位置，否则返回-1
int LocateVex(MGraph G, int vertex);

//初始条件：图G存在且用邻接矩阵存储，start是起始机场的编号，terminal是目标机场的编号
//操作结果：若start与terminal之间连通，则打印输出“可以连通”，否则打印输出“不可以连通”
void BFSTraverse(MGraph &G, int start, int terminal);

//初始条件：图G存在且以邻接矩阵形式存储，v是图G中某个顶点的下标
//操作结果：访问该顶点的信息，即打印输出相应的机场信息
void Visit(MGraph G, int v);

#endif // MGRAPH_H
