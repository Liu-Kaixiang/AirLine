#include "algraph.h"

//��ʼ�����������ͼG
//�������������ͼG�����ڽӱ�洢
void CreateGraph(ALGraph &G)
{
    G.arcnum = LineNum;
    int AirportNum = 0;
    G.vertices[AirportNum].data = airline[0].DepAirport;//����ɻ����ȸ�ֵ��Ϊ����
    G.vertices[AirportNum].firstarc = NULL;//��ʼ��Ϊ0
    G.vertices[AirportNum].IsVisited = false;//��ʼ��δ������
    AirportNum++;
    for(int i = 1; i < LineNum; i++)//����������ɻ���
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vertices[j].data == airline[i].DepAirport)//�Ѵ洢�Ķ�����Ϣ�뵱ǰ������ͬ
                break;
        }
        if(j >= AirportNum)//�����µĻ���
        {
            G.vertices[AirportNum].data = airline[i].DepAirport;
            G.vertices[AirportNum].firstarc = NULL;
            G.vertices[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }

    for(int i = 0; i < LineNum; i++)//�������еִ����
    {
        int j = 0;
        for(; j < AirportNum; j++)
        {
            if(G.vertices[j].data == airline[i].ArrAirport)
                break;
        }
        if(j >= AirportNum)//�����µĻ���
        {
            G.vertices[AirportNum].data = airline[i].ArrAirport;
            G.vertices[AirportNum].firstarc = NULL;
            G.vertices[AirportNum].IsVisited = false;
            AirportNum++;
        }
    }

    G.vexnum = AirportNum;//������

    for(int i = 0; i < LineNum; i++)
    {
        int flag = 0; //���ڱ�ʾ�ִ�����Ƿ��Ѿ������ڽӱ�Ĭ��δ����
        int pos = LocateVex(G, airline[i].DepAirport);//��ɻ����ڶ��������е�λ��
        ArcNode* p = G.vertices[pos].firstarc;//���ڱ����ڽӱ�
        while(p)
        {
            if(G.vertices[p->adjvex].data == airline[i].ArrAirport)//�����ǰ�������Ѿ������˴˺����µĵִ����
            {
                flag = 1;
                break;
            }
            p = p->nextarc;
        }
        if(flag == 1)//������ͬ�����߲�ͬ���������Ӳ�ͬ������Ϣ
        {
            continue;
        }
        else //������ͬ
        {
            //ͷ�巨
            ArcNode* q = (ArcNode*)malloc(sizeof(ArcNode));
            q->nextarc = G.vertices[pos].firstarc;
            q->adjvex = LocateVex(G, airline[i].ArrAirport);
            G.vertices[pos].firstarc = q;
        }
    }
}

//��ʼ������ͼG���������ڽӱ�洢��v��G��ĳ��������±�
//�������������v�ĵ�һ���ڽӶ���λ�ã���������G��û���ڽӵ㣬�򷵻�-1
int FirstAdjVex(ALGraph G, int v)
{
    if(G.vertices[v].firstarc == NULL)
        return -1;//û���ڽӵ�
    else
        return G.vertices[v].firstarc->adjvex;//���ص�һ���ڽӵ�洢��λ����Ϣ
}

//��ʼ������ͼG���������ڽӱ�洢��v��G��ĳ��������±꣬w��v���ڽӶ�����±�
//�������������v�ģ������w������һ���ڽӶ���λ�ã���w��v�����һ���ڽӵ㣬�򷵻�-1
int NextAdjVex(ALGraph G, int v, int w)
{
    ArcNode* p = G.vertices[v].firstarc;
    while(p != NULL)//������ö�����صĶ���
    {
        if(p->adjvex == w)//pָ��w���ڽ���λ��
        {
            if(p->nextarc)//��w֮���н���򷵻ض�Ӧ����е�adjvexֵ
                return p->nextarc->adjvex;
            else
                return -1;//��w���޺�̣��򷵻�-1����ʾ���ա�
        }
        p = p->nextarc;//ָ����һ�����
    }
    //return ERROR;//w����v���ڽӶ��㣬�������
    return -1;
}

//��ʼ������ͼG���������ڽӱ�洢��vertexΪ�����еĻ�����Ϣ
//�����������G�д��ڶ���vertex���򷵻�����ͼ�е�λ�ã����򷵻�-1
int LocateVex(ALGraph G, int vertex)
{
    for(int i = 0; i < G.vexnum; i++)
    {
        if(vertex == G.vertices[i].data)//��λ����Ӧ����λ��
            return i;
    }
    return -1;//δ�ҵ�
}

//��ʼ������ͼG���������ڽӱ�洢��ͼG��ÿ�����㶼δ������������IsVisitedֵΪfalse��v��G��ĳ��������±�
//�����������ӡ�����vΪ����������ȱ���
void DFS(ALGraph &G, int v) //�˴������&
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

//��ʼ������ͼG���������ڽӱ�洢����ͼG��IsVisitedֵ��Ҫ��v��G��ĳ��������±�
//�����������ӡ�����vΪ����������ȱ���
void DFSTraverse(ALGraph &G, int v)
{
    for(int i = 0; i < G.vexnum; i++)//��ʼ������Ҫ��ÿ�α����Ժ�IsVisited���ᱻ�޸�
    {
        G.vertices[i].IsVisited = false;
    }
    DFS(G, v);
}

//��ʼ������ͼG���������ڽӱ�洢��v��G��ĳ��������±�
//�����������ӡ�����vΪ���Ĺ�����ȱ���
void BFSTraverse(ALGraph &G, int v)
{
    for(int i = 0; i < G.vexnum; i++)//��ʼ������Ҫ��ÿ�α����Ժ�IsVisited���ᱻ�޸�
    {
        G.vertices[i].IsVisited = false;
    }
    queue<int> que;
    if(!G.vertices[v].IsVisited)//��ǰ���δ������
    {
        G.vertices[v].IsVisited = true; //����Ϊ�Ѿ����ʹ�
        Visit(G, v);//������Ϣ
        que.push(v);//�����
        while(!que.empty()) //�����в���ʱ
        {
            int u = que.front(); //ȡ����Ԫ��
            que.pop();
            for(int w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w)) //������˶��������������ڽӵ�
            {
                if(!G.vertices[w].IsVisited)
                {
                    G.vertices[w].IsVisited = true;
                    Visit(G, w);
                    que.push(w);//�����
                }
            }
        }
    }
}

//��ʼ������ͼG���������ڽӱ���ʽ�洢��v��ͼG��ĳ��������±�
//������������ʸö������Ϣ������ӡ�����Ӧ�Ļ�����Ϣ
void Visit(ALGraph G, int v)
{
    cout << G.vertices[v].data << "  ";
}
