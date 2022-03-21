#ifndef MGRAPH_H
#define MGRAPH_H

/***���ļ�ʵ���ڽӾ���Ĵ洢�ͻ�����������***/

#include "datadefine.h"

//������
//�ڽӾ���
typedef struct ArcCell{
    AirLine LineInfo; //�洢������Ϣ�Ľṹ�壺����ID��������ڣ�����/���ں��࣬����ţ����ʱ�䣬�ִ�ʱ�䣬�ɻ��ţ����ͣ���Ʊ�۸��
    ArcCell* next; //ָ����һ������ָ��
}ArcCell, *AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct VexNode
{
    int data;//������Ϣ
    bool IsVisited;//�Ƿ񱻷��ʹ�
}VexNode;

typedef struct{
    VexNode vexs[MAX_VERTEX_NUM]; //�����������洢����
    AdjMatrix arcs; //�ڽӾ���,��ÿһ�����ϴ洢����һ��ָ�룬����ָ��һ��������������洢��Ϊ�Ըû���Ϊ��ɻ����ĺ��ߡ�
    int vexnum, arcnum; //ͼ�ĵ�ǰ�������ͻ���
}MGraph;

//��ʼ�����������ͼG
//�������������ͼG�����ڽӾ���洢
void CreateGraph(MGraph &G); //�Ѽ��

//��ʼ������ͼG���������ڽӾ���洢��v��G��ĳ��������±�
//�������������v�ĵ�һ���ڽӶ���λ�ã���������G��û���ڽӵ㣬�򷵻�-1
int FirstAdjVex(MGraph G,int v);

//��ʼ������ͼG���������ڽӾ���洢��v��G��ĳ��������±꣬w��v���ڽӶ�����±�
//�������������v�ģ������w������һ���ڽӶ���λ�ã���w��v�����һ���ڽӵ㣬�򷵻�-1
int NextAdjVex(MGraph G, int v, int w);

//��ʼ������ͼG���������ڽӾ���洢��vertexΪ�����еĻ�����Ϣ
//�����������G�д��ڶ���vertex���򷵻�����ͼ�е�λ�ã����򷵻�-1
int LocateVex(MGraph G, int vertex);

//��ʼ������ͼG���������ڽӾ���洢��start����ʼ�����ı�ţ�terminal��Ŀ������ı��
//�����������start��terminal֮����ͨ�����ӡ�����������ͨ���������ӡ�������������ͨ��
void BFSTraverse(MGraph &G, int start, int terminal);

//��ʼ������ͼG���������ڽӾ�����ʽ�洢��v��ͼG��ĳ��������±�
//������������ʸö������Ϣ������ӡ�����Ӧ�Ļ�����Ϣ
void Visit(MGraph G, int v);

#endif // MGRAPH_H
