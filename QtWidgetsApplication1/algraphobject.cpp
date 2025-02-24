#include "algraphobject.h"
#include <direct.h>
#include <QApplication>
#include <fstream>
#include <queue>

int visited[60];
int finalvst[60];

AlgraphObject::AlgraphObject(QObject *parent) : QObject(parent)
{
    exepath = QApplication::applicationDirPath();


    if ((mysql = mysql_init(NULL)) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
    }
    if (mysql_real_connect(mysql, "localhost", "root", "su15906477192", "metro", 3306, NULL, 0) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
    }
    mysql_set_character_set(mysql, "utf8");



}

void AlgraphObject::Initgraph(){
    readState();//全部站点
    readEdge();//站点对应的线
    readLineweb();
    readLine();

}

int AlgraphObject::LocateVex(int state, QString name){
    for (int i=1;i<=vexnum;i++)
        if(name==QString::fromUtf8(node[i].name.data())){
            for (int j=0;j<node[i].num;j++)
                if (state==node[i].line[j])
                    return node[i].no;
        }
    return -1;
}

//第一个
int AlgraphObject::FirstAdjVex(int v) {
    int m, n;
    for (int i = 0; i < changenum; i++) {
        m = v > i ? v : i;
        n = v > i ? i : v;
        if (edges[m][n] > 0 && visited[i] == 0)
            return i;
    }
    return -1;
}
//下一个
int AlgraphObject::NextAdjVex(int v, int w) {
    int m, n;
    for (int i = w; i < changenum; i++) {
        m = v > i ? v : i;
        n = v > i ? i : v;
        if (edges[m][n] > 0 && visited[i] == 0&&i!=w)
            return i;
    }
    return -1;
}
//深度优先搜索
void AlgraphObject::DFS(int v, int b, int stations, std::string path)
{
    int w;
    visited[v] = stations+1; //置已访问标记
    path = path + node[head[v]].name + "->";
    stations++;

    for (w = FirstAdjVex(v); w >= 0; w = NextAdjVex(v, w))
        if (w == b) {
            if (stations <= minstate) {
                path += node[head[b]].name;
                minstate = stations;//保存结果
                allstate = path;
                for (int x = 0; x < 60; x++)
                    finalvst[x] = visited[x];
                return;
            }
        }
        else if (!visited[w] && stations + 1 <= minstate) {
            DFS(w, b, stations, path);
            visited[w] = 0;
        }
    stations--;
    return;
}

//深度优先搜索
void AlgraphObject::DFSTraverse() {
    for (int v = 0; v < changenum; v++)
        visited[v] = 0;        //访问标志数组初始化
    std::string path;
    DFS(0, changenum - 1, 0, path);
}
//查询站点路径
void AlgraphObject::Findrute(int a,int b){
    //先构建可换乘点的无向图和邻接矩阵信息
    finalstate.clear();
    int k=1;
    head[0]=a;
    for (int i=1;i<=vexnum;i++)
    {
        if (node[i].num>1){
            head[k]=node[i].no;
            k++;
        }
    }
    head[k]=b;
    changenum=k+1;

    for (int i=0;i<changenum;i++)
    {
        for (int j=0;j<changenum;j++)
            edges[i][j]=0;  
    }
    int same = 0;
    for (int i = 1; i <= k; i++)
    {
        for (int j = 0; j < i; j++)
        {
            same = 0;
            for (int m = 0; m < node[head[i]].num; m++)
            {
                for (int n = 0; n < node[head[j]].num; n++)
                    if (node[head[i]].line[m] == node[head[j]].line[n])
                    {
                        same = 1;
                        edges[i][j] = 1;
                        edges[j][i] = node[head[i]].line[m];
                        break;
                    }
                if (same == 1)
                    break;
            }
        }
    }
    //回溯法搜索最短路径
    minstate=5;
    DFSTraverse();

    //构建输出
    int x[5],t=1;
    for(int i=2;i<5;i++){
        for(int j=0;j<60;j++)
            if (finalvst[j]==i){
                x[t]=j;
                t++;
            }
    }
    x[0]=0;
    x[t]=changenum-1;
    statechange="";
    for (int i=1;i<t;i++){
        if (i<t)
            statechange+=node[head[x[i]]].name;
        if (i!=t-1&&i<t)
            statechange+="--";
    }
    int u,v,pos1,pos2, sign1, sign2;
    int sub;
    allstate = "";
    // finalstate.swap(vector<int>());
    for (int i = 0; i < t; i++) {
        u = x[i] > x[i + 1] ? x[i] : x[i + 1];
        v = x[i] > x[i + 1] ? x[i + 1] : x[i];
        sign1 = 0;
        sign2 = 0;
        sub=0;
        while(1){
            for (unsigned int j = 0; j < this->linedetail[edges[v][u] - 1+sub].size(); j++) {
                if (linedetail[edges[v][u] - 1+sub][j] == head[x[i]]) {
                    pos1 = j;
                    sign1 = 1;
                }
                if (linedetail[edges[v][u] - 1+sub][j] == head[x[i + 1]]) {
                    pos2 = j;
                    sign2 = 1;
                }
                if (sign1&&sign2)
                    break;
            }
            if ((sign1==0||sign2==0)&&(edges[v][u]==10||edges[v][u]==11)){
                sub=4;
                sign1=0;
                sign2=0;
            }
            else
                break;
        }
        if (pos1 > pos2)
            for (int m = pos1; m >= pos2; m--) {
                if (m == pos2&&i == t - 1)
                    allstate = allstate + node[linedetail[edges[v][u]-1+sub][m]].name;
                else if(m!=pos2)
                    allstate = allstate + node[linedetail[edges[v][u]-1+sub][m]].name + "->";
                finalstate.push_back(linedetail[edges[v][u]-1+sub][m]);
            }
        else
            for (int m = pos1; m <= pos2; m++){
                if (m == pos2&&i == t - 1)
                    allstate = allstate + node[linedetail[edges[v][u]-1+sub][m]].name;
                else if(m!=pos2)
                    allstate = allstate + node[linedetail[edges[v][u]-1+sub][m]].name + "->";
                finalstate.push_back(linedetail[edges[v][u]-1+sub][m]);
            }
    }
}
#if 1
void AlgraphObject::readState()
{

    QString select;
    select.append("select * from state");
    if (mysql_query(mysql, select.toStdString().c_str()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if (result->row_count == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    int line;
    int no;
    int i;
    i = 1;
    while (row = mysql_fetch_row(result))
    {
        no = atoi(row[0]);
        node[i].no = no;
        QString name1;
        name1 = row[1];
        node[i].name = name1.toStdString();
        node[i].x = atoi(row[2]);
        node[i].y = atoi(row[3]);
        node[i].num = 0;

        for (int v = 0; v < 4; v++) 
        {//线路信息，站点在几号线上，最多在四条线上 -1
            line = atoi(row[v + 4]);
            node[i].line[v] = line;
            if (line > 0)
            {
                node[i].num += 1;
            }
        }
        i = i + 1;
    }
    vexnum = i - 1;//记录顶点数量

    mysql_free_result(result);


}

void AlgraphObject::readLine()
{
    QString select;
    select.append("select * from line");
    if (mysql_query(mysql, select.toStdString().c_str()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if (result->row_count == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    int i = 0;
    int k;
    for (int i= 0; i < 20; i++)
        linenumber[i] = -1;
    while (row = mysql_fetch_row(result))
    {
        k = atoi(row[0]);
        linenumber[i] = k;
        i++;
    }
    
    mysql_free_result(result);
}

void AlgraphObject::readLineweb()
{

    std::ifstream fin;
    fin.open(QString(exepath + "/lineweb.txt").toStdString());
    if (!fin.is_open()) {
        exit(0);
    }
    int u, v;
    for (int i = 0; i < 20 && fin.peek() != EOF; i++) {   //读入线路信息
        if (i == 0)
            fin >> v;
        while (v == i + 1)
        {
            fin >> u;
            linedetail[i].push_back(u);
            if (fin.peek() != EOF)
                fin >> v;
            else
                break;
        }
    }
    fin.close();
}

void AlgraphObject::readEdge()
{
    QString select;
    select.append("select * from edge");
    if (mysql_query(mysql, select.toStdString().c_str()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if ((result = mysql_store_result(mysql)) == NULL)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }
    if (result->row_count == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("错误");
        msgBox.setText("数据库加载失败!");
        msgBox.setIcon(QMessageBox::Critical);
        QPushButton* okButton = msgBox.addButton(QMessageBox::Ok);
        msgBox.exec();
        return;
    }

    for (int i = 1; i <= vexnum; i++) {
        for (int j = 1; j <= vexnum; j++)
            arcs[i][j] = 0;
    }
    int no;
    int k, a, b;
    while (row = mysql_fetch_row(result))
    {
        no = atoi(row[0]);
        k = atoi(row[1]);
        a = k > no ? k : no;
        b = k > no ? no : k;
        arcs[a][b] = sqrt((node[no].x - node[k].x) * (node[no].x - node[k].x) + (node[no].y - node[k].y) * (node[no].y - node[k].y));
        arcs[b][a] = atoi(row[2]);
    }
    mysql_free_result(result);
}
#endif
