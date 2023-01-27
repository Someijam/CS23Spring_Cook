/*
Author:Someijam
Date:2023/01/14
Problem description:
CSpring_Cook
*/
#include"customHeaders.h"//其他头文件在此文件中

using namespace std;

vector<Station> Stations;
QuadTreeNode MapRoot;
time_t now = time(0);
tm* ltm = localtime(&now);
string fDate="";
string fTime="";
FILE* fJZin;
FILE* fWZin;
FILE* fYDin;
FILE* fLOGout;
FILE* fAREAout;
FILE* fSWITCHout;

int main()
{
    // auto setDateTime=[]()
    // {
    //     fDate=fDate+to_string(1900 + ltm->tm_year);
    //     fDate=fDate+"-";
    //     if(1+ltm->tm_mon<10)fDate=fDate+"0";
    //     fDate=fDate+to_string(1 + ltm->tm_mon);
    //     fDate=fDate+"-";
    //     if(ltm->tm_mday<10)fDate=fDate+"0";
    //     fDate=fDate+to_string(ltm->tm_mday);

    //     if(ltm->tm_hour<10)fTime=fTime+"0";
    //     fTime=fTime+to_string(ltm->tm_hour);
    //     fTime=fTime+":";
    //     if(ltm->tm_min<10)fTime=fTime+"0";
    //     fTime=fTime+to_string(ltm->tm_min);
    //     fTime=fTime+":";
    //     if(ltm->tm_sec<10)fTime=fTime+"0";
    //     fTime=fTime+to_string(ltm->tm_sec);
    // };//此函数仅使用一次，采用Lambda表达式，截取外部作用域中所有变量，并作为引用在函数体中使用

    setDateTime();//更新日志文件里的时间

    fJZin=freopen("./test_data/jz001.txt", "r", stdin);//默认是基站输入
    if(!fJZin)//检验文件是否打开
    {
        cerr<<"基站数据文件不存在的，是不是输错了？"<<endl;
        exit(0);
    }
    string cmdLogPath="./logs/"+fDate;
    cmdLogPath=cmdLogPath+"_";
    cmdLogPath=cmdLogPath+fTime;
    cmdLogPath=cmdLogPath+".log";
    fLOGout=freopen(cmdLogPath.c_str(), "w", stdout);//日志文件，cmdLogPath不允许再更新
    if(!fJZin)//检验日志是否打开
    {
        cerr<<"日志文件不存在的，是不是输错了？"<<endl;
        exit(0);
    }

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
            else if(strcmp(tempSt.typeName,"乡镇")==0)tempSt.type=1;
            else if(strcmp(tempSt.typeName,"高速")==0)tempSt.type=2;
            else 
            {
                setDateTime();//更新日志文件里的时间
                cerr<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件中基站类型不与城区乡镇和高速的任意一种匹配，请检查如下基站:编号#"<<tempSt.no<<endl;
            }
            Stations.push_back(tempSt);
        }
        if(tempSt.x!=-1||tempSt.y!=-1)
        {
            setDateTime();//更新日志文件里的时间
            cerr<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件尾部或格式有误，检查是否为jz001.txt的错误版本"<<tempSt.no<<endl;
            exit(0);
        }
    }
    else
    {
        setDateTime();//更新日志文件里的时间
        cerr<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件头部有误"<<endl;
        exit(0);
    }
    //线性存储各个基站数据到内存，免得频繁磁盘IO

    for(int i=1;i<Stations.size();i++)//基站信息添加到四叉树
    {
        addStationToTree(Stations[i]);
        setDateTime();//更新日志文件里的时间
        cout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Added St#"<<Stations[i].no<<" \tPosition("<<Stations[i].x<<","<<Stations[i].y<<") \t to the Quad Tree."<<endl;
    }
    //将基站存储到四叉树中

    /******************任务1******************/
    setDateTime();//更新日志文件里的时间
    cout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"即将执行Task1，请前往\"outputs/task1.out\"下查看输出结果。"<<endl;
    fclose(fLOGout);
    fAREAout=freopen("./outputs/task1.out", "w", stdout);//打开用于输出答案的文件
    task1Traverse();
    fclose(fAREAout);
    fLOGout=freopen(cmdLogPath.c_str(), "a", stdout);//输出回到日志文件
    setDateTime();//更新日志文件里的时间
    cout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"Task1已完成。"<<endl;
    /*****************任务1结束*****************/


    /******************收尾工作******************/
    deleteMap(&MapRoot);//释放四叉树占用的空间
    setDateTime();//更新日志文件里的时间
    cout<<"["<<fTime<<"]"<<"[Main/INFO]"<<"四叉树已经清除。"<<endl;
    fclose(fJZin);
    fclose(fLOGout);
    return 0;
}