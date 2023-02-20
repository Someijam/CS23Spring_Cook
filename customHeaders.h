//工程全部的头文件
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
#include<bitset>
#include<ctime>
//宏定义
#define BORDER_EXP 17//地图尺寸指数
#define MAX_UNIT_NUNS (int)9//单分块最大基站数
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
    pair<int,int> prefix;//分别表示x和y方向的象限记录
    int quarterWidth();//该区块1/4边长
    QuadTreeNode* northNode();//北侧区块
    QuadTreeNode* southNode();//南侧区块
    QuadTreeNode* eastNode();//东侧区块
    QuadTreeNode* westNode();//西侧区块
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
extern bool task1_2Finished;
extern bool task1_3Finished;
extern QuadTreeNode* NW_estChunk;//最西北角区块地址
extern QuadTreeNode* SE_estChunk;//最东南角区块地址

extern FILE* fJZin;

extern ifstream jzin;
extern ifstream wzin;
extern ifstream ydin;
extern ofstream logout;
extern ofstream task1out;
extern ofstream task2out;
extern ofstream task3out;
extern ofstream task4out;
extern ofstream task5out;

//函数声明
void setDateTime();//更新日期和时间
void readJzFile();//将基站文件读入内存
int defineWhichQuadrant(Station* st,QuadTreeNode* tree);//查找这个基站相对于当前中心的象限
void diverseTree(QuadTreeNode* leaf);//将此树叶分为四个子节点
void addStationToTree(Station st);//将基站st添加到四叉树
void deleteMap(QuadTreeNode* head);//释放四叉树空间
void task1Traverse();//任务1:遍历西北角和东南角的基站
void task1PreOrderTraverse_2(QuadTreeNode* T);//一直往西北找的最小区域，备用
void task1PreOrderTraverse_3(QuadTreeNode* T);//一直往东南找的最小区域，备用
void task2PreOrderTraverse_1(QuadTreeNode* T);//任务2:遍历区域1
void task2PreOrderTraverse_2(QuadTreeNode* T);//任务2:遍历整个子区域2
void task2Process();//任务2:遍历指定区块的相邻区块基站
void task2PreOrderTraverse_3(QuadTreeNode* T);//任务2:遍历最东南角西北侧子区域