//工程全部的头文件
#include<iostream>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<ctime>
//宏定义
#define BORDER_EXP 17

//名字空间
using namespace std;

//自定义结构
struct QuadTreeNode//四叉树结构
{
    // 四叉树的节点包含以下信息：
    int x;
    int y; // 节点的坐标(中心位置)
    int level; // 节点的级别(整张图最中间为0级，逐级增加)
    //quarterWidth=pow(2,17-level)
    QuadTreeNode* children[4];//={NULL}; // 子节点，最多有4个
    QuadTreeNode* parent;//上级节点
    bool isLeaf; // 是否为叶节点
    vector<int> includedStationNo;//此区域(节点)内所有基站编号/序号，没有则size为0
    int quarterWidth();
};
struct Station//基站信息
{
    int x;
    int y;//坐标
    char typeName[20];//类别名称
    int type;//类别编号
    double baseStrength;//强度
    int no;//顺序编号
};

//全局变量
extern vector<Station> Stations;
extern QuadTreeNode MapRoot;
extern time_t now;//当前时间
extern char* presentDateTime;
extern tm* ltm;
extern string fDate;
extern string fTime;
//函数声明
int defineWhichQuadrant(Station* st,QuadTreeNode* tree);//查找这个基站相对于当前中心的象限
void diverseTree(QuadTreeNode* leaf);//将此树叶分为四个子节点
void addStationToTree(Station st);//将基站st添加到四叉树
void deleteMap(QuadTreeNode* head);//释放四叉树空间
