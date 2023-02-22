//工程全部的头文件
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<vector>
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
    QuadTreeNode* children[4];//={NULL}; // 子节点，最多有4个
    QuadTreeNode* parent;//上级节点
    bool isLeaf; // 是否为叶节点
    vector<int> includedStationIndex;//此区域(节点)内所有基站 ！索引！ ，没有则size为0
    pair<int,int> prefix;//分别表示x和y方向的象限记录
    int quarterWidth();//该区块1/4边长
    QuadTreeNode* northNode();//北侧区块
    QuadTreeNode* southNode();//南侧区块
    QuadTreeNode* eastNode();//东侧区块
    QuadTreeNode* westNode();//西侧区块
    QuadTreeNode* nwNode();//西北区块
    QuadTreeNode* neNode();//东北区块
    QuadTreeNode* swNode();//西南区块
    QuadTreeNode* seNode();//东南区块
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
struct Route//移动路径
{
    double xs;
    double ys;//起点
    double xe;
    double ye;//终点
    double velocity;//速度
    int startTime;//离散时间=hour*60+min
};


//全局变量
extern vector<Station> Stations;
extern vector<int> ExpressWayStationsNo;
extern QuadTreeNode MapRoot;
extern time_t now;//当前时间
extern char* presentDateTime;
extern tm* ltm;
extern string fDate;
extern string fTime;
extern int maxLevel;
extern bool task1_2Finished;
extern bool task1_3Finished;
extern QuadTreeNode* NW_estChunk;//最西北角区块地址
extern QuadTreeNode* SE_estChunk;//最东南角区块地址
extern QuadTreeNode* SE_nwChunk;//东南角区块的西北小区块地址
extern QuadTreeNode* tempNode;
extern QuadTreeNode* tempThis;
extern int testx3[3];
extern int testy3[3];//任务3数据
extern int testx4[3];
extern int testy4[3];//任务4数据
extern vector<Route> terminalMovement;//终端运动轨迹

extern FILE* fJZin;
extern FILE* fRTin;

extern ofstream logout;
extern ofstream task1out;
extern ofstream task2out;
extern ofstream task3out;
extern ofstream task4out;
extern ofstream task5out;

//函数声明
//结构体定义中需要使用的方法函数(需声明)
void quadtreeAssistTraverse1(QuadTreeNode* T);//辅助函数1
void quadtreeAssistTraverse2(QuadTreeNode* T);//辅助函数2
void quadtreeAssistTraverse3(QuadTreeNode* T);//辅助函数3
void quadtreeAssistTraverse4(QuadTreeNode* T);//辅助函数4

//C++通用工具函数(需声明)
bool isInVector(vector<int> &vec,int a);//待改进为模版函数，查找元素a是否在vec中

//与main过程有关的函数(需声明)
void setDateTime();//更新时间
void readJzFile();//将基站文件读入内存
void readTermMoveFile();//将终端路线读入内存

//和四叉树结构有关的函数(需声明)
int defineWhichQuadrant(Station* st,QuadTreeNode* tree);//查找这个基站相对于当前中心的象限
void diverseTree(QuadTreeNode* leaf);//将此树叶分为四个子节点
void addStationToTree(int index);//将索引为index基站添加到四叉树
void deleteMap(QuadTreeNode* head);//释放四叉树空间

//任务过程函数(需声明)
void task1Process();//任务1:遍历西北角和东南角的基站
void task2Process();//任务2:主体调用
void task3Process();//任务3:给定3个坐标，找到要求的基站
void task4Process();//任务4:类似任务3
void task5Process();//任务5过程
