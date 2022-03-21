#include "function.h"

void ReadFile(string str)
{
    //读文件
    ifstream inFile(str, ios::in);
    string lineStr;

    LineNum = -1;//航线数量初始化为-1，第一行名称不读入
    while(getline(inFile, lineStr))
    {
        //第一行用于存储各列的信息
        //存成二维表结构
        stringstream ss(lineStr);
        string str;
        vector<string> lineArray;
        // 按照逗号分隔
        while(getline(ss, str, ','))
            lineArray.push_back(str);

        if(LineNum == -1)
        {
            LineNum++;//第一行为名称
            continue;
        }
        airline[LineNum++] = {stoi(lineArray[0]), stoi(lineArray[3]), stoi(lineArray[4]), stoi(lineArray[5]),
                              DateToMin(StrToDate(lineArray[6])), DateToMin(StrToDate(lineArray[7])), stoi(lineArray[8]),
                              stoi(lineArray[9]), stoi(lineArray[10])};
    }
}

//初始条件：str为表示日期的字符串
//操作结果：将str中的信息转换为结构体类型存储，并返回结果
Date StrToDate(string str)
{
    Date dt;
    string temp = "";//设置为空串
    int len = str.length();
    int index = 0;//0表示存储月，1表示存储日，2表示存储年，3表示存储小时，4表示存储分钟
    for(int i = 0; i < len; i++)
    {
        while(str[i] != '/' && str[i] != ' ' && str[i] != ':' && i < len)//三种间隔符
        {
            temp.push_back(str[i]);
            i++;
        }
        switch (index) {
        case 0:
            dt.month = stoi(temp);
            temp.clear();//清空字符串
            index++;
            break;
        case 1:
            dt.day = stoi(temp);
            temp.clear();//清空字符串
            index++;
            break;
        case 2:
            dt.year = stoi(temp);
            temp.clear();//清空字符串
            index++;
            break;
        case 3:
            dt.hour = stoi(temp);
            temp.clear();//清空字符串
            index++;
            break;
        case 4:
            dt.minute = stoi(temp);
            temp.clear();//清空字符串
            index++;
            break;
        default:
            break;
        }
    }
    return dt;
}

//初始条件：dt为表示日期的结构体
//操作结果：将dt中的信息转换为以分钟为单位的时间，并返回
int DateToMin(Date dt)
{
    //经统计，最早的航班是5号出发
    return ((dt.day - 5) * 24 + dt.hour) * 60 + dt.minute;//以天为单位转换到分钟
}

//初始条件：r为空的结构体，用以存储用户所有需求
//操作结果：通过用户的输入将用户的所有需求存入r中，并得到其值
void Request(Req &r)
{
    for(int i = 0; i < 10; i++)//初始化为0
        r.AirplaneModel[i] = 0;

    r.FirstDepTime = 0;
    r.LastDepTime = INFINITY;//初始化时默认无要求
    r.FirstArrTime = 0;
    r.LastArrTime = INFINITY;

    cout << "请输入你的需求:" << endl;

    Date dt;
    cout << "请输入你希望的最早起飞时间(请以日、小时、分钟的格式顺序输入, 若无则输入-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute; //换行符结束
    if(dt.day != -1)
        r.FirstDepTime = DateToMin(dt);

    cout << "请输入你希望的最晚起飞时间(请以日、小时、分钟的格式顺序输入, 若无则输入-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute;
    if(dt.day != -1)
        r.LastDepTime = DateToMin(dt);

    cout << "请输入你希望的最早抵达时间(请以日、小时、分钟的格式顺序输入, 若无则输入-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute;
    if(dt.day != -1)
        r.FirstArrTime = DateToMin(dt);

    cout << "请输入你希望的最晚抵达时间(请以日、小时、分钟的格式顺序输入, 若无则输入-1 -1 -1)" << endl;
    cin >> dt.day >> dt.hour >> dt.minute;
    if(dt.day != -1)
        r.LastArrTime = DateToMin(dt);

    int ReqModelNum = 0;//要求的机型数量
    cout << "请问你想要几种机型（请输入1-6的整数，其中6表示任何机型都可以）：";
    cin >> ReqModelNum;

    if(ReqModelNum >= 1 && ReqModelNum <= 5)
    {

        cout << "请输入你想要的机型种类：";
        for(int i = 0; i < ReqModelNum; i++)
        {
            int model;
            cin >> model;
            r.AirplaneModel[model] = 1;//若用户输入5，则指机型5处的值为1
        }
    }
    else if(ReqModelNum == 6)//所有机型都可
    {
        for(int i = 0; i < ReqModelNum; i++)
            r.AirplaneModel[i] = 1;
    }
    else if(ReqModelNum >= 7)
        cout << "错误输入！" << endl;
}

//初始条件：r存储了用户输入的所有需求，ReqType指用户需求种类（0,1,2均需要保证所乘坐的飞机机型存在；0表示对起飞时段有要求，1表示对抵达时段有要求，2表示仅对机型有要求），p为传入的当前航线结点
//操作结果：根据不同的ReqType来确定该航线是否符合用户需求，若符合则返回true，否则返回false
bool IsMatchReq(Req r, int ReqType, ArcCell* p)
{
    if(ReqType == 0)
    {
        if(r.FirstDepTime <= p->LineInfo.DepTime && r.LastDepTime >= p->LineInfo.DepTime)
        {
            if(r.AirplaneModel[p->LineInfo.AirplaneModel] == 1)//要保证此机型存在且可以乘坐
                return true;
        }
    }

    if(ReqType == 1)
    {
        if(r.FirstArrTime <= p->LineInfo.ArrTime && r.LastArrTime >= p->LineInfo.ArrTime)
        {
            if(r.AirplaneModel[p->LineInfo.AirplaneModel] == 1)//要保证此机型存在且可以乘坐
                return true;
        }
    }

    if(ReqType == 2)
    {
        if(r.AirplaneModel[p->LineInfo.AirplaneModel] == 1)
            return true;
    }

    return false;
}

//初始条件：dt1,dt2为两个时间，包含年、月、日、小时、分钟
//操作结果：若dt1的时间在dt2时间之后则返回1，若二者相同则返回0，否则返回-1
int CompareDate(Date dt1, Date dt2)
{
    if(dt1.year > dt2.year)
        return 1;
    else if(dt1.year < dt2.year)
        return -1;

    if(dt1.month > dt2.month)
        return 1;
    else if(dt1.month < dt2.month)
        return -1;

    if(dt1.day > dt2.day)
        return 1;
    else if(dt1.day < dt2.day)
        return -1;

    if(dt1.hour > dt2.hour)
        return 1;
    else if(dt1.hour < dt2.hour)
        return -1;

    if(dt1.minute > dt2.minute)
        return 1;
    else if(dt1.minute < dt2.minute)
        return -1;
    else
        return 0;
}

void FreeGraph(MGraph &G)
{
    ArcCell *p, *q; //用以遍历与每个顶点相连的单链表
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            p = G.arcs[i][j];
            if(p)
            {
                while(p)//遍历单链表
                {
                    q = p;
                    p = p->next;
                    free(q);
                    q = NULL;
                }
            }
        }
    }
    p = NULL;//防止成为野指针
    G.arcnum = 0;
    G.vexnum = 0;
}

//初始条件：图G存在且用邻接表存储
//操作结果：打印输出从任意机场出发的遍历,包括深度优先遍历和广度优先遍历
void Mission1(ALGraph &G)
{
    cout << "DFSTraverse:" << endl;
    int DepAirport;
    cout << "请输入起始机场：";
    cin >> DepAirport;
    int DepPos = LocateVex(G, DepAirport);
    if(DepPos == -1)
    {
        cout << "此机场不存在！" << endl;
        return;
    }

    DFSTraverse(G, DepPos);//头插法建表
    /*
    for(int i = 0; i < G.vexnum; i++)
    {
        cout << "以机场" << G.vertices[i].data << "为起始点，结果为：";
        DFSTraverse(G, i);
        cout << endl << endl;
    }
    */
    cout << endl << endl;

    cout << "BFSTraverse:" << endl;

    cout << "请输入起始机场：";
    cin >> DepAirport;
    DepPos = LocateVex(G, DepAirport);
    if(DepPos == -1)
    {
        cout << "此机场不存在！" << endl;
        return;
    }
    BFSTraverse(G, DepPos); //头插法建表
    cout << endl << endl;
    /*
    for(int i = 0; i < G.vexnum; i++)
    {
        cout << "以机场" << G.vertices[i].data << "为起始点，结果为：";
        BFSTraverse(G, i);
        cout << endl << endl;
    }
    */
}

//初始条件：图G存在且用邻接表存储
//操作结果：使用邻接矩阵表来完成任意两个机场的可连通性，包括是否可以直飞、1次中转、2次中转等
void Mission2(MGraph &G)
{

    //算法思想：每个结点内都存有路径中经过的机场数，利用队列的特性，只要搜到某一个结点的当前机场为目标机场，则此结点存储的路径就是转机次数最短的路径

    cout << "请分别输入出发机场与目的机场的编号（利用广度优先遍历搜索）：";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "错误输入！出发机场和目的机场相同！" << endl;
        return;
    }
    int StartPos = LocateVex(G, DepAirport); //出发机场在顶点向量中的位置下标
    int TerminalPos = LocateVex(G, ArrAirport); //目的机场在顶点向量中的位置下标

    queue<Path*> PathNode;//路径结点,存储路径上的相关信息

    cout << "Loading..." << endl;

    for(int i = 0; i < G.vexnum; i++)//遍历起始机场所在的邻接矩阵一行，做栈的初始化
    {
        if(G.arcs[StartPos][i])//当前位置有航线
        {
            ArcCell* p = G.arcs[StartPos][i];//用以遍历以此结点为头的所有航线
            while(p)//遍历与此结点相关的所有航线，即以此机场为出发机场的所有航线
            {
                if(i == TerminalPos)//找所有能直达目的机场的航线中的最短时间，此结点不需要创建和入队列，只需要确定最短时间，作为时间的上界
                {
                    cout << "可以直飞，最少转机次数为0！ " << endl;
                    return;
                }

                //其他所有航线生成结点入队列
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//当前路径长,对应的转机次数为此基础上减2
                node->StartTime = p->LineInfo.DepTime;//起始时间为出发时间
                node->CurTime = p->LineInfo.ArrTime;//当前时间为此航线的抵达时间
                node->TraceAirport[0] = G.vexs[StartPos].data; //路径经过的机场
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//入队列

                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//队列非空，进行BFS,一层层的搜，搜到为止
    {
        Path *pNode = PathNode.front();//取队首元素
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//当前所在机场

        if(CurAirport == ArrAirport)//用队列，只要搜到就停
        {
            cout << "最少转机次数: " << pNode->TraceLen - 2 << endl;
            return;
        }

        int CurPos = LocateVex(G, CurAirport);//当前的机场在顶点向量中的下标

        for(int i = 0; i < G.vexnum; i++)//遍历此结点当前所在机场的邻接矩阵的一行
        {
            if(G.arcs[CurPos][i] && i != StartPos)//保证该位置有航线且路径上不出现起始机场
            {
                ArcCell *p = G.arcs[CurPos][i];//用以遍历航线，选取可行的航线S
                bool IsThrough = false;//用于表示当前遍历的机场是否已经出现在路径中，若没有出现则为false
                for(int j = 0; j < pNode->TraceLen; j++)//遍历路径中所有走过的机场
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//当前机场已经出现在路径中，进行剪枝
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//只有未经过的机场才有必要继续走
                {
                    while(p)//遍历与此机场相关的所有航线
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime) //此趟航班的起飞时间在当前时间（即抵达此机场的时间）之后，可以通行
                        {
                            Path *newNode = (Path*)malloc(sizeof(Path));
                            newNode->TraceLen = pNode->TraceLen + 1;
                            newNode->CurTime = p->LineInfo.ArrTime;
                            newNode->StartTime = pNode->StartTime;
                            newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;

                            for(int k = 0; k < pNode->TraceLen - 1; k++)//复制路径上的航班ID
                            {
                                newNode->TraceID[k] = pNode->TraceID[k];
                            }
                            for(int k = 0; k < pNode->TraceLen; k++)//复制路径上的机场
                            {
                                newNode->TraceAirport[k] = pNode->TraceAirport[k];
                            }
                            newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                            PathNode.push(newNode);
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
    }
    cout << "不能到达目的机场！" << endl;//遍历完仍然未返回时说明无可达路径
}

//注：此处的最短时间唯一，但路径不一定唯一
//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：使用邻接矩阵表来完成求任意两个机场之间的最短飞行时间（含转机停留时间）
void Mission3(MGraph &G)
{
    /*优化（剪枝）
     * 1.在求最短时间时，对每个起落点的所有航班仅取其中落地时间最早的一班。(可以保证最优)
     * 2.在求最短时间时，若当前路径的总时间已经大于当前记录的最小值，则将其删除
     * 3.航班的起飞时间须晚于乘客抵达该机场的时间
     * 4.航班的目的机场不应在路径上出现过
     * 5.路径不应出现回路
     * 6.在列举航线时，若航线过多则只显示前2000条以及最终的总条数（若航线过多则可能计算时间较长）。
    */

    /*基本算法思想：
     * 1.首先遍历起飞机场所在的邻接矩阵的一行；
     *   对于能直达终点的航线特殊处理，此时需要修改用以统计最短时间的变量；
     *   对于其他航线需要生成相应的结点入栈
     * 2.在栈非空时进行DFS，同时在遍历时进行相应的优化和剪枝，比如若当前路径的总时间已经大于当前记录的最小值，则将其删除等
     * 3.在遍历时对于当前结点还需要遍历此结点目前所在的机场的邻接矩阵的一行，若有满足条件的航线，则生成新的结点入栈；
     * 4.以此类推到最终栈空为止。
    */

    cout << "请输入出发机场与目的机场的序号：";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "错误输入！出发机场和目的机场相同！" << endl;
        return;
    }

    int StartPos = LocateVex(G, DepAirport); //出发机场在顶点向量中的位置下标
    int TerminalPos = LocateVex(G, ArrAirport); //目的机场在顶点向量中的位置下标

    int MinTime = INFINITY;//最短通行时间；只选择其中最早抵达的航线，即在到达某个机场重点所有航线中只选择第一个到达的航线，进行优化剪枝
    int MinAirportTrace[G.vexnum] = {G.vexs[StartPos].data, G.vexs[TerminalPos].data, 0}; //标记数组，存储最短路径的机场信息
    int MinIDtrace[G.vexnum] = {0}; //标记数组，存储最短路径的航班ID信息
    int TraceLen = 2; //路径长度，记录的是路径中的机场数。初始值为2，表示最少是两个机场

    stack<Path*> PathNode;//路径结点,存储路径上的相关信息

    cout << "Loading..." << endl;

    for(int i = 0; i < G.vexnum; i++)//遍历起始机场所在的邻接矩阵一行，做栈的初始化
    {
        if(G.arcs[StartPos][i])//当前位置有航线
        {
            ArcCell* p = G.arcs[StartPos][i];//用以遍历以此结点为头的所有航线
            while(p)//遍历与此结点相关的所有航线，即以此机场为出发机场的所有航线
            {
                if(i == TerminalPos)//找所有能直达目的机场的航线中的最短时间，此结点不需要创建和入栈，只需要确定最短时间，作为时间的上界
                {
                    if(p->LineInfo.ArrTime - p->LineInfo.DepTime < MinTime)//只取时间最短的航线
                    {
                        MinTime = p->LineInfo.ArrTime - p->LineInfo.DepTime;
                        MinIDtrace[0] = p->LineInfo.FlightID;//记录航线ID
                    }
                    p = p->next;//遍历下一条相关的航线
                    continue;
                }

                //其他所有航线生成结点入栈
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//当前路径长
                node->StartTime = p->LineInfo.DepTime;//起始时间为出发时间
                node->CurTime = p->LineInfo.ArrTime;//当前时间为此航线的抵达时间
                node->SumTime = node->CurTime - node->StartTime; //总耗时
                node->TraceAirport[0] = G.vexs[StartPos].data; //路径经过的机场
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//入栈
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//栈非空，进行DFS，同时在遍历过程中进行一系列剪枝操作，做到尽可能的优化
    {
        Path *pNode = PathNode.top();//取栈顶元素
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//当前所在机场
        if(pNode->SumTime > MinTime)//当前路径花费的时间已经多于最短的时间，无需操作，进行剪枝
        {
            continue;
        }

        if(CurAirport == ArrAirport)//如果已经到达目的机场，则进行判断
        {
            if(pNode->SumTime < MinTime)//总耗时小于当前最短时间，则进行相应的更新
            {
                MinTime = pNode->SumTime; //更改最短耗时

                TraceLen = pNode->TraceLen;//修改标记路径长
                for(int i = 0; i < TraceLen; i++)//将此结点存储的路径复制给MinAirportTrace当作暂时的最短路径
                    MinAirportTrace[i] = pNode->TraceAirport[i];//修改标记数组信息
                for(int i = 0; i < TraceLen - 1; i++)
                    MinIDtrace[i] = pNode->TraceID[i];//修改标记数组信息
            }
            continue;//更新后当前结点无需再进行后续操作
        }

        int CurPos = LocateVex(G, CurAirport);//当前的机场在顶点向量中的下标

        for(int i = 0; i < G.vexnum; i++)//遍历此结点当前所在机场的邻接矩阵的一行
        {
            if(G.arcs[CurPos][i] && i != StartPos)//保证该位置有航线且路径上不出现起始机场
            {
                ArcCell *p = G.arcs[CurPos][i];//用以遍历航线，选取可行的航线
                ArcCell *q = NULL; //用于去掉那些可以但晚到的航班，即前一班的抵达时间在后一班起飞时间之后，此种情况不符合要求
                int MinArr = INFINITY;//最早抵达下一个机场的时间
                bool IsThrough = false;//用于表示当前遍历的机场是否已经出现在路径中，若没有出现则为false
                for(int j = 0; j < pNode->TraceLen; j++)//遍历路径中所有走过的机场
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//当前机场已经出现在路径中，进行剪枝
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//只有未经过的机场才有必要继续走
                {
                    while(p)//遍历与此机场相关的所有航线
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime ) //此趟航班的起飞时间在当前时间（即抵达此机场的时间）之后，可以通行
                        {
                            if(p->LineInfo.ArrTime - pNode->CurTime < MinArr)//选择到达下一个机场最早的一趟航班
                            {
                                MinArr = p->LineInfo.ArrTime - pNode->CurTime;
                                q = p;
                            }
                        }
                        p = p->next;
                    }
                }

                if(q)//找到可以通行的当前最优航班
                {
                    p = q;
                    Path *newNode = (Path*)malloc(sizeof(Path));
                    newNode->TraceLen = pNode->TraceLen + 1;
                    newNode->CurTime = p->LineInfo.ArrTime;
                    newNode->StartTime = pNode->StartTime;
                    newNode->SumTime = newNode->CurTime - newNode->StartTime;//总耗时
                    newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;

                    for(int k = 0; k < pNode->TraceLen - 1; k++)//复制路径上的航班ID
                    {
                        newNode->TraceID[k] = pNode->TraceID[k];
                    }
                    for(int k = 0; k < pNode->TraceLen; k++)//复制路径上的机场
                    {
                        newNode->TraceAirport[k] = pNode->TraceAirport[k];
                    }
                    newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                    PathNode.push(newNode);
                }

            }
        }
        delete pNode;
    }

    cout << "Done!" << endl;
    if(MinTime == INFINITY)
    {
        cout << "无法抵达！" << endl;
        return;
    }

    cout << "最短时间为：" << MinTime << "min" << endl;
    cout << "路径为：" << endl << "航班ID:";
    int i = 0;
    for(i = 0; i < TraceLen - 2; i++)
        cout << MinIDtrace[i] << "->";

    cout << MinIDtrace[i] << endl << "机场：";

    for(i = 0; i < TraceLen - 1; i++)
        cout << MinAirportTrace[i] << "->";

    cout << MinAirportTrace[i] << endl;
}

//初始条件：图G存在且以邻接矩阵形式存储，start是起始机场的编号，terminal是目标机场的编号
//操作结果：仅限直飞或1次中转，打印输出任意两个机场的航线（航班ID顺序表）
void Mission4(MGraph G)
{
    int start, terminal;
    cout << "请输入出发机场和目的机场：";
    cin >> start >> terminal;

    if(start == terminal)
    {
        cout << "错误输入！起始位置与终止位置相同" << endl;
        return;
    }
    int StartPos = LocateVex(G, start);
    int TerminalPos = LocateVex(G, terminal);
    if(StartPos == -1 || TerminalPos == -1)
    {
        cout << "错误输入！无此机场编号" << endl;
        return;
    }

    int flag1 = 0;//能否直飞，不能时为0，能时为1
    if(G.arcs[StartPos][TerminalPos])
    {
        ArcCell* p = G.arcs[StartPos][TerminalPos];
        cout << "可以直飞！" << endl;
        cout << "航班ID为：" << p->LineInfo.FlightID;
        while(p->next)
        {
            p = p->next;
            cout << "或" << p->LineInfo.FlightID;
        }
        cout << endl << endl;
        flag1 = 1;
        return;
    }
    else
    {
        cout << "不能直飞抵达！" << endl;
    }


    int flag2 = 0;//是否可以经过一次转机抵达，若能则为1,不能则为0

    int PrintNum = 0; //打印输出次数
    for(int i = 0; i < G.vexnum; i++)
    {
        ArcCell* p = G.arcs[StartPos][i];
        while(p)
        {
            if(G.arcs[i][TerminalPos])//找到对应的路线
            {
                ArcCell* q = G.arcs[i][TerminalPos];
                while(q)
                {
                    //比较时间，保证前一个航班的抵达时间在后一个航班出发时间之前
                    if(p->LineInfo.ArrTime < q->LineInfo.DepTime)//比较每条路径
                    {
                        flag2 = 1;
                        if(PrintNum == 0)
                        {
                            cout << "可以经过一次转机抵达！" << endl;
                            PrintNum++;
                        }
                        cout << "航班ID为：" << p->LineInfo.FlightID << "->" << q->LineInfo.FlightID << endl;
                    }
                    q = q->next;
                }
            }
            p = p->next;
        }
    }
    if(flag1 == 0 && flag2 == 0)
    {
        cout << "仅限直飞或1次中转时，无法抵达！" << endl;
    }
}

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：给定起飞时段或者降落时段或者机型要求, 打印输出任意两个机场的多个备选航线（航班ID顺序表）
void Mission5(MGraph G)
{
    //算法思想与Mission3类似

    cout << "请输入出发机场与目的机场的序号：";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "错误输入！出发机场和目的机场相同！" << endl;
        return;
    }

    int StartPos = LocateVex(G, DepAirport); //出发机场在顶点向量中的位置下标
    int TerminalPos = LocateVex(G, ArrAirport); //目的机场在顶点向量中的位置下标

    Req r;//用以存储用户的各项需求
    cout << "!!请尽可能多的加要求，否则可能路径会很多。如果可能路径过多，则仅输出前2000条航线，每统计出100000条航线则输出“Loading...”一次。" << endl;
    Request(r);//用户输入需求

    stack<Path*> PathNode;//路径结点,存储路径上的相关信息

    int FlightNum = 0;//用以统计航线数量
    for(int i = 0; i < G.vexnum; i++)//以起始机场为起点的结点入栈
    {
        if(G.arcs[StartPos][i])//当前位置有航线
        {
            ArcCell* p = G.arcs[StartPos][i];//用以遍历以此结点为头的所有航线
            while(p)//遍历与此结点相关的所有航线
            {
                if(!IsMatchReq(r, 0, p))//当前结点不满足起飞时段要求，直接跳过
                {
                    p =p->next;
                    continue;
                }
                if(i == TerminalPos)//直达目的机场
                {
                    if(IsMatchReq(r, 1, p))//抵达时段在要求范围内
                    {
                        FlightNum++;
                        cout << "路径" << FlightNum << ": " << p->LineInfo.FlightID << endl;
                    }
                    p = p->next;//遍历下一条相关的航线
                    continue;
                }

                //其他所有航线生成结点入栈
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//当前路径长
                node->StartTime = p->LineInfo.DepTime;//起始时间为出发时间
                node->CurTime = p->LineInfo.ArrTime;//当前时间为此航线的抵达时间
                node->SumTime = node->CurTime - node->StartTime; //总耗时
                node->TraceAirport[0] = G.vexs[StartPos].data; //路径经过的机场
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//入栈
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//栈非空，进行DFS，在遍历过程中进行简单的剪枝操作
    {
        Path *pNode = PathNode.top();//取栈顶元素
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//当前所在机场

        //第一批新生成的结点中的最后一个机场不会为目的机场,
        //之后生成的结点理论上最后一个结点也不会为目的机场，因为只要到目的机场且符合要求则直接输出。
        //此处加上一个判断作为健壮性的体现。
        if(CurAirport == ArrAirport)
        {
            cout << "入栈结点出现错误！" << endl;
            return;
        }

        int CurPos = LocateVex(G, CurAirport);//当前的机场在定点向量中的下标

        for(int i = 0; i < G.vexnum; i++)
        {
            if(G.arcs[CurPos][i] && i != StartPos)//保证路径上不出现起始机场
            {
                ArcCell *p = G.arcs[CurPos][i];
                if(i == TerminalPos)//抵达目标机场
                {
                    while(p)
                    {
                        if(IsMatchReq(r, 2, p) && p->LineInfo.DepTime > pNode->CurTime)//符合抵达时间要求且此趟航班起飞时间在当前时间之后（现实中不可能等于）
                        {
                            FlightNum++;
                            if(FlightNum <= 2000)//仅打印输出前2000条
                            {
                                cout << "路径" << FlightNum << ": ";
                                for(int j = 0; j < pNode->TraceLen - 1; j++)
                                    cout << pNode->TraceID[j] << "->";

                                cout << p->LineInfo.FlightID << endl;
                            }
                            else if(FlightNum % 100000 == 0)//是10万的倍数
                            {
                                cout << "Loading..." << endl;
                            }
                        }
                        p = p->next;
                    }
                    continue;
                }

                bool IsThrough = false;//用于表示当前遍历的机场是否已经出现在路径中，若没有出现则为false
                for(int j = 0; j < pNode->TraceLen; j++)//遍历路径中所有走过的机场
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//当前机场已经出现在路径中，进行剪枝
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//只有未经过的机场才有必要继续走
                {
                    while(p)//遍历与此机场相关的所有航线
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime) //此趟航班的起飞时间在当前时间（即抵达此机场的时间）之后，可以通行
                        {
                            if(IsMatchReq(r, 2, p))//符合机型要求
                            {
                                Path *newNode = (Path*)malloc(sizeof(Path));
                                newNode->TraceLen = pNode->TraceLen + 1;
                                newNode->CurTime = p->LineInfo.ArrTime;
                                newNode->StartTime = pNode->StartTime;
                                newNode->SumTime = newNode->CurTime - newNode->StartTime;
                                newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;//将当前航线的ID信息存在新结点的路径信息中

                                for(int k = 0; k < pNode->TraceLen - 1; k++)
                                {
                                    newNode->TraceID[k] = pNode->TraceID[k];
                                }
                                for(int k = 0; k < pNode->TraceLen; k++)
                                {
                                    newNode->TraceAirport[k] = pNode->TraceAirport[k];
                                }
                                newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                                PathNode.push(newNode);
                            }
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
        pNode = NULL;
    }

    cout << "Done!" << endl;
    if(FlightNum == 0)
    {
        cout << "无法抵达！" << endl;
        return;
    }
    else
    {
        cout << "可行的不同路径数量总计为：" << FlightNum << endl;
    }
}

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：给定起飞时段或者降落时段或者机型要求，打印输出任意两个机场之间的航费（机票价格）最低的路径
void Mission6(MGraph G)
{
    //算法思想与Mission3类似

    cout << "请输入出发机场与目的机场的序号：";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "错误输入！出发机场和目的机场相同！" << endl;
        return;
    }

    int StartPos = LocateVex(G, DepAirport); //出发机场在顶点向量中的位置下标
    int TerminalPos = LocateVex(G, ArrAirport); //目的机场在顶点向量中的位置下标

    Req r;
    cout << "!!请尽可能多的加要求，否则求解时间可能会很长！" << endl;
    Request(r);//用户输入需求

    int MinFare = INFINITY;//用以记录所有可以抵达目的机场的航线中的最短航费
    int MinAirportTrace[G.vexnum] = {G.vexs[StartPos].data, G.vexs[TerminalPos].data, 0}; //标记数组，存储费用最少的路径的机场信息
    int MinIDtrace[G.vexnum] = {0}; //标记数组，存储费用最少的路径的航班ID
    int TraceLen = 2; //路径长度，初始值为2，表示最少是两个机场

    stack<Path*> PathNode;//路径结点,存储路径上的相关信息

    cout << "Loading..." << endl;

    for(int i = 0; i < G.vexnum; i++)//以起始机场为起点的结点入栈
    {
        if(G.arcs[StartPos][i])//当前位置有航线
        {
            ArcCell* p = G.arcs[StartPos][i];//用以遍历以此结点为头的所有航线
            while(p)//遍历与此结点相关的所有航线
            {
                if(!IsMatchReq(r, 0, p))//不满足起飞时段的要求
                {
                    p = p->next;
                    continue;
                }

                if(i == TerminalPos)//找所有能直达目的机场的航线中的最短时间，此结点不需要创建和入栈，只需要确定最短时间，作为时间的上界
                {
                    if(IsMatchReq(r, 1, p))//满足抵达时间要求，此时不存在转机的问题
                    {
                        if(p->LineInfo.AirFare < MinFare)//只取时间最短的航线
                        {
                            MinFare = p->LineInfo.AirFare;
                            MinIDtrace[0] = p->LineInfo.FlightID;
                            TraceLen = 2;
                        }
                    }

                    p = p->next;//遍历下一条相关的航线
                    continue;
                }

                //其他所有航线生成结点入栈
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//当前路径长
                node->StartTime = p->LineInfo.DepTime;//起始时间为出发时间
                node->CurTime = p->LineInfo.ArrTime;//当前时间为此航线的抵达时间
                node->SumTime = node->CurTime - node->StartTime; //总耗时
                node->SumFare = p->LineInfo.AirFare;//当前总费用
                node->TraceAirport[0] = G.vexs[StartPos].data; //路径经过的机场
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//入栈
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//栈非空，进行DFS，在遍历过程中进行一系列剪枝操作，做到尽可能的优化
    {
        Path *pNode = PathNode.top();//取栈顶元素
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//当前所在机场

        if(CurAirport == ArrAirport)//如果已经到达目的机场
        {
            delete pNode;
            continue;
        }
        int CurPos = LocateVex(G, CurAirport);//当前的机场在顶点向量中的下标

        for(int i = 0; i < G.vexnum; i++)
        {
            if(G.arcs[CurPos][i] && i != StartPos)//保证路径上不出现起始机场
            {
                ArcCell *p = G.arcs[CurPos][i];
                if(i == TerminalPos)//目的机场
                {
                    while(p)
                    {
                        if(IsMatchReq(r, 1, p) && p->LineInfo.DepTime > pNode->CurTime)//符合抵达时间要求以及转机要求
                        {
                            int SumFare = pNode->SumFare + p->LineInfo.AirFare;
                            if(SumFare < MinFare)
                            {
                                MinFare = SumFare;
                                TraceLen = pNode->TraceLen + 1;
                                int j;
                                for(j = 0; j < TraceLen - 2; j++)//更新ID信息
                                    MinIDtrace[j] = pNode->TraceID[j];
                                MinIDtrace[j] = p->LineInfo.FlightID;

                                for(j = 0; j < TraceLen - 1; j++)//更新机场信息
                                    MinAirportTrace[j] = pNode->TraceAirport[j];
                                MinAirportTrace[j] = p->LineInfo.ArrAirport;
                            }
                        }
                        p = p->next;
                    }
                    continue;
                }

                bool IsThrough = false;//用于表示当前遍历的机场是否已经出现在路径中，若没有出现则为false
                for(int j = 0; j < pNode->TraceLen; j++)//遍历路径中所有走过的机场
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//当前机场已经出现在路径中，进行剪枝
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//只有未经过的机场才有必要继续走
                {
                    while(p)//遍历与此机场相关的所有航线
                    {
                        if(p->LineInfo.DepTime > pNode->CurTime) //此趟航班的起飞时间在当前时间（即抵达此机场的时间）之后，可以通行
                        {
                            if(IsMatchReq(r, 2, p) && (pNode->SumFare + p->LineInfo.AirFare) < MinFare)//符合机型要求并且航费要小于当前抵达目的机场的最少航费
                            {
                                Path *newNode = (Path*)malloc(sizeof(Path));
                                newNode->TraceLen = pNode->TraceLen + 1;
                                newNode->CurTime = p->LineInfo.ArrTime;
                                newNode->StartTime = pNode->StartTime;
                                newNode->SumTime = newNode->CurTime - newNode->StartTime;
                                newNode->SumFare = pNode->SumFare + p->LineInfo.AirFare;

                                for(int k = 0; k < newNode->TraceLen - 2; k++)
                                {
                                    newNode->TraceID[k] = pNode->TraceID[k];
                                }
                                newNode->TraceID[newNode->TraceLen - 2] = p->LineInfo.FlightID;//TraceLen记录路径中的机场数，而航班ID数比机场数少一

                                for(int k = 0; k < newNode->TraceLen - 1; k++)
                                {
                                    newNode->TraceAirport[k] = pNode->TraceAirport[k];
                                }
                                newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;

                                newNode->SumFare = pNode->SumFare + p->LineInfo.AirFare;//总费用的改变
                                PathNode.push(newNode);
                            }
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
    }

    cout << "Done!" << endl;
    if(MinFare == INFINITY)
    {
        cout << "无法抵达！" << endl;
        return;
    }

    cout << "最短航费为：" << MinFare << endl;
    cout << "路径为：" << endl << "航班ID:";
    int i = 0;
    for(i = 0; i < TraceLen - 2; i++)
        cout << MinIDtrace[i] << "->";

    cout << MinIDtrace[i] << endl << "机场：";

    for(i = 0; i < TraceLen - 1; i++)
        cout << MinAirportTrace[i] << "->";

    cout << MinAirportTrace[TraceLen - 1] << endl;
}

//初始条件：图G存在且以邻接矩阵形式存储
//操作结果：给定飞行时长或者中转时间限制，打印输出任意两个机场的多个备选航线（航班ID顺序表）
void Mission7(MGraph G)
{
    //算法思想与Mission3类似

    cout << "请输入出发机场与目的机场的序号：";
    int DepAirport, ArrAirport;
    cin >> DepAirport >> ArrAirport;

    if(DepAirport == ArrAirport)
    {
        cout << "错误输入！出发机场和目的机场相同！" << endl;
        return;
    }

    int TransUpLimit = INFINITY, TransDownLimit = 0;//分别为转机时间的上下界,默认分别为无穷大和0
    int FlightMaxTime = INFINITY, FlightMinTime = 0; //分别为飞行的最长时间和最短时间，默认分别为无穷大和0

    cout << "!!请输入尽可能多的要求，不然解集会很大" << endl;//可以加上仅前2000条输出
    cout << "请分别输入飞行时长的下界与上界（以分钟为单位，无则输入-1 -1）：";
    cin >> FlightMinTime >> FlightMaxTime;
    if(FlightMinTime == -1)//无要求
    {
        FlightMaxTime = INFINITY;
        FlightMinTime = 0;
    }

    cout << "请分别输入每次转机时长的下界与上界（以分钟为单位，无则输入-1 -1）：";
    cin >> TransDownLimit >> TransUpLimit;
    if(TransDownLimit == -1)
    {
        TransUpLimit = INFINITY;
        TransDownLimit = 0;
    }
    int StartPos = LocateVex(G, DepAirport); //出发机场在顶点向量中的位置下标
    int TerminalPos = LocateVex(G, ArrAirport); //目的机场在顶点向量中的位置下标

    stack<Path*> PathNode;//路径结点,存储路径上的相关信息

    cout << "Loading..." << endl;

    int FlightNum = 0;//用以统计航线数量
    for(int i = 0; i < G.vexnum; i++)//以起始机场为起点的结点入栈
    {
        if(G.arcs[StartPos][i])//当前位置有航线
        {
            ArcCell* p = G.arcs[StartPos][i];//用以遍历以此结点为头的所有航线
            while(p)//遍历与此结点相关的所有航线
            {
                if(p->LineInfo.ArrTime - p->LineInfo.DepTime < FlightMinTime ||
                        p->LineInfo.ArrTime - p->LineInfo.DepTime > FlightMaxTime)//当前结点不满足飞行时间要求，直接跳过
                {
                    p = p->next;
                    continue;
                }
                if(i == TerminalPos)//直达目的机场，无需中转
                {

                    FlightNum++;
                    cout << "路径" << FlightNum << ": " << p->LineInfo.FlightID << endl;

                    p = p->next;//遍历下一条相关的航线
                    continue;
                }

                //其他所有航线生成结点入栈
                Path *node = (Path*)malloc(sizeof(Path));
                node->TraceLen = 2;//当前路径长
                node->StartTime = p->LineInfo.DepTime;//起始时间为出发时间
                node->CurTime = p->LineInfo.ArrTime;//当前时间为此航线的抵达时间
                node->SumTime = node->CurTime - node->StartTime; //总耗时
                node->TraceAirport[0] = G.vexs[StartPos].data; //路径经过的机场
                node->TraceAirport[1] = G.vexs[i].data;
                node->TraceID[0] = p->LineInfo.FlightID;
                PathNode.push(node);//入栈
                p = p->next;
            }
        }
    }

    while(!PathNode.empty())//栈非空，进行DFS，在遍历过程中进行简单的剪枝操作
    {
        Path *pNode = PathNode.top();//取栈顶元素
        PathNode.pop();

        int CurAirport = pNode->TraceAirport[pNode->TraceLen - 1];//当前所在机场

        if(pNode->SumTime > FlightMaxTime)//若当前结点所用总时间已经大于时间上限,无需再判断
            continue;

        if(CurAirport == ArrAirport)//如果栈顶元素的机场为目的机场，则此结点出错，需要返回
        {
            cout << "当前结点出错！" << endl;
            return;
        }

        int CurPos = LocateVex(G, CurAirport);//当前的机场在定点向量中的下标

        for(int i = 0; i < G.vexnum; i++)
        {
            if(G.arcs[CurPos][i] && i != StartPos)//保证路径上不出现起始机场
            {
                ArcCell *p = G.arcs[CurPos][i];//用以遍历单链表

                if(i == TerminalPos)//抵达目标机场
                {
                    while(p)
                    {
                        int SumTime = p->LineInfo.ArrTime - pNode->StartTime;//如果乘坐此航班的总耗时
                        int TransTime = p->LineInfo.DepTime - pNode->CurTime;//如果乘坐此航班的转机时长，若无法转机，则此时长会为负值
                        if((TransTime >= TransDownLimit && TransTime <= TransUpLimit)
                                && (SumTime >= FlightMinTime && SumTime <= FlightMaxTime))//符合转机要求以及总航行时间的要求
                        {
                            FlightNum++;
                            if(FlightNum <= 2000)
                            {
                                cout << "路径" << FlightNum << ": ";
                                for(int j = 0; j < pNode->TraceLen - 1; j++)
                                    cout << pNode->TraceID[j] << "->";

                                cout << p->LineInfo.FlightID << endl;
                            }
                            else if(FlightNum % 100000 == 0)//是10万的倍数
                            {
                                cout << "Loading..." << endl;
                            }
                        }
                        p = p->next;
                    }
                    continue;
                }

                bool IsThrough = false;//用于表示当前遍历的机场是否已经出现在路径中，若没有出现则为false
                for(int j = 0; j < pNode->TraceLen; j++)//遍历路径中所有走过的机场
                {
                    if(G.vexs[i].data == pNode->TraceAirport[j])//当前机场已经出现在路径中，进行剪枝
                    {
                        IsThrough = true;
                        break;
                    }
                }

                if(!IsThrough)//只有未经过的机场才有必要继续走
                {
                    while(p)//遍历与此机场相关的所有航线
                    {
                        int SumTime = p->LineInfo.ArrTime - pNode->StartTime;//如果乘坐此航班的总耗时
                        int TransTime = p->LineInfo.DepTime - pNode->CurTime;//如果乘坐此航班的转机时长，若无法转机，则此时长会为负值
                        if(TransTime >= TransDownLimit && TransTime <= TransUpLimit) //此趟航班的转机时间在要求范围内
                        {
                            if(SumTime <= FlightMaxTime)//当前所用时间还未超过航行时间上限的航班才有意义
                            {
                                Path *newNode = (Path*)malloc(sizeof(Path));
                                newNode->TraceLen = pNode->TraceLen + 1;
                                newNode->CurTime = p->LineInfo.ArrTime;
                                newNode->StartTime = pNode->StartTime;
                                newNode->SumTime = newNode->CurTime - newNode->StartTime;

                                for(int k = 0; k < pNode->TraceLen - 1; k++)
                                {
                                    newNode->TraceID[k] = pNode->TraceID[k];
                                }
                                newNode->TraceID[pNode->TraceLen - 1] = p->LineInfo.FlightID;

                                for(int k = 0; k < pNode->TraceLen; k++)
                                {
                                    newNode->TraceAirport[k] = pNode->TraceAirport[k];
                                }
                                newNode->TraceAirport[newNode->TraceLen - 1] = G.vexs[i].data;
                                PathNode.push(newNode);
                            }
                        }
                        p = p->next;
                    }
                }
            }
        }
        delete pNode;
    }

    cout << "Done!" << endl;
    if(FlightNum == 0)
    {
        cout << "无法抵达！" << endl;
        return;
    }
    else
    {
        cout << "可行的不同路径数量总计为：" << FlightNum << endl;
    }
}
