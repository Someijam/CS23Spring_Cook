/*
Author:Someijam
Date:2023/01/14
Problem description:
CS23pring_Cook 21级网安23春课设
约定：x轴正方向为东方向，y轴正方向为北方向
*/
#include"customHeaders.h"//其他头文件在此文件中

using namespace std;

vector<Station> Stations;
vector<int> ExpressWayStationsNo;
QuadTreeNode MapRoot;
time_t now = time(0);
tm* ltm = localtime(&now);
string fDate="";
string fTime="";
int maxLevel=0;
bool task1_2Finished=false;
bool task1_3Finished=false;
QuadTreeNode* NW_estChunk;//最西北角区块地址
QuadTreeNode* SE_estChunk;//最东南角区块地址
QuadTreeNode* SE_nwChunk;//东南角区块的西北小区块地址
int testx3[3]={101000,18291,26354};
int testy3[3]={23500,26354,28000};//任务3数据

FILE* fJZin;

ifstream jzin;
ifstream wzin;
ifstream ydin;
ofstream logout;
ofstream task1out;
ofstream task2out;
ofstream task3out;
ofstream task4out;
ofstream task5out;

int main()
{
    setDateTime();//更新日志文件里的时间

    string cmdLogPath="./logs/"+fDate;
    cmdLogPath=cmdLogPath+"_";
    cmdLogPath=cmdLogPath+fTime;
    cmdLogPath=cmdLogPath+".log";

    // jzin.open("./test_data/jz001.txt",ios::in);//基站输入
    wzin.open("./test_data/wz001.txt",ios::in);//伪基站输入
    ydin.open("./test_data/yd001.txt",ios::in);//移动轨迹输入
    task1out.open("./outputs/task1.out",ios::out);
    task2out.open("./outputs/task2.out",ios::out);
    task3out.open("./outputs/task3.out",ios::out);
    //打开用于输出答案的文件
    logout.open(cmdLogPath.c_str(),ios::out);//日志文件

    MapRoot.x=0;
    MapRoot.y=0;
    MapRoot.level=0;
    MapRoot.isLeaf=true;
    MapRoot.parent=NULL;
    MapRoot.prefix.first=0;
    MapRoot.prefix.second=0;

    readJzFile();
    //线性存储各个基站数据到内存，免得频繁磁盘IO
    int stCnt=0;
    for(int i=1;i<Stations.size();i++)//基站信息添加到四叉树
    {
        addStationToTree(i);
        setDateTime();//更新日志文件里的时间
        // logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Added St#"<<Stations[i].no<<" \tPosition("<<Stations[i].x<<","<<Stations[i].y<<") \t to the Quad Tree."<<endl;
        stCnt=i;
    }
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Totally added "<<stCnt<<" stations to the Quad Tree."<<endl;
    //将基站存储到四叉树中

    /******************任务1******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Task1，请前往\"outputs/task1.out\"下查看输出结果。"<<endl;
    task1Traverse();
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Task1已完成。"<<endl;
    /*****************任务1结束*****************/

    /******************任务2******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Task2，请前往\"outputs/task2.out\"下查看输出结果。"<<endl;
    task2Process();
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Task2已完成。"<<endl;
    /*****************任务2结束*****************/

    /******************任务3******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Task3，请前往\"outputs/task3.out\"下查看输出结果。"<<endl;
    task3Process();
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Task3已完成。"<<endl;
    /*****************任务3结束*****************/



    /******************收尾工作******************/
    deleteMap(&MapRoot);//释放四叉树占用的空间
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"四叉树已经清除。"<<endl;
    // logout<<"MaxLevel="<<maxLevel<<endl;
    return 0;
}