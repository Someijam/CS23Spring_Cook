/*
Author:Someijam
Date:2023/01/14
Problem description:
CSpring_Cook
*/
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<vector>
#define BORDER 131072

using namespace std;


struct QuadTreeNode
{
    // 四叉树的节点包含以下信息：
    int x;
    int y; // 节点的坐标(中心位置)
    int level; // 节点的级别(整张图最中间为0级，逐级增加)
    QuadTreeNode* children[4]={0}; // 子节点，最多有4个
    QuadTreeNode* parent;//上级节点
    bool isLeaf; // 是否为叶节点
    int includedStationNo=0;//此区域(节点)内唯一的一个基站编号，没有用0表示
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

int defineWhichQuadrant(Station st,QuadTreeNode tree)
{
    if((st.x-tree.x>0)&&(st.y-tree.y>=0))return 0;
    else if((st.x-tree.x<=0)&&(st.y-tree.y>0))return 1;
    else if((st.x-tree.x<0)&&(st.y-tree.y<=0))return 2;
    else if((st.x-tree.x>=0)&&(st.y-tree.y<0))return 3;
    else return 0;
}
void addStationToTree(Station st)
{
    QuadTreeNode* currentTree=&MapRoot;
    if(currentTree->isLeaf)//是叶节点
    {
        if(currentTree->includedStationNo==0)
        {
            currentTree->includedStationNo=st.no;//新建的叶节点，没人，使用该节点
            return;
        }
        else //这一级节点有人了
        {
            currentTree->isLeaf=false;//稍后分裂节点
            for(int i=0;i<4;i++)//分裂节点
            {
                currentTree->children[i]=new QuadTreeNode;
                currentTree->children[i]->parent=currentTree;
                currentTree->children[i]->includedStationNo=0;
                currentTree->children[i]->isLeaf=true;
                currentTree->children[i]->level=currentTree->level+1;
            }
            currentTree->children[0]->x=(currentTree->x+BORDER)/2;
            currentTree->children[1]->x=(currentTree->x-BORDER)/2;
            currentTree->children[2]->x=(currentTree->x-BORDER)/2;
            currentTree->children[3]->x=(currentTree->x+BORDER)/2;

            currentTree->children[0]->y=(currentTree->y+BORDER)/2;
            currentTree->children[1]->y=(currentTree->y+BORDER)/2;
            currentTree->children[2]->y=(currentTree->y-BORDER)/2;
            currentTree->children[3]->y=(currentTree->y-BORDER)/2;
            //初始化新节点

            currentTree->children[defineWhichQuadrant(Stations[currentTree->includedStationNo],*currentTree)]->includedStationNo=currentTree->includedStationNo;
            currentTree->includedStationNo=0;
            //上一层的站点移下来
        }
    }
    while(currentTree->isLeaf==false)//不是叶节点,找到叶节点为止
    {
        int quadrant=defineWhichQuadrant(st,*currentTree);
        // if(!currentTree->children[quadrant])//没有子节点，考虑是否等价于(currentTree->isLeaf=true)
        // {
        //     QuadTreeNode* newChild;
        //     newChild=new QuadTreeNode;
        //     currentTree->children[quadrant]=newChild;
        // }
        currentTree=currentTree->children[defineWhichQuadrant(st,*currentTree)];

    }
    currentTree->includedStationNo=st.no;
    return;
}

vector<Station> Stations;

int main()
{
    freopen("./test_data/jzdemo.txt", "r", stdin);
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
        while(scanf("%d,%d,%s  %lf,%d",&tempSt.x,&tempSt.y,tempSt.typeName,&tempSt.baseStrength,&tempSt.no)!=2)//!=2表示没有到最后一个
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
    }
    return 0;
}