/*
Author:Someijam
Date:2023/01/14
Problem description:
CSpring_Cook
*/
#include"customHeaders.h"//其他头文件在此文件中

vector<Station> Stations;
QuadTreeNode MapRoot;
time_t now = time(0);
char* presentDateTime = ctime(&now);
tm* ltm = localtime(&now);
string fDate="";
string fTime="";

int main()
{
    fDate=fDate+to_string(1900 + ltm->tm_year);
    fDate=fDate+"-";
    if(1+ltm->tm_mon<10)fDate=fDate+"0";
    fDate=fDate+to_string(1 + ltm->tm_mon);
    fDate=fDate+"-";
    if(ltm->tm_mday<10)fDate=fDate+"0";
    fDate=fDate+to_string(ltm->tm_mday);

    if(ltm->tm_hour<10)fTime=fTime+"0";
    fTime=fTime+to_string(ltm->tm_hour);
    fTime=fTime+":";
    if(ltm->tm_min<10)fTime=fTime+"0";
    fTime=fTime+to_string(ltm->tm_min);
    fTime=fTime+":";
    if(ltm->tm_sec<10)fTime=fTime+"0";
    fTime=fTime+to_string(ltm->tm_sec);

    int fOpenStatus=0;
    freopen("./test_data/jz001.txt", "r", stdin);//测试输入
    string cmdLogPath="./logs/"+fDate;
    cmdLogPath=cmdLogPath+"_";
    cmdLogPath=cmdLogPath+fTime;
    cmdLogPath=cmdLogPath+".log";
    freopen(cmdLogPath.c_str(), "w", stdout);//日志文件

    MapRoot.x=0;
    MapRoot.y=0;
    MapRoot.level=0;
    MapRoot.isLeaf=true;
    MapRoot.parent=NULL;

    Station tempSt={0};
    Stations.push_back(tempSt);
    char inputType[5]={0};

    cin>>inputType;
    if(strcmp(inputType,"JZ")==0)//基站信息录入
    {
        while(scanf("%d,%d,%s  %lf,%d",&tempSt.x,&tempSt.y,tempSt.typeName,&tempSt.baseStrength,&tempSt.no)==5)//5表示正常输入
        {
            if(strcmp(tempSt.typeName,"城区")==0)tempSt.type=0;
            if(strcmp(tempSt.typeName,"乡镇")==0)tempSt.type=1;
            if(strcmp(tempSt.typeName,"高速")==0)tempSt.type=2;
            Stations.push_back(tempSt);
        }
    }
    //线性存储各个基站数据

    for(int i=1;i<Stations.size();i++)//基站信息添加到四叉树
    {
        addStationToTree(Stations[i]);
        cout<<"["<<fDate<<" "<<fTime<<"]"<<"[Main/INFO]"<<"Added St#"<<Stations[i].no<<" \tPosition("<<Stations[i].x<<","<<Stations[i].y<<") \t to the Quad Tree."<<endl;
    }
    //将基站存储到四叉树中


    deleteMap(&MapRoot);//释放四叉树占用的空间
    return 0;
}