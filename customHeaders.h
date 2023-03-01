//工程全部的头文件
#include<iostream>
#include<fstream>
#include<iomanip>
#include<algorithm>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<vector>
#include<queue>
#include<ctime>
#ifdef _MSC_VER
#  include <nmmintrin.h>
#  define __builtin_popcount _mm_popcnt_u64
#endif
//宏定义
#define BORDER_EXP 17//地图尺寸指数
#define MAX_UNIT_NUMS (int)9//单分块最大基站数，在等级不超过下方MAX_LEVEL的情况下
#define MAX_LEVEL 8//四叉树最深树叶的等级
#define VCHUNK_HALFWIDTH 1000//虚拟分块宽度
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
    // QuadTreeNode* northNode();//北侧区块
    // QuadTreeNode* southNode();//南侧区块
    // QuadTreeNode* eastNode();//东侧区块
    // QuadTreeNode* westNode();//西侧区块
    // QuadTreeNode* nwNode();//西北区块
    // QuadTreeNode* neNode();//东北区块
    // QuadTreeNode* swNode();//西南区块
    // QuadTreeNode* seNode();//东南区块
};
struct Station//基站信息
{
    int x;
    int y;//坐标
    char typeName[20];//类别名称
    int type;//类别编号
    double baseStrength;//强度
    int no;//顺序编号
    double validDistance();//有效距离
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
struct FakeSt//伪基站路径
{
    double xs;
    double ys;
    double xe;
    double ye;
    double velocity;
    int startTime;
    int no;
    void getCurrentPosition(long double time,double &x,double &y);//方法，给定时间获取当前伪基站位置
};
struct Square//正方形区域
{
    int centerX;
    int centerY;//中心坐标
    int halfWidth;//宽度的一半
    bool isLeafIntersectsMe(QuadTreeNode* leaf);//四叉树叶与我相交吗?
    void collectLeavesInside(vector<QuadTreeNode*> &containerOfLeaves);//提供容器，收集与自己相交的四叉树叶
    void collectStationsInside(vector<int> &containerOfStations);//提供容器，收集自己内部的所有基站
    Square(int x,int y,int halfw);
    Square();
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
extern int maxX;
extern int maxY;
extern int minX;
extern int minY;
// extern int maxLevel;
extern int testx3[3];
extern int testy3[3];//任务3数据
extern int testx4[3];
extern int testy4[3];//任务4数据
extern vector<Route> terminalMovement;//终端运动轨迹
extern vector<FakeSt> fakeStationMovement;//伪基站移动轨迹

extern FILE* fJZin;
extern FILE* fRTin;
extern FILE* fWZin;

extern ofstream logout;
extern ofstream task1out;
extern ofstream task2out;
extern ofstream task3out;
extern ofstream task4out;
extern ofstream task5out;
extern ofstream ext1out;
extern ofstream ext2out;
extern ofstream adv1out;
extern ofstream adv2out;

//函数声明
//结构体定义中需要使用的方法函数(需声明)
void quadtreeAssistTraverse1(QuadTreeNode* T);//辅助函数1
void quadtreeAssistTraverse2(QuadTreeNode* T);//辅助函数2
void quadtreeAssistTraverse3(QuadTreeNode* T);//辅助函数3
void quadtreeAssistTraverse4(QuadTreeNode* T);//辅助函数4

//通用工具函数(需声明)
bool isInVector(vector<int> &vec,int a);//待改进为模版函数，查找元素a是否在vec中
double distanceBetween(double x1,double y1,double x2,double y2);//两点间距离公式

//与main过程有关的函数(需声明)
void setDateTime();//更新时间
void readJzFile();//将基站文件读入内存
void readTermMoveFile();//将终端路线读入内存
void readWZMoveFile();//将伪基站路径线性读入内存
void analyzeStatistics();//分析基站分布数据

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
void ext1Process(int i);//扩展1，备用
void ext2Process(int i1,int i2);//扩展2过程
void adv1Process(int i);//升级1过程
void adv2Process(int i);//升级2过程
void miscProcess();//杂项