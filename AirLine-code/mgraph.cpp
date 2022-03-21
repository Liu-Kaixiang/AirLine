#include "mgraph.h"

//初始条件：传入空图G
//操作结果：构造图G，用邻接矩阵存储
void CreateGraph(MGraph &G)
{
    //一定注意指针初始化为空指针
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = NULL;//邻接矩阵每个位置初始值为空
        }
    }

    G.arcnum = LineNum;

    //以下算法实现机场数的求解以及vexs定点向量的初始化
    int AirportNum = 0;
    G.vexs[AirportNum].data = airline[0].DepAirport;//将起飞机场先赋值作为机场
    G.vexs[AirportNum].IsVisited = false;//初始化未被访问
    AirportNum++;
    for(int i = 1; i < LineNum; i++)//遍历所有起飞机场
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vexs[j].data == airline[i].DepAirport)//已存储的顶点信息与当前机场相同
                break;
        }
        if(j >= AirportNum)//出现新的机场
        {
            G.vexs[AirportNum].data = airline[i].DepAirport;
            G.vexs[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }

    for(int i = 0; i < LineNum; i++)//遍历所有抵达机场
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vexs[j].data == airline[i].ArrAirport)
                break;
        }
        if(j >= AirportNum)//出现新的机场
        {
            G.vexs[AirportNum].data = airline[i].ArrAirport;
            G.vexs[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }
    G.vexnum = AirportNum;//顶点数

    //以下算法实现邻接矩阵arcs的初始化
    for(int i = 0; i < LineNum; i++)
    {
        //确定当前航线应当存储的行列位置
        int row = LocateVex(G, airline[i].DepAirport);//起飞机场在顶点向量中的位置
        int col = LocateVex(G, airline[i].ArrAirport);//抵达机场在顶点向量中的位置
        //cout << i << ": " << row << "  " << col << endl;
        ArcCell* p = (ArcCell*)malloc(sizeof(ArcCell)); //开辟新的结点空间


        //采用头插法建单链表
        p->LineInfo = airline[i];
        p->next = NULL;

        //经统计，大约只有400多个点可以满足直飞
        if(!G.arcs[row][col])//对于第一个结点，直接将其赋值给邻接矩阵
        {
            G.arcs[row][col] = p;//本质上为指针指向，并不需要malloc空间
        }
        else
        {
            p->next = G.arcs[row][col]->next;
            G.arcs[row][col]->next = p;
        }
    }
}

//初始条件：图G存在且用邻接矩阵存储，v是G中某个顶点的下标
//操作结果：返回v的第一个邻接顶点位置，若顶点在G中没有邻接点，则返回-1
int FirstAdjVex(MGraph G,int v)//由于邻接矩阵定义的不同需要修改
{
    for(int i = 0; i < G.vexnum; i++)
    {
        if(G.arcs[v][i])//在邻接矩阵当前位置不是空指针，则找到
            return i;
    }
    return -1; //未找到
}

//初始条件：图G存在且用邻接矩阵存储，v是G中某个顶点的下标，w是v的邻接顶点的下标
//操作结果：返回v的（相对于w）的下一个邻接顶点位置，若w是v的最后一个邻接点，则返回-1
int NextAdjVex(MGraph G, int v, int w)
{
    for(int i = w + 1; i < G.vexnum; i++)//从w位置之后查找
    {
        if(G.arcs[v][i])//在邻接矩阵当前位置不是空指针，则找到
            return i;
    }
    return -1; //未找到
}


//初始条件：图G存在且用邻接矩阵存储，vertex为顶点中的机场信息
//操作结果：若G中存在顶点vertex，则返回其在图中的位置，否则返回-1
int LocateVex(MGraph G, int vertex)
{
    for(int i = 0; i < G.vexnum; i++)
    {
        if(G.vexs[i].data == vertex) //找到
            return i;
    }
    return -1;//未找到
}

//初始条件：图G存在且用邻接表存储，v是G中某个顶点的下标
//操作结果：打印输出以v为起点的广度优先遍历
void BFSTraverse(MGraph &G, int start, int terminal)
{
    for(int i = 0; i < G.vexnum; i++)//初始化很重要，每次遍历以后IsVisited都会被修改
    {
        G.vexs[i].IsVisited = false;
    }
    queue<int> que;

    int StartPos = LocateVex(G, start); //起始机场在顶点向量中的下标
    int TerminalPos = LocateVex(G, terminal); //目的机场在顶点向量中的下标

    if(StartPos == -1 || TerminalPos == -1)
    {
        cout << "没有此机场编号！" << endl;
        return;
    }

    if(!G.vexs[StartPos].IsVisited)//当前结点未被访问
    {
        G.vexs[StartPos].IsVisited = true; //设置为已经访问过
        que.push(StartPos);//入队列
        while(!que.empty()) //当队列不空时
        {
            int u = que.front(); //取队首元素
            que.pop();
            for(int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) //遍历与此顶点相连的所有邻接点
            {
                if(!G.vexs[w].IsVisited && w != TerminalPos)
                {
                    G.vexs[w].IsVisited = true;
                    que.push(w);//入队列

                }
                else if(w == TerminalPos)
                {
                    cout << "可以连通！" << endl;
                    return;
                }
            }
        }
    }
    cout << "不可以连通！" << endl;
    //return -1;
}

//初始条件：图G存在且以邻接矩阵形式存储，v是图G中某个顶点的下标
//操作结果：访问该顶点的信息，即打印输出相应的机场信息
void Visit(MGraph G, int v)
{
    cout << G.vexs[v].data << "  ";
}


