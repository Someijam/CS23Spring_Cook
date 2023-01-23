/*
Author:Someijam
Date:2023/01/14
Problem description:
CSpring_Cook
*/
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<vector>
#define BORDER_EXP 17
using namespace std;

struct QuadTreeNode//四叉树结构
{
    // 四叉树的节点包含以下信息：
    int x;
    int y; // 节点的坐标(中心位置)
    int level; // 节点的级别(整张图最中间为0级，逐级增加)
    //quarterWidth=pow(2,17-level)
    QuadTreeNode* children[4]; // 子节点，最多有4个
    QuadTreeNode* parent;//上级节点
    bool isLeaf; // 是否为叶节点
    vector<int> includedStationNo;//此区域(节点)内所有基站编号/序号，没有则size为0
    int quarterWidth();
}MapRoot;

struct Station//基站信息
{
    int x;
    int y;//坐标
    char typeName[20];//类别名称
    int type;//类别编号
    double baseStrength;//强度
    int no;//顺序编号
};

vector<Station> Stations;

int QuadTreeNode::quarterWidth()//当前节点四分之一边长
{
    return pow(2,BORDER_EXP-1-(this->level));
}

int defineWhichQuadrant(Station* st,QuadTreeNode* tree)//查找这个基站相对于当前中心的象限
{
    if((st->x-tree->x>0)&&(st->y-tree->y>=0))return 0;
    else if((st->x-tree->x<=0)&&(st->y-tree->y>0))return 1;
    else if((st->x-tree->x<0)&&(st->y-tree->y<=0))return 2;
    else if((st->x-tree->x>=0)&&(st->y-tree->y<0))return 3;
    else return 0;
}

void diverseTree(QuadTreeNode* leaf)//将此树叶分为四个子节点
{
    if(!leaf->isLeaf)
    {
        cerr<<"此种情况绝对不会出现，除非是见鬼了：尝试将四叉树的非叶节点再次四分"<<endl;
        exit(0);
    }
    for(int i=0;i<4;i++)
    {
        leaf->children[i]=new QuadTreeNode;//此处动态分配了内存
        leaf->children[i]->isLeaf=true;
        leaf->children[i]->level=leaf->level+1; 
        leaf->children[i]->parent=leaf;
        if(i==0)
        {
            leaf->children[i]->x=leaf->x+leaf->quarterWidth();
            leaf->children[i]->y=leaf->y+leaf->quarterWidth();
        }
        else if(i==1)
        {
            leaf->children[i]->x=leaf->x-leaf->quarterWidth();
            leaf->children[i]->y=leaf->y+leaf->quarterWidth();
        }
        else if(i==2)
        {
            leaf->children[i]->x=leaf->x-leaf->quarterWidth();
            leaf->children[i]->y=leaf->y-leaf->quarterWidth();
        }
        else if(i==3)
        {
            leaf->children[i]->x=leaf->x+leaf->quarterWidth();
            leaf->children[i]->y=leaf->y-leaf->quarterWidth();
        }
    }
    leaf->isLeaf=false;
    return;
}

void addStationToTree(Station st)//将基站st添加到四叉树
{
    QuadTreeNode* insertTarget=&MapRoot;
    while(!insertTarget->isLeaf)
    {
        insertTarget=insertTarget->children[defineWhichQuadrant(&st,insertTarget)];
    }
    //将insertTargrt定位到需要插入的位置
    if((insertTarget->includedStationNo.size()<9)&&(insertTarget->includedStationNo.size()>=0))
    {
        insertTarget->includedStationNo.push_back(st.no);
    }//叶节点没有满则继续插入
    else if(insertTarget->includedStationNo.size()==9)
    {
        diverseTree(insertTarget);
        for(int i=0;i<insertTarget->includedStationNo.size();i++)
        {
            insertTarget->children[defineWhichQuadrant(&Stations[insertTarget->includedStationNo[i]],insertTarget)]->includedStationNo.push_back(insertTarget->includedStationNo[i]);
            //将 当前节点基站序号存储容器的第i个人 添加到 当前节点的 第（第i个基站相对于当前节点的）象限的子节点 的基站序号存储容器
        }//转移当前的9个站点序号到下面四个节点
        insertTarget->includedStationNo.clear();
        // insertTarget->children[defineWhichQuadrant(&st,insertTarget)]->includedStationNo.push_back(st.no);//转移完毕，有很大概率上面的9个还是会挤到一起，所以得递归调用
        addStationToTree(st);//递归调用，上面节点挤到一起了还得再分
    }//叶节点满了就转移到子节点稍后再插入
    else
    {
        cerr<<"此种情况绝对不会出现，除非是见鬼了：insertTarget->includedStationNo.size()="<<insertTarget->includedStationNo.size()<<endl;
        exit(0);
    }

    return;
}

void deleteMap(QuadTreeNode* head)
{
    if(head==NULL)
        return;//到尾巴就回
    for(int i=0;i<4;i++)
    {
        deleteMap(head->children[i]);
    }
    if(head->level!=0)
    {
        cout<<"Deleted a stem in level#"<<head->level<<endl;
        delete head;//MapRoot不是动态分配，不显式删除
    }
    return;
}

int main()
{
    freopen("./test_data/jzdemo.txt", "r", stdin);//测试输入
    MapRoot.x=0;
    MapRoot.y=0;
    MapRoot.level=0;
    MapRoot.isLeaf=true;
    MapRoot.parent=NULL;

    Station tempSt={0};
    Stations.push_back(tempSt);
    char inputType[5]={0};

    cin>>inputType;
    if(strcmp(inputType,"JZ")==0)
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

    for(int i=1;i<Stations.size();i++)
    {
        addStationToTree(Stations[i]);
        cout<<"Added St#"<<Stations[i].no<<" \tPosition("<<Stations[i].x<<","<<Stations[i].y<<") \t to the Quad Tree."<<endl;
    }
    //将基站存储到四叉树中
    deleteMap(&MapRoot);//释放四叉树占用的空间
    return 0;
}