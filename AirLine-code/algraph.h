#ifndef ALGRAPH_H
#define ALGRAPH_H
/***���ļ�ʵ���ڽӱ�Ĵ洢�ͻ�����������***/

#include "datadefine.h"

//�ڽӱ�ͷ�巨����������������ܰ����������ߣ������ߵ���Ϣ��ͬ
typedef struct ArcNode
{
    int adjvex; //�û���ָ��Ķ����λ��
    struct ArcNode *nextarc; //ָ����һ������ָ��
}ArcNode;

typedef struct VNode
{
    int data; //������Ϣ��������
    ArcNode *firstarc; //ָ���һ�������ö���Ļ�
    bool IsVisited; //�Ƿ񱻷���
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct
{
    AdjList vertices;
    int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͻ���
}ALGraph;

//��ʼ�����������ͼG
//�������������ͼG�����ڽӱ�洢
void CreateGraph(ALGraph &G);

//��ʼ������ͼG���������ڽӱ�洢��v��G��ĳ��������±�
//�������������v�ĵ�һ���ڽӶ���λ�ã���������G��û���ڽӵ㣬�򷵻�-1
int FirstAdjVex(ALGraph G, int v);

//��ʼ������ͼG���������ڽӱ�洢��v��G��ĳ��������±꣬w��v���ڽӶ�����±�
//�������������v�ģ������w������һ���ڽӶ���λ�ã���w��v�����һ���ڽӵ㣬�򷵻�-1
int NextAdjVex(ALGraph G, int v, int w);

//��ʼ������ͼG���������ڽӱ�洢��vertexΪ�����еĻ�����Ϣ
//�����������G�д��ڶ���vertex���򷵻�����ͼ�е�λ�ã����򷵻�-1
int LocateVex(ALGraph G, int vertex);

//��ʼ������ͼG���������ڽӱ�洢��ͼG��ÿ�����㶼δ������������IsVisitedֵΪfalse��v��G��ĳ��������±�
//�����������ӡ�����vΪ����������ȱ���
void DFS(ALGraph &G, int v);

//��ʼ������ͼG���������ڽӱ�洢����ͼG��IsVisitedֵ��Ҫ��v��G��ĳ��������±�
//�����������ӡ�����vΪ����������ȱ���
void DFSTraverse(ALGraph &G, int v);

//��ʼ������ͼG���������ڽӱ�洢��v��G��ĳ��������±�
//�����������ӡ�����vΪ���Ĺ�����ȱ���
void BFSTraverse(ALGraph &G, int v);

//��ʼ������ͼG���������ڽӱ���ʽ�洢��v��ͼG��ĳ��������±�
//������������ʸö������Ϣ������ӡ�����Ӧ�Ļ�����Ϣ
void Visit(ALGraph G, int v);

#endif // ALGRAPH_H
