#ifndef ALGRAPH_H
#define ALGRAPH_H
/***此文件实现邻接表的存储和基本操作函数***/

#include "datadefine.h"

//邻接表：头插法建表，两个机场间可能包含多条航线，但航线的信息不同
typedef struct ArcNode
{
    int adjvex; //该弧所指向的顶点的位置
    struct ArcNode *nextarc; //指向下一条弧的指针
}ArcNode;

typedef struct VNode
{
    int data; //顶点信息，即机场
    ArcNode *firstarc; //指向第一条依附该顶点的弧
    bool IsVisited; //是否被访问
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum, arcnum; //图的当前顶点数和弧数
}ALGraph;

//初始条件：传入空图G
//操作结果：构造图G，用邻接表存储
void CreateGraph(ALGraph &G);

//初始条件：图G存在且用邻接表存储，v是G中某个顶点的下标
//操作结果：返回v的第一个邻接顶点位置，若顶点在G中没有邻接点，则返回-1
int FirstAdjVex(ALGraph G, int v);

//初始条件：图G存在且用邻接表存储，v是G中某个顶点的下标，w是v的邻接顶点的下标
//操作结果：返回v的（相对于w）的下一个邻接顶点位置，若w是v的最后一个邻接点，则返回-1
int NextAdjVex(ALGraph G, int v, int w);

//初始条件：图G存在且用邻接表存储，vertex为顶点中的机场信息
//操作结果：若G中存在顶点vertex，则返回其在图中的位置，否则返回-1
int LocateVex(ALGraph G, int vertex);

//初始条件：图G存在且用邻接表存储，图G中每个顶点都未被遍历到，即IsVisited值为false，v是G中某个顶点的下标
//操作结果：打印输出以v为起点的深度优先遍历
void DFS(ALGraph &G, int v);

//初始条件：图G存在且用邻接表存储，对图G中IsVisited值无要求，v是G中某个顶点的下标
//操作结果：打印输出以v为起点的深度优先遍历
void DFSTraverse(ALGraph &G, int v);

//初始条件：图G存在且用邻接表存储，v是G中某个顶点的下标
//操作结果：打印输出以v为起点的广度优先遍历
void BFSTraverse(ALGraph &G, int v);

//初始条件：图G存在且以邻接表形式存储，v是图G中某个顶点的下标
//操作结果：访问该顶点的信息，即打印输出相应的机场信息
void Visit(ALGraph G, int v);

#endif // ALGRAPH_H
