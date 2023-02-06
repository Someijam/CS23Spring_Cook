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
QuadTreeNode MapRoot;
time_t now = time(0);
tm* ltm = localtime(&now);
string fDate="";
string fTime="";
bool task1_2Finished=false;
bool task1_3Finished=false;

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
    task1out.open("./outputs/task1.out",ios::out);//打开用于输出答案的文件
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
        addStationToTree(Stations[i]);
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
    logout<<"["<<fTime<<"]"<<"[Main/WARN]"<<"需求文档未定义\"西北角树叶的东侧树叶\"、\"南侧相邻树叶\"、\"东南角所在树叶的西北侧\"以及\"西北侧的北侧相邻树叶\""<<endl;
    logout<<"["<<fTime<<"]"<<"[Main/WARN]"<<"将跳过任务2"<<endl;
    /*****************任务2结束*****************/



    /******************收尾工作******************/
    deleteMap(&MapRoot);//释放四叉树占用的空间
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"四叉树已经清除。"<<endl;

    return 0;
}