#ifndef DATADEFINE_H
#define DATADEFINE_H

#include <iostream>
#include <memory.h>
#include <string>
#include <string.h>
#include <typeinfo>
#include <vector>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <stdlib.h>

using namespace std;

#define INFINITY 2147483647 //int�͵����ֵ
#define MAX_VERTEX_NUM 100 //��󶥵�����
#define MAX_AIRLINE_NUM 2500//������к�������

typedef struct Date{
    int year; //��
    int month; //��
    int day; //��
    int hour; //Сʱ
    int minute; //����
}Date;//����

typedef struct AirLine
{
    int FlightID;//����ID
    int FlightNO; //�����
    int DepAirport; //��ɻ���
    int ArrAirport; //�ִ����
    int DepTime; //���ʱ��,�Է���Ϊ��λ
    int ArrTime; //�ִ�ʱ��,�Է���Ϊ��λ
    int AirplaneID;//�ɻ���
    int AirplaneModel; //����
    int AirFare; //��Ʊ�۸�
}AirLine; //������Ϣ

extern AirLine airline[MAX_AIRLINE_NUM];//�洢������Ϣ�Ľṹ��

extern int LineNum; //������������ͳ�ƹ���2346�����ߣ�������

#endif // DATADEFINE_H
