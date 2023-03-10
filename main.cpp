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
// int maxLevel=0;
// bool task1_2Finished=false;
// bool task1_3Finished=false;
// QuadTreeNode* NW_estChunk;//最西北角区块地址
// QuadTreeNode* SE_estChunk;//最东南角区块地址
// QuadTreeNode* SE_nwChunk;//东南角区块的西北小区块地址
QuadTreeNode* tempNode;
QuadTreeNode* tempThis;
int maxX;
int maxY;
int minX;
int minY;
int testx3[3]={101000,18291,85000};
int testy3[3]={23500,26354,28000};//任务3数据
int testx4[3]={3000,70000,100000};
int testy4[3]={36900,35000,7002};//任务4数据
vector<Route> terminalMovement;//终端运动轨迹
vector<FakeSt> fakeStationMovement;//伪基站移动轨迹

FILE* fJZin;
FILE* fRTin;
FILE* fWZin;

ofstream logout;
ofstream task1out;
ofstream task2out;
ofstream task3out;
ofstream task4out;
ofstream task5out;
ofstream ext1out;
ofstream ext2out;
ofstream adv1out;
ofstream adv2out;

int main()
{
    setDateTime();//更新日志文件里的时间

    string cmdLogPath="./logs/"+fDate;
    cmdLogPath=cmdLogPath+"_";
    cmdLogPath=cmdLogPath+fTime;
    cmdLogPath=cmdLogPath+".log";

    task1out.open("./outputs/task1.out",ios::out);
    task2out.open("./outputs/task2.out",ios::out);
    task3out.open("./outputs/task3.out",ios::out);
    task4out.open("./outputs/task4.out",ios::out);
    task5out.open("./outputs/task5.out",ios::out);
    ext1out.open("./outputs/ext1.out",ios::out);
    ext2out.open("./outputs/ext2.out",ios::out);
    adv1out.open("./outputs/adv1.out",ios::out);
    adv2out.open("./outputs/adv2.out",ios::out);
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
    analyzeStatistics();//分析基站分布数据
    readTermMoveFile();
    //线性读取终端移动路径到内存
    readWZMoveFile();
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Successfully added terminal routes to the memory."<<endl;

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
    task1Process();
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

    /******************任务4******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Task4，请前往\"outputs/task4.out\"下查看输出结果。"<<endl;
    task4Process();
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Task4已完成。"<<endl;
    /*****************任务4结束*****************/

    /******************任务5******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Task5，请前往\"outputs/task5.out\"下查看输出结果。"<<endl;
    task5Process();
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Task5已完成。"<<endl;
    /*****************任务5结束*****************/

    /******************扩展1******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Ext1，请前往\"outputs/ext1.out\"下查看输出结果。"<<endl;
    ext1Process_2(1);
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Ext1已完成。"<<endl;
    /*****************扩展1结束*****************/

    /******************扩展2******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Ext2，请前往\"outputs/ext2.out\"下查看输出结果。"<<endl;
    ext2Process(3,6);
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Ext2已完成。"<<endl;
    /*****************扩展2结束*****************/

    /******************升级1******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Adv1，请前往\"outputs/adv1.out\"下查看输出结果。"<<endl;
    adv1Process(12);
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Adv1已完成。"<<endl;
    /*****************升级1结束*****************/

    /******************升级1******************/
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Adv2，请前往\"outputs/adv2.out\"下查看输出结果。"<<endl;
    adv2Process(9);
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Adv2已完成。"<<endl;
    /*****************升级1结束*****************/

    miscProcess();//杂项

    /******************收尾工作******************/
    deleteMap(&MapRoot);//释放四叉树占用的空间
    setDateTime();//更新日志文件里的时间
    logout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"四叉树已经清除。"<<endl;
    // logout<<"MaxLevel="<<maxLevel<<endl;
    logout.close();
    task1out.close();
    task2out.close();
    task3out.close();
    task4out.close();
    task5out.close();
    ext1out.close();
    ext2out.close();
    adv1out.close();
    adv2out.close();//关闭文件
    return 0;
}
