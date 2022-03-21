#include "algraph.h"

//初始条件：传入空图G
//操作结果：构造图G，用邻接表存储
void CreateGraph(ALGraph &G)
{
    G.arcnum = LineNum;
    int AirportNum = 0;
    G.vertices[AirportNum].data = airline[0].DepAirport;//将起飞机场先赋值作为机场
    G.vertices[AirportNum].firstarc = NULL;//初始化为0
    G.vertices[AirportNum].IsVisited = false;//初始化未被访问
    AirportNum++;
    for(int i = 1; i < LineNum; i++)//遍历所有起飞机场
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vertices[j].data == airline[i].DepAirport)//已存储的顶点信息与当前机场相同
                break;
        }
        if(j >= AirportNum)//出现新的机场
        {
            G.vertices[AirportNum].data = airline[i].DepAirport;
            G.vertices[AirportNum].firstarc = NULL;
            G.vertices[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }

    for(int i = 0; i < LineNum; i++)//遍历所有抵达机场
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vertices[j].data == airline[i].ArrAirport)
                break;
        }
        if(j >= AirportNum)//出现新的机场
        {
            G.vertices[AirportNum].data = airline[i].ArrAirport;
            G.vertices[AirportNum].firstarc = NULL;
            G.vertices[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }

    G.vexnum = AirportNum;//顶点数

    for(int i = 0; i < LineNum; i++)
    {
        int flag = 0; //用于表示抵达机场是否已经接入邻接表，默认未接入
        int pos = LocateVex(G, airline[i].DepAirport);//起飞机场在顶点数组中的位置
        ArcNode* p = G.vertices[pos].firstarc;//用于遍历邻接表
        while(p)
        {
            if(G.vertices[p->adjvex].data == airline[i].ArrAirport)//如果当前顶点中已经连接了此航线下的抵达机场
            {
                flag = 1;
                break;
            }
            p = p->nextarc;
        }
        if(flag == 1)//机场相同但航线不同，向下连接不同航线信息
        {
            continue;
        }
        else //机场不同
        {
            //头插法
            ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
            q->nextarc = G.vertices[pos].firstarc;
            q->adjvex = LocateVex(G, airline[i].ArrAirport);
            G.vertices[pos].firstarc = q;
        }
    }
}

//初始条件：图G存在且用邻接表存储，v是G中某个顶点的下标
//操作结果：返回v的第一个邻接顶点位置，若顶点在G中没有邻接点，则返回-1
int FirstAdjVex(ALGraph G, int v)
{
    if(G.vertices[v].firstarc == NULL)
        return -1;//没有邻接点
    else
        return G.vertices[v].firstarc->adjvex;//返回第一个邻接点存储的位置信息
}

//初始条件：图G存在且用邻接表存储，v是G中某个顶点的下标，w是v的邻接顶点的下标
//操作结果：返回v的（相对于w）的下一个邻接顶点位置，若w是v的最后一个邻接点，则返回-1
int NextAdjVex(ALGraph G, int v, int w)
{
    ArcNode* p = G.vertices[v].firstarc;
    while(p != NULL)//遍历与该顶点相关的顶点
    {
        if(p->adjvex == w)//p指向w所在结点的位置
        {
            if(p->nextarc)//若w之后还有结点则返回对应结点中的adjvex值
                return p->nextarc->adjvex;
            else
                return -1;//若w后无后继，则返回-1，表示“空”
        }
        p = p->nextarc;//指向下一个结点
    }
    //return ERROR;//w不是v的邻接顶点，输入出错
    return -1;
}

//初始条件：图G存在且用邻接表存储，vertex为顶点中的机场信息
//操作结果：若G中存在顶点vertex，则返回其在图中的位置，否则返回-1
int LocateVex(ALGraph G, int vertex)
{
    for(int i = 0; i < G.vexnum; i++)
    {
        if(vertex == G.vertices[i].data)//定位到相应顶点位置
            return i;
    }
    return -1;//未找到
}

//初始条件：图G存在且用邻接表存储，图G中每个顶点都未被遍历到，即IsVisited值为false，v是G中某个顶点的下标
//操作结果：打印输出以v为起点的深度优先遍历
void DFS(ALGraph &G, int v) //此处必须加&
{
    G.vertices[v].IsVisited = true;
    Visit(G, v);
    for(int w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if(!G.vertices[w].IsVisited)
        {
            DFS(G,w);
        }
    }
}

//初始条件：图G存在且用邻接表存储，对图G中IsVisited值无要求，v是G中某个顶点的下标
//操作结果：打印输出以v为起点的深度优先遍历
void DFSTraverse(ALGraph &G, int v)
{
    for(int i = 0; i < G.vexnum; i++)//初始化很重要，每次遍历以后IsVisited都会被修改
    {
        G.vertices[i].IsVisited = false;
    }
    DFS(G, v);
}

//初始条件：图G存在且用邻接表存储，v是G中某个顶点的下标
//操作结果：打印输出以v为起点的广度优先遍历
void BFSTraverse(ALGraph &G, int v)
{
    for(int i = 0; i < G.vexnum; i++)//初始化很重要，每次遍历以后IsVisited都会被修改
    {
        G.vertices[i].IsVisited = false;
    }
    queue<int> que;
    if(!G.vertices[v].IsVisited)//当前结点未被访问
    {
        G.vertices[v].IsVisited = true; //设置为已经访问过
        Visit(G, v);//访问信息
        que.push(v);//入队列
        while(!que.empty()) //当队列不空时
        {
            int u = que.front(); //取队首元素
            que.pop();
            for(int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) //遍历与此顶点相连的所有邻接点
            {
                if(!G.vertices[w].IsVisited)
                {
                    G.vertices[w].IsVisited = true;
                    Visit(G, w);
                    que.push(w);//入队列
                }
            }
        }
    }
}

//初始条件：图G存在且以邻接表形式存储，v是图G中某个顶点的下标
//操作结果：访问该顶点的信息，即打印输出相应的机场信息
void Visit(ALGraph G, int v)
{
    cout << G.vertices[v].data << "  ";
}
