#ifndef ALGRAPHOBJECT_H
#define ALGRAPHOBJECT_H

#include <QObject>
#include <QString>
#include <iostream>
#include <qlist.h>
#include <QLinkedList>
#include <vector>
#include <QMessageBox>
#include "../include/mysql.h"
#define MAX_VERTEX_NUM 450   //最大顶点个数

//using namespace std;



class AlgraphObject : public QObject
{
    Q_OBJECT
    typedef struct Node
    {
        int no;    //序号
        std::string name;   //站点名称
        int x,y;    //站点坐标
        int line[4]; //线路信息，站点在几号线上，最多在四条线上
        int num;
    }Node;
public:
    explicit AlgraphObject(QObject *parent = nullptr);
    QString exepath;

    MYSQL* mysql;
    MYSQL_RES* result;
    MYSQL_ROW  row;

public:
    Node node[MAX_VERTEX_NUM];
    int vexnum;   //顶点数量
    int arcnum;   //边的数量
    int arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];   //邻接矩阵
    int start,end;   //起始站
    int linenumber[20];

    std::string allstate;
    std::string statechange;
    int changenum;
    int head[100];
    int edges[100][100];
    int minstate;

    std::vector <int> linedetail[20];
    std::vector <int> finalstate;

    void Initgraph();//初始
    int LocateVex(int state,QString name);//定位

    int FirstAdjVex(int v);//第一个
    int NextAdjVex(int v, int w);//下一个
    void DFS(int v, int b, int stations, std::string path);//深度优先搜索
    void DFSTraverse();//深度优先搜索
    void Findrute(int a,int b);//查询站点路径


    void readState();
    void readLine();
    void readLineweb();
    void readEdge();
};

#endif // ALGRAPHOBJECT_H
