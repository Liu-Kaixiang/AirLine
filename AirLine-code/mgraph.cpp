#include "mgraph.h"

//��ʼ�����������ͼG
//�������������ͼG�����ڽӾ���洢
void CreateGraph(MGraph &G)
{
    //һ��ע��ָ���ʼ��Ϊ��ָ��
    for(int i = 0; i < G.vexnum; i++)
    {
        for(int j = 0; j < G.vexnum; j++)
        {
            G.arcs[i][j] = NULL;//�ڽӾ���ÿ��λ�ó�ʼֵΪ��
        }
    }

    G.arcnum = LineNum;

    //�����㷨ʵ�ֻ�����������Լ�vexs���������ĳ�ʼ��
    int AirportNum = 0;
    G.vexs[AirportNum].data = airline[0].DepAirport;//����ɻ����ȸ�ֵ��Ϊ����
    G.vexs[AirportNum].IsVisited = false;//��ʼ��δ������
    AirportNum++;
    for(int i = 1; i < LineNum; i++)//����������ɻ���
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vexs[j].data == airline[i].DepAirport)//�Ѵ洢�Ķ�����Ϣ�뵱ǰ������ͬ
                break;
        }
        if(j >= AirportNum)//�����µĻ���
        {
            G.vexs[AirportNum].data = airline[i].DepAirport;
            G.vexs[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }

    for(int i = 0; i < LineNum; i++)//�������еִ����
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vexs[j].data == airline[i].ArrAirport)
                break;
        }
        if(j >= AirportNum)//�����µĻ���
        {
            G.vexs[AirportNum].data = airline[i].ArrAirport;
            G.vexs[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }
    G.vexnum = AirportNum;//������

    //�����㷨ʵ���ڽӾ���arcs�ĳ�ʼ��
    for(int i = 0; i < LineNum; i++)
    {
        //ȷ����ǰ����Ӧ���洢������λ��
        int row = LocateVex(G, airline[i].DepAirport);//��ɻ����ڶ��������е�λ��
        int col = LocateVex(G, airline[i].ArrAirport);//�ִ�����ڶ��������е�λ��
        //cout << i << ": " << row << "  " << col << endl;
        ArcCell* p = (ArcCell*)malloc(sizeof(ArcCell)); //�����µĽ��ռ�


        //����ͷ�巨��������
        p->LineInfo = airline[i];
        p->next = NULL;

        //��ͳ�ƣ���Լֻ��400������������ֱ��
        if(!G.arcs[row][col])//���ڵ�һ����㣬ֱ�ӽ��丳ֵ���ڽӾ���
        {
            G.arcs[row][col] = p;//������Ϊָ��ָ�򣬲�����Ҫmalloc�ռ�
        }
        else
        {
            p->next = G.arcs[row][col]->next;
            G.arcs[row][col]->next = p;
        }
    }
}

//��ʼ������ͼG���������ڽӾ���洢��v��G��ĳ��������±�
//�������������v�ĵ�һ���ڽӶ���λ�ã���������G��û���ڽӵ㣬�򷵻�-1
int FirstAdjVex(MGraph G,int v)//�����ڽӾ�����Ĳ�ͬ��Ҫ�޸�
{
    for(int i = 0; i < G.vexnum; i++)
    {
        if(G.arcs[v][i])//���ڽӾ���ǰλ�ò��ǿ�ָ�룬���ҵ�
            return i;
    }
    return -1; //δ�ҵ�
}

//��ʼ������ͼG���������ڽӾ���洢��v��G��ĳ��������±꣬w��v���ڽӶ�����±�
//�������������v�ģ������w������һ���ڽӶ���λ�ã���w��v�����һ���ڽӵ㣬�򷵻�-1
int NextAdjVex(MGraph G, int v, int w)
{
    for(int i = w + 1; i < G.vexnum; i++)//��wλ��֮�����
    {
        if(G.arcs[v][i])//���ڽӾ���ǰλ�ò��ǿ�ָ�룬���ҵ�
            return i;
    }
    return -1; //δ�ҵ�
}


//��ʼ������ͼG���������ڽӾ���洢��vertexΪ�����еĻ�����Ϣ
//�����������G�д��ڶ���vertex���򷵻�����ͼ�е�λ�ã����򷵻�-1
int LocateVex(MGraph G, int vertex)
{
    for(int i = 0; i < G.vexnum; i++)
    {
        if(G.vexs[i].data == vertex) //�ҵ�
            return i;
    }
    return -1;//δ�ҵ�
}

//��ʼ������ͼG���������ڽӱ�洢��v��G��ĳ��������±�
//�����������ӡ�����vΪ���Ĺ�����ȱ���
void BFSTraverse(MGraph &G, int start, int terminal)
{
    for(int i = 0; i < G.vexnum; i++)//��ʼ������Ҫ��ÿ�α����Ժ�IsVisited���ᱻ�޸�
    {
        G.vexs[i].IsVisited = false;
    }
    queue<int> que;

    int StartPos = LocateVex(G, start); //��ʼ�����ڶ��������е��±�
    int TerminalPos = LocateVex(G, terminal); //Ŀ�Ļ����ڶ��������е��±�

    if(StartPos == -1 || TerminalPos == -1)
    {
        cout << "û�д˻�����ţ�" << endl;
        return;
    }

    if(!G.vexs[StartPos].IsVisited)//��ǰ���δ������
    {
        G.vexs[StartPos].IsVisited = true; //����Ϊ�Ѿ����ʹ�
        que.push(StartPos);//�����
        while(!que.empty()) //�����в���ʱ
        {
            int u = que.front(); //ȡ����Ԫ��
            que.pop();
            for(int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) //������˶��������������ڽӵ�
            {
                if(!G.vexs[w].IsVisited && w != TerminalPos)
                {
                    G.vexs[w].IsVisited = true;
                    que.push(w);//�����

                }
                else if(w == TerminalPos)
                {
                    cout << "������ͨ��" << endl;
                    return;
                }
            }
        }
    }
    cout << "��������ͨ��" << endl;
    //return -1;
}

//��ʼ������ͼG���������ڽӾ�����ʽ�洢��v��ͼG��ĳ��������±�
//������������ʸö������Ϣ������ӡ�����Ӧ�Ļ�����Ϣ
void Visit(MGraph G, int v)
{
    cout << G.vexs[v].data << "  ";
}


