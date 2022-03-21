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

#define INFINITY 2147483647 //int型的最大值
#define MAX_VERTEX_NUM 100 //最大顶点数量
#define MAX_AIRLINE_NUM 2500//最大现有航线数量

typedef struct Date{
    int year; //年
    int month; //月
    int day; //日
    int hour; //小时
    int minute; //分钟
}Date;//日期

typedef struct AirLine
{
    int FlightID;//航班ID
    int FlightNO; //航班号
    int DepAirport; //起飞机场
    int ArrAirport; //抵达机场
    int DepTime; //起飞时间,以分钟为单位
    int ArrTime; //抵达时间,以分钟为单位
    int AirplaneID;//飞机号
    int AirplaneModel; //机型
    int AirFare; //机票价格
}AirLine; //航线信息

extern AirLine airline[MAX_AIRLINE_NUM];//存储航线信息的结构体

extern int LineNum; //航线数量，经统计共有2346条航线，即弧数

#endif // DATADEFINE_H
