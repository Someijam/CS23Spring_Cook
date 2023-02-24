#include"customHeaders.h"//其他头文件在此文件中

using namespace std;

//结构体定义中需要使用的方法函数(需声明)
int QuadTreeNode::quarterWidth()//当前节点四分之一边长
{
    return pow(2,BORDER_EXP-1-(this->level));
}
QuadTreeNode* QuadTreeNode::northNode()//北侧区块
{
    int targetX=this->prefix.first;
    int targetY=this->prefix.second+1;
    if(targetY>>this->level)return NULL;
    //以上面两个数的二进制形式寻找
    QuadTreeNode* currentNode=&MapRoot;
    for(int i=this->level;i>=1;i--)//要求：同级，如果达不到同级深度，则尽可能深
    {
        if(currentNode->isLeaf)break;

        if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[0];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[1];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[2];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[3];
    }
    return currentNode;
}
QuadTreeNode* QuadTreeNode::southNode()//南侧区块
{
    int targetX=this->prefix.first;
    int targetY=this->prefix.second-1;
    if(targetY<0)return NULL;
    //以上面两个数的二进制形式寻找
    QuadTreeNode* currentNode=&MapRoot;
    for(int i=this->level;i>=1;i--)//要求：同级，如果达不到同级深度，则尽可能深
    {
        if(currentNode->isLeaf)break;

        if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[0];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[1];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[2];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[3];
    }
    return currentNode;
}
QuadTreeNode* QuadTreeNode::eastNode()//东侧区块
{
    int targetX=this->prefix.first+1;
    int targetY=this->prefix.second;
    if(targetX>>this->level)return NULL;
    //以上面两个数的二进制形式寻找
    QuadTreeNode* currentNode=&MapRoot;
    for(int i=this->level;i>=1;i--)//要求：同级，如果达不到同级深度，则尽可能深
    {
        if(currentNode->isLeaf)break;

        if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[0];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[1];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[2];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[3];
    }
    return currentNode;
}
QuadTreeNode* QuadTreeNode::westNode()//西侧区块
{
    int targetX=this->prefix.first-1;
    int targetY=this->prefix.second;
    if(targetX<0)return NULL;
    //以上面两个数的二进制形式寻找
    QuadTreeNode* currentNode=&MapRoot;
    for(int i=this->level;i>=1;i--)//要求：同级，如果达不到同级深度，则尽可能深
    {
        if(currentNode->isLeaf)break;

        if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[0];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==1)currentNode=currentNode->children[1];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==0&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[2];
        else if(__builtin_popcount(targetX&(1<<(i-1)))==1&&__builtin_popcount(targetY&(1<<(i-1)))==0)currentNode=currentNode->children[3];
    }
    return currentNode;
}
QuadTreeNode* QuadTreeNode::nwNode()//西北区块
{
    tempNode=NULL;
    tempThis=this;
    if(this->westNode()==NULL||this->northNode()==NULL)return NULL;
    // if(this->westNode()->northNode()==this->northNode()->westNode())return this->westNode()->northNode();
    QuadTreeNode* currentNode=this->westNode()->northNode();
    quadtreeAssistTraverse1(currentNode);
    return tempNode;
}
QuadTreeNode* QuadTreeNode::neNode()//东北区块
{
    tempNode=NULL;
    tempThis=this;
    if(this->eastNode()==NULL||this->northNode()==NULL)return NULL;
    // if(this->eastNode()->northNode()==this->northNode()->eastNode())return this->eastNode()->northNode();
    QuadTreeNode* currentNode=this->eastNode()->northNode();
    quadtreeAssistTraverse2(currentNode);
    return tempNode;
}
QuadTreeNode* QuadTreeNode::swNode()//西南区块
{
    tempNode=NULL;
    tempThis=this;
    if(this->westNode()==NULL||this->southNode()==NULL)return NULL;
    // if(this->westNode()->southNode()==this->southNode()->westNode())return this->westNode()->southNode();
    QuadTreeNode* currentNode=this->westNode()->southNode();
    quadtreeAssistTraverse3(currentNode);
    return tempNode;
}
QuadTreeNode* QuadTreeNode::seNode()//东南区块
{
    tempNode=NULL;
    tempThis=this;
    if(this->eastNode()==NULL||this->southNode()==NULL)return NULL;
    // if(this->eastNode()->southNode()==this->southNode()->eastNode())return this->eastNode()->southNode();
    QuadTreeNode* currentNode=this->eastNode()->southNode();
    quadtreeAssistTraverse4(currentNode);
    return tempNode;
}
void quadtreeAssistTraverse1(QuadTreeNode* T)//辅助函数1
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->southNode()->eastNode()==tempThis)&&(T->eastNode()->southNode()==tempThis))
        {
            tempNode=T;
        }
        for(int i=0;i<4;i++)
        {
            quadtreeAssistTraverse1(T->children[i]);
        }
    }
    return;
}
void quadtreeAssistTraverse2(QuadTreeNode* T)//辅助函数2
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->southNode()->westNode()==tempThis)&&(T->westNode()->southNode()==tempThis))
        {
            tempNode=T;
        }
        for(int i=0;i<4;i++)
        {
            quadtreeAssistTraverse2(T->children[i]);
        }
    }
    return;
}
void quadtreeAssistTraverse3(QuadTreeNode* T)//辅助函数3
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->northNode()->eastNode()==tempThis)&&(T->eastNode()->northNode()==tempThis))
        {
            tempNode=T;
        }
        for(int i=0;i<4;i++)
        {
            quadtreeAssistTraverse3(T->children[i]);
        }
    }
    return;
}
void quadtreeAssistTraverse4(QuadTreeNode* T)//辅助函数4
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->northNode()->westNode()==tempThis)&&(T->westNode()->northNode()==tempThis))
        {
            tempNode=T;
        }
        for(int i=0;i<4;i++)
        {
            quadtreeAssistTraverse4(T->children[i]);
        }
    }
    return;
}

//C++通用工具函数(需声明)
bool isInVector(vector<int> &vec,int a)//待改进为模版函数，查找元素a是否在vec中
{
    vector<int>::iterator i;
    for(i=vec.begin();i!=vec.end();++i)//这里要改成++i
    {
        if(*i.base()==a)return true;
    }
    return false;
}

//与main过程有关的函数(需声明)
void setDateTime()//更新时间
{
    now = time(0);
    ltm = localtime(&now);
    fDate="";
    fDate=fDate+to_string(1900 + ltm->tm_year);
    fDate=fDate+"-";
    if(1+ltm->tm_mon<10)fDate=fDate+"0";
    fDate=fDate+to_string(1 + ltm->tm_mon);
    fDate=fDate+"-";
    if(ltm->tm_mday<10)fDate=fDate+"0";
    fDate=fDate+to_string(ltm->tm_mday);
    fTime="";
    if(ltm->tm_hour<10)fTime=fTime+"0";
    fTime=fTime+to_string(ltm->tm_hour);
    fTime=fTime+":";
    if(ltm->tm_min<10)fTime=fTime+"0";
    fTime=fTime+to_string(ltm->tm_min);
    fTime=fTime+":";
    if(ltm->tm_sec<10)fTime=fTime+"0";
    fTime=fTime+to_string(ltm->tm_sec);
}
void readJzFile()//将基站文件读入内存
{
    Station tempSt={0};
    Stations.push_back(tempSt);
    char inputType[5]={0};

    string jzfile="./test_data/jz001.txt";
    fJZin=freopen(jzfile.c_str(), "r", stdin);//默认是基站输入
    if(!fJZin)//检验文件是否打开
    {
        cerr<<"基站数据文件不存在的，是不是输错了？"<<endl;
        exit(0);
    }
    cin>>inputType;
    if(strcmp(inputType,"JZ")==0)//基站信息录入
    {
        while(scanf("%d,%d,%s %lf,%d",&tempSt.x,&tempSt.y,tempSt.typeName,&tempSt.baseStrength,&tempSt.no)==5)//5表示正常输入
        {
            if(strcmp(tempSt.typeName,"城区")==0)tempSt.type=0;
            else if(strcmp(tempSt.typeName,"乡镇")==0)tempSt.type=1;
            else if(strcmp(tempSt.typeName,"高速")==0)tempSt.type=2;
            else 
            {
                setDateTime();//更新日志文件里的时间
                logout<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件中基站类型不与城区乡镇和高速的任意一种匹配，请检查如下基站:编号#"<<tempSt.no<<endl;
            }
            Stations.push_back(tempSt);
            if(tempSt.type==2)ExpressWayStationsNo.push_back(tempSt.no);
        }
        if(tempSt.x!=-1||tempSt.y!=-1)
        {
            setDateTime();//更新日志文件里的时间
            logout<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件尾部或格式有误，检查是否为jz001.txt的错误版本"<<tempSt.no<<endl;
            exit(0);
        }
    }
    else
    {
        setDateTime();//更新日志文件里的时间
        logout<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件头部有误"<<endl;
        exit(0);
    }
    fclose(fJZin);

    // ofstream positionout;
    // positionout.open("./hints/positions2_express.txt",ios::out);
    // for(int i=0;i<Stations.size();i++)
    // {
    //     if(Stations[i].type==2)
    //         positionout<<Stations[i].x<<" "<<Stations[i].y<<endl;
    // }
    // exit(0);

    jzfile="./test_data/jz002.txt";
    fJZin=freopen(jzfile.c_str(), "r", stdin);//默认是基站输入
    if(!fJZin)//检验文件是否打开
    {
        cerr<<"基站数据文件不存在的，是不是输错了？"<<endl;
        exit(0);
    }
    cin>>inputType;
    if(strcmp(inputType,"JZ")==0)//基站信息录入
    {
        while(scanf("%d,%d,%s %lf,%d",&tempSt.x,&tempSt.y,tempSt.typeName,&tempSt.baseStrength,&tempSt.no)==5)//5表示正常输入
        {
            if(strcmp(tempSt.typeName,"城区")==0)tempSt.type=0;
            else if(strcmp(tempSt.typeName,"乡镇")==0)tempSt.type=1;
            else if(strcmp(tempSt.typeName,"高速")==0)tempSt.type=2;
            else 
            {
                setDateTime();//更新日志文件里的时间
                logout<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件中基站类型不与城区乡镇和高速的任意一种匹配，请检查如下基站:编号#"<<tempSt.no<<endl;
            }
            Stations.push_back(tempSt);
        }
        if(tempSt.x!=-1||tempSt.y!=-1)
        {
            setDateTime();//更新日志文件里的时间
            logout<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件尾部或格式有误，检查是否为jz001.txt的错误版本"<<tempSt.no<<endl;
            exit(0);
        }
    }
    else
    {
        setDateTime();//更新日志文件里的时间
        logout<<"["<<fTime<<"]"<<"[Main/ERR]"<<"基站文件头部有误"<<endl;
        exit(0);
    }
    fclose(fJZin);
    return;
}
void readTermMoveFile()//将终端路线读入内存
{
    Route tempSegment={0};
    terminalMovement.push_back(tempSegment);
    string rtFile="./test_data/yd001.txt";
    fRTin=freopen(rtFile.c_str(),"r",stdin);
    if(!fRTin)
    {
        cerr<<"基站移动路径文件不存在"<<endl;
        exit(0);
    }
    char inputType[5]={0};
    cin>>inputType;
    if(strcmp(inputType,"YD")==0)
    {
        int hr=0;
        int min=0;
        while(scanf("%lf,%lf,%lf,%lf,%lf,%d,%d",&tempSegment.xs,&tempSegment.ys,&tempSegment.xe,&tempSegment.ye,&tempSegment.velocity,&hr,&min)==7)//正常输入为7个参数
        {
            tempSegment.startTime=60*hr+min;
            terminalMovement.push_back(tempSegment);
        }
    }
    else
    {
        setDateTime();//更新日志文件里的时间
        logout<<"["<<fTime<<"]"<<"[Main/ERR]"<<"移动路径文件头部有误"<<endl;
        exit(0);
    }
    fclose(fRTin);
    return;
}

//和四叉树结构有关的函数(需声明)
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
        setDateTime();//更新日志文件里的时间
        logout<<"["<<fTime<<"]"<<"[TDIV/ERR]此种情况绝对不会出现，除非是见鬼了：尝试将四叉树的非叶节点再次四分"<<endl;
        exit(0);
    }
    for(int i=0;i<4;i++)
    {
        leaf->children[i]=new QuadTreeNode;//此处动态分配了内存
        leaf->children[i]->isLeaf=true;
        leaf->children[i]->level=leaf->level+1; 
        leaf->children[i]->parent=leaf;

        leaf->children[i]->prefix.first=leaf->prefix.first<<1;
        leaf->children[i]->prefix.second=leaf->prefix.second<<1;//编号

        for(int j=0;j<4;j++)
        {
            leaf->children[i]->children[j]=NULL;
        }
        if(i==0)
        {
            leaf->children[i]->x=leaf->x+leaf->quarterWidth();
            leaf->children[i]->y=leaf->y+leaf->quarterWidth();
            leaf->children[i]->prefix.first++;//(1,1)
            leaf->children[i]->prefix.second++;//编号
        }
        else if(i==1)
        {
            leaf->children[i]->x=leaf->x-leaf->quarterWidth();
            leaf->children[i]->y=leaf->y+leaf->quarterWidth();
            leaf->children[i]->prefix.second++;//编号(0,1)
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
            leaf->children[i]->prefix.first++;//编号(1,1)
        }
    }
    leaf->isLeaf=false;
    return;
}
void addStationToTree(int index)//将索引为index基站添加到四叉树
{
    QuadTreeNode* insertTarget=&MapRoot;
    while(!insertTarget->isLeaf)
    {
        insertTarget=insertTarget->children[defineWhichQuadrant(&Stations[index],insertTarget)];
    }
    //将insertTargrt定位到需要插入的位置
    if((insertTarget->includedStationIndex.size()<MAX_UNIT_NUNS)&&(insertTarget->includedStationIndex.size()>=0))
    {
        insertTarget->includedStationIndex.push_back(index);
    }//叶节点没有满则继续插入
    else if(insertTarget->includedStationIndex.size()==MAX_UNIT_NUNS)
    {
        diverseTree(insertTarget);
        for(int i=0;i<insertTarget->includedStationIndex.size();i++)
        {
            insertTarget->children[defineWhichQuadrant(&Stations[insertTarget->includedStationIndex[i]],insertTarget)]->includedStationIndex.push_back(insertTarget->includedStationIndex[i]);
            //将 当前节点基站索引存储容器的第i个人 添加到 当前节点的 第（第i个基站相对于当前节点的）象限的子节点 的基站索引存储容器
        }//转移当前的9个站点序号到下面四个节点
        insertTarget->includedStationIndex.clear();
        // insertTarget->children[defineWhichQuadrant(&st,insertTarget)]->includedStationIndex.push_back(st.no);//转移完毕，有很大概率上面的9个还是会挤到一起，所以得递归调用
        addStationToTree(index);//递归调用，上面节点挤到一起了还得再分
    }//叶节点满了就转移到子节点稍后再插入
    else
    {
        setDateTime();//更新日志文件里的时间
        logout<<"["<<fTime<<"]"<<"[STAD/ERR]此种情况绝对不会出现，除非是见鬼了：insertTarget->includedStationIndex.size()="<<insertTarget->includedStationIndex.size()<<endl;
        exit(0);
    }

    return;
}
void deleteMap(QuadTreeNode* head)//释放四叉树空间
{
    if(head==NULL)
        return;//到尾巴就回
    for(int i=0;i<4;i++)
    {
        deleteMap(head->children[i]);//这里触发过报错：head不存在但是不等于NULL
    }
    if(head->level!=0)
    {
        setDateTime();//更新日志文件里的时间
        // logout<<"["<<fTime<<"]"<<"[Main/INFO]Deleted a stem in level#"<<head->level<<endl;
        // if(head->level>maxLevel)maxLevel=head->level;
        delete head;//MapRoot不是动态分配，不显式删除
        head=NULL;
    }
    return;
}

//非通用工具函数
QuadTreeNode* positionInWhichChunk(int x,int y)//当前坐标的点在哪一个最小区块内
{
    QuadTreeNode* currentChunk=&MapRoot;
    while (!currentChunk->isLeaf)
    {
        int quadrant=-1;
        if((x-currentChunk->x>0)&&(y-currentChunk->y>=0))quadrant=0;
        else if((x-currentChunk->x<=0)&&(y-currentChunk->y>0))quadrant=1;
        else if((x-currentChunk->x<0)&&(y-currentChunk->y<=0))quadrant=2;
        else if((x-currentChunk->x>=0)&&(y-currentChunk->y<0))quadrant=3;
        currentChunk=currentChunk->children[quadrant];
    }
    return currentChunk;
}
double distanceFromSttoPoint(Station st,int posx,int posy)//计算基站到考察点的距离
{
    return sqrt(pow(posx-st.x,2)+pow(posy-st.y,2));
}
double currentPointSignalStrength(Station st,int x,int y)//计算基站到当前点的相对强度
{
    int R[3]={300,1000,5000};
    return st.baseStrength*pow((R[st.type]/distanceFromSttoPoint(st,x,y)),2);
}
void stationsNearBy(vector<int> &nearbyStationsIndex,int posx,int posy)//工具函数，给定点坐标，收集附近的基站到容器中。
{
    QuadTreeNode* T=positionInWhichChunk(posx,posy);
    //城镇和乡镇只需找自己的区块以及临近的区块
    for(int i=0;i<T->includedStationIndex.size();i++)
    {
        if(distanceFromSttoPoint(Stations[T->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[T->includedStationIndex[i]].baseStrength))&&Stations[T->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(T->includedStationIndex[i]);//城镇基站允许收录的条件
        if(distanceFromSttoPoint(Stations[T->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[T->includedStationIndex[i]].baseStrength))&&Stations[T->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(T->includedStationIndex[i]);//乡镇基站允许收录的条件
    }
    QuadTreeNode* neighborTChunk=T->northNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    neighborTChunk=T->southNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    neighborTChunk=T->westNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    neighborTChunk=T->eastNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    neighborTChunk=T->nwNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    neighborTChunk=T->neNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    neighborTChunk=T->swNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    neighborTChunk=T->seNode();
    if(neighborTChunk)
    {
        for(int i=0;i<neighborTChunk->includedStationIndex.size();i++)
        {
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(300*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==0)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//城镇基站允许收录的条件
            if(distanceFromSttoPoint(Stations[neighborTChunk->includedStationIndex[i]],posx,posy)<=(1000*sqrt(Stations[neighborTChunk->includedStationIndex[i]].baseStrength))&&Stations[neighborTChunk->includedStationIndex[i]].type==1)nearbyStationsIndex.push_back(neighborTChunk->includedStationIndex[i]);//乡镇基站允许收录的条件
        }
    }
    //高速基站单独比较
    for(int i=0;i<ExpressWayStationsNo.size();i++)
    {
        if(distanceFromSttoPoint(Stations[ExpressWayStationsNo[i]],posx,posy)<=5000*sqrt(Stations[ExpressWayStationsNo[i]].baseStrength))
            nearbyStationsIndex.push_back(ExpressWayStationsNo[i]);//高速基站收录条件
    }
    return;
}
int bestMatchStation(int x,int y)//工具函数，给定x,y返回最优基站在Stations中的索引
{
    vector<int> nearbyStationsIndex;
    stationsNearBy(nearbyStationsIndex,x,y);
    int index=0;
    if(nearbyStationsIndex.size()==0)return 0;//附近没有基站，返回0
    int strongestStationIndex=nearbyStationsIndex[0];
    for(int i=0;i<nearbyStationsIndex.size();i++)
    {
        if(currentPointSignalStrength(Stations[strongestStationIndex],x,y)<currentPointSignalStrength(Stations[nearbyStationsIndex[i]],x,y))strongestStationIndex=nearbyStationsIndex[i];
    }
    return strongestStationIndex;
}
void getCurrentPosition(long double currentTime,int routeNo,double &x,double &y)//给时间和路径序号，获得终端当前坐标
{
    double cosTheta=(terminalMovement[routeNo].xe-terminalMovement[routeNo].xs)/sqrt(pow(terminalMovement[routeNo].xe-terminalMovement[routeNo].xs,2)+pow(terminalMovement[routeNo].ye-terminalMovement[routeNo].ys,2));
    double sinTheta=(terminalMovement[routeNo].ye-terminalMovement[routeNo].ys)/sqrt(pow(terminalMovement[routeNo].xe-terminalMovement[routeNo].xs,2)+pow(terminalMovement[routeNo].ye-terminalMovement[routeNo].ys,2));
    double r=(50*terminalMovement[routeNo].velocity*(currentTime-terminalMovement[routeNo].startTime))/3.0;
    x=terminalMovement[routeNo].xs+r*cosTheta;
    y=terminalMovement[routeNo].ys+r*sinTheta;
    return;
}
void printDoubleMinToTime(long double time,ofstream &fout)//给出离散时间和流，输出格式时间
{
    int hr=int(time/60);
    int min=int(time)%60;
    long double sec=60*(time-int(time));
    if(hr<10)fout<<"0";
    fout<<hr<<":";
    if(min<10)fout<<"0";
    fout<<min<<":";
    if(sec<10)fout<<"0";
    fout<<setiosflags(ios::fixed)<<setprecision(3)<<sec;//<<resetiosflags(ios::fixed);
    // fout<<sec;
    return;
}
//任务辅助函数
void task1PreOrderTraverse_2(QuadTreeNode* T)//任务1:一直往西北找的最小区域，1023遍历
{
    if(!T)return;
    else
    {
        if(T->isLeaf)
        {
            if(!task1_2Finished)
            {
                for(int i=0;i<T->includedStationIndex.size();i++)
                {
                    if(T->includedStationIndex.size()>0&&i==0)
                    {
                        NW_estChunk=T;//记录最西北的区块的地址供后续任务使用
                        task1out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
                        task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
                        // task1out<<"#1/4Width="<<T->quarterWidth()<<" Center("<<T->x<<","<<T->y<<")"<<endl;
                    }
                    if(Stations[T->includedStationIndex[i]].x!=0&&Stations[T->includedStationIndex[i]].y!=0)
                    {
                        task1out<<"\t基站#"<<Stations[T->includedStationIndex[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationIndex[i]].x<<","<<Stations[T->includedStationIndex[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationIndex[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationIndex[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                        task1_2Finished=true;
                    }
                }
            }
        }
        task1PreOrderTraverse_2(T->children[1]);
        task1PreOrderTraverse_2(T->children[0]);
        task1PreOrderTraverse_2(T->children[2]);
        task1PreOrderTraverse_2(T->children[3]);
    }
    return;
}
void task1PreOrderTraverse_3(QuadTreeNode* T)//任务1:一直往东南找的最小区域，3021遍历
{
    if(!T)return;
    else
    {
        if(T->isLeaf)
        {
            if(!task1_3Finished)
            {
                for(int i=0;i<T->includedStationIndex.size();i++)
                {
                    if(T->includedStationIndex.size()>0&&i==0)
                    {
                        SE_estChunk=T;//记录最东南区块的地址
                        task1out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
                        task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
                        // task1out<<"#1/4Width="<<T->quarterWidth()<<" Center("<<T->x<<","<<T->y<<")"<<endl;
                    }
                    if(Stations[T->includedStationIndex[i]].x!=0&&Stations[T->includedStationIndex[i]].y!=0)
                    {
                        task1out<<"\t基站#"<<Stations[T->includedStationIndex[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationIndex[i]].x<<","<<Stations[T->includedStationIndex[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationIndex[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationIndex[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                        task1_3Finished=true;
                    }
                }
            }
        }
        task1PreOrderTraverse_3(T->children[3]);
        task1PreOrderTraverse_3(T->children[0]);
        task1PreOrderTraverse_3(T->children[2]);
        task1PreOrderTraverse_3(T->children[1]);
    }
    return;
}
void task2PreOrderTraverse_1(QuadTreeNode* T)//任务2:遍历最西北角东侧子区域,遍历验证可逆区块
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->westNode()==NW_estChunk))
        {
            task2out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
            // task2out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
            for(int i=0;i<T->includedStationIndex.size();i++)
            {
                if(Stations[T->includedStationIndex[i]].x!=0&&Stations[T->includedStationIndex[i]].y!=0)
                {
                    task2out<<"\t基站#"<<Stations[T->includedStationIndex[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationIndex[i]].x<<","<<Stations[T->includedStationIndex[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationIndex[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationIndex[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                }
            }
            if(T->includedStationIndex.size()==0)task2out<<"\t此区块由其父节点分裂产生，但是没有基站"<<endl;
        }
        for(int i=0;i<4;i++)
        {
            task2PreOrderTraverse_1(T->children[i]);
        }
    }
    return;
}
void task2PreOrderTraverse_2(QuadTreeNode* T)//任务2:遍历最西北角南侧子区域,遍历验证可逆区块
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->northNode()==NW_estChunk))
        {
            task2out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
            // task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
            for(int i=0;i<T->includedStationIndex.size();i++)
            {
                if(Stations[T->includedStationIndex[i]].x!=0&&Stations[T->includedStationIndex[i]].y!=0)
                {
                    task2out<<"\t基站#"<<Stations[T->includedStationIndex[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationIndex[i]].x<<","<<Stations[T->includedStationIndex[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationIndex[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationIndex[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                }
            }
            if(T->includedStationIndex.size()==0)task2out<<"\t此区块由其父节点分裂产生，但是没有基站"<<endl;
        }
        for(int i=0;i<4;i++)
        {
            task2PreOrderTraverse_2(T->children[i]);
        }
    }
    return;
}
void task2PreOrderTraverse_3(QuadTreeNode* T)//任务2:遍历最东南角西北侧子区域
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->southNode()->eastNode()==SE_estChunk)&&(T->eastNode()->southNode()==SE_estChunk))
        {
            SE_nwChunk=T;
            task2out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
            // task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
            for(int i=0;i<T->includedStationIndex.size();i++)
            {
                if(Stations[T->includedStationIndex[i]].x!=0&&Stations[T->includedStationIndex[i]].y!=0)
                {
                    task2out<<"\t基站#"<<Stations[T->includedStationIndex[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationIndex[i]].x<<","<<Stations[T->includedStationIndex[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationIndex[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationIndex[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                }
            }
            if(T->includedStationIndex.size()==0)task2out<<"\t此区块由其父节点分裂产生，但是没有基站"<<endl;
        }
        for(int i=0;i<4;i++)
        {
            task2PreOrderTraverse_3(T->children[i]);
        }
    }
    return;
}
void task2PreOrderTraverse_4(QuadTreeNode* T)//任务2:遍历最东南角西北侧再北侧的子区域
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->southNode()==SE_nwChunk))
        {
            task2out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
            // task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
            for(int i=0;i<T->includedStationIndex.size();i++)
            {
                if(Stations[T->includedStationIndex[i]].x!=0&&Stations[T->includedStationIndex[i]].y!=0)
                {
                    task2out<<"\t基站#"<<Stations[T->includedStationIndex[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationIndex[i]].x<<","<<Stations[T->includedStationIndex[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationIndex[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationIndex[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                }
            }
            if(T->includedStationIndex.size()==0)task2out<<"\t此区块由其父节点分裂产生，但是没有基站"<<endl;
        }
        for(int i=0;i<4;i++)
        {
            task2PreOrderTraverse_4(T->children[i]);
        }
    }
    return;
}

//任务过程函数(需声明)
void task1Process()//任务1:遍历西北角和东南角的基站
{
    task1out<<"[ANS-Main/1-2]西北角区块基站数据："<<endl;
    QuadTreeNode* NWPartRoot=MapRoot.children[1];
    task1PreOrderTraverse_2(NWPartRoot);
    task1out<<"[ANS-Main/1-3]东南角区块基站数据："<<endl;
    QuadTreeNode* SEPartRoot=MapRoot.children[3];
    task1PreOrderTraverse_3(SEPartRoot);
    task1out<<"完成。"<<endl;
    return;
}
void task2Process()//任务2:主体调用
{
    //最西北角的东侧
    task2out<<"[ANS-Main/2-1]最西北角的东侧有以下树叶区块:"<<endl;
    QuadTreeNode* NW_E=NW_estChunk->eastNode();
    if(NW_E)task2PreOrderTraverse_1(NW_E);
    task2out<<"---"<<endl;
    task2out<<endl;
    //最西北角的南侧
    task2out<<"[ANS-Main/2-2]最西北角的南侧有以下树叶区块:"<<endl;
    QuadTreeNode* NW_S=NW_estChunk->southNode();
    if(NW_S)task2PreOrderTraverse_2(NW_S);
    task2out<<"---"<<endl;
    task2out<<endl;
    //最东南角的西北侧
    task2out<<"[ANS-Main/2-3]最东南角的西北侧有以下树叶区块:"<<endl;
    QuadTreeNode* SE_NW=SE_estChunk->westNode()->northNode();
    if(SE_NW)task2PreOrderTraverse_3(SE_NW);
    task2out<<"---"<<endl;
    task2out<<endl;
    //最东南角西北侧的再北侧
    task2out<<"[ANS-Main/2-4]最东南角西北侧的再北侧有以下树叶区块:"<<endl;
    QuadTreeNode* SE_NW_N=SE_nwChunk->northNode();
    if(SE_NW_N)task2PreOrderTraverse_4(SE_NW_N);
    task2out<<"完成"<<endl;
    return;
}
void task3Process()//任务3:给定3个坐标，找到要求的基站
{
    for(int i=0;i<3;i++)
    {
        task3out<<"[ANS-Main/3-"<<i+1<<"]";
        task3out<<"位置坐标("<<testx3[i]<<","<<testy3[i]<<")附近";
        vector<int> nearbyStationsIndex;
        //分3种条件，遍历3次，保证找到所有类型的基站，存放到nearByStationsIndex容器中
        //城镇、乡镇：当前区块和周围区块即可(区块最深8级，宽1024)，高速单独比较
        stationsNearBy(nearbyStationsIndex,testx3[i],testy3[i]);
        //在上面的容器中找到信号最强的那一个序号
        if(nearbyStationsIndex.size()==0)
        {
            task3out<<"没有符合要求的基站"<<endl;
            continue;
        }//没有符合要求的基站
        int strongestStationIndex=nearbyStationsIndex[0];
        for(int j=0;j<nearbyStationsIndex.size();j++)
        {
            if(currentPointSignalStrength(Stations[strongestStationIndex],testx3[i],testy3[i])<currentPointSignalStrength(Stations[nearbyStationsIndex[j]],testx3[i],testy3[i]))strongestStationIndex=nearbyStationsIndex[i];
        }
        task3out<<"的最优信号基站为:\t编号#"<<Stations[strongestStationIndex].no<<"\t基站位置:("<<Stations[strongestStationIndex].x<<","<<Stations[strongestStationIndex].y<<")"<<"\t类型:"<<Stations[strongestStationIndex].typeName<<"\t距离:"<<distanceFromSttoPoint(Stations[strongestStationIndex],testx3[i],testy3[i])<<"\t相对强度:"<<currentPointSignalStrength(Stations[strongestStationIndex],testx3[i],testy3[i])<<endl;
        task3out<<"附近所有的基站:";
        for(int j=0;j<nearbyStationsIndex.size();j++)
        {
            task3out<<Stations[nearbyStationsIndex[j]].no<<" ";
        }
        task3out<<endl;
    }
    task3out<<"完成"<<endl;
    return;
}
void task4Process()//任务4:类似任务3
{
    for(int i=0;i<3;i++)
    {
        task4out<<"[ANS-Main/4-"<<i+1<<"]";
        task4out<<"位置坐标("<<testx4[i]<<","<<testy4[i]<<")附近";
        vector<int> nearbyStationsIndex;
        //分3种条件，遍历3次，保证找到所有类型的基站，存放到nearByStationsIndex容器中
        //城镇、乡镇：当前区块和周围区块即可(区块最深8级，宽1024)，高速单独比较
        stationsNearBy(nearbyStationsIndex,testx4[i],testy4[i]);//这里也适用任务3的函数
        //在上面的容器中找到信号最强的那一个序号
        if(nearbyStationsIndex.size()==0)
        {
            task4out<<"没有符合要求的基站"<<endl;
            continue;
        }//没有符合要求的基站
        int strongestStationIndex=nearbyStationsIndex[0];
        for(int j=0;j<nearbyStationsIndex.size();j++)
        {
            if(currentPointSignalStrength(Stations[strongestStationIndex],testx4[i],testy4[i])<currentPointSignalStrength(Stations[nearbyStationsIndex[j]],testx4[i],testy4[i]))strongestStationIndex=nearbyStationsIndex[i];
        }
        task4out<<"的最优信号基站为:\t编号#"<<Stations[strongestStationIndex].no<<"\t基站位置:("<<Stations[strongestStationIndex].x<<","<<Stations[strongestStationIndex].y<<")"<<"\t类型:"<<Stations[strongestStationIndex].typeName<<"\t距离:"<<distanceFromSttoPoint(Stations[strongestStationIndex],testx4[i],testy4[i])<<"\t相对强度:"<<currentPointSignalStrength(Stations[strongestStationIndex],testx4[i],testy4[i])<<endl;
        task4out<<"附近所有的基站:";
        for(int j=0;j<nearbyStationsIndex.size();j++)
        {
            task4out<<Stations[nearbyStationsIndex[j]].no<<" ";
        }
        task4out<<endl;
    }
    task4out<<"完成"<<endl;
    return;
}
void task5Process()//任务5过程
{
    task5out<<"[ANS-Main/5]"<<endl;
    vector<int> passedStationsIndexType0;
    vector<int> passedStationsIndexType1;
    vector<int> passedStationsIndexType2;
    int lastConnectedStationIndex=-1;//刚才连上的基站编号
    for(int i=1;i<terminalMovement.size();i++)//第i段移动轨迹
    {
        task5out<<"终端正在第"<<i<<"段路径上移动:"<<endl;
        int endTime;
        if(i==terminalMovement.size()-1)endTime=1140;
        else endTime=terminalMovement[i+1].startTime;//结束时间为下一段路径的开始时间，最后一次是19:00(1140)
        double presentX=terminalMovement[i].xs;
        double presentY=terminalMovement[i].ys;//设置好起始坐标
        
        for(double globalMapTime=terminalMovement[i].startTime;globalMapTime<=endTime;globalMapTime+=(1.0/60))//分度值为1/60min(1s)
        {
            getCurrentPosition(globalMapTime,i,presentX,presentY);//当前时间的坐标已经存入presentX presentY
            int shouldConnectStationIndex=bestMatchStation(presentX,presentY);
            if(shouldConnectStationIndex==lastConnectedStationIndex)continue;//相同，不用切换
            //以下为输出
            task5out<<"\t["<<int(globalMapTime/60)<<":";
            if(int(globalMapTime)%60<10)task5out<<"0";
            task5out<<int(globalMapTime)%60<<":";
            double sec=60*(globalMapTime-int(globalMapTime));
            if(int(sec)<10)task5out<<"0";
            task5out<<sec<<"] ";
            if(shouldConnectStationIndex==0)
            {
                task5out<<"无信号"<<endl;
            }
            else 
            {
                if(Stations[shouldConnectStationIndex].type==0&&(!isInVector(passedStationsIndexType0,shouldConnectStationIndex)))passedStationsIndexType0.push_back(shouldConnectStationIndex);
                else if(Stations[shouldConnectStationIndex].type==1&&(!isInVector(passedStationsIndexType1,shouldConnectStationIndex)))passedStationsIndexType1.push_back(shouldConnectStationIndex);
                else if(Stations[shouldConnectStationIndex].type==2&&(!isInVector(passedStationsIndexType2,shouldConnectStationIndex)))passedStationsIndexType2.push_back(shouldConnectStationIndex);
                task5out<<"切换到基站#"<<Stations[shouldConnectStationIndex].no<<"\t类型:"<<Stations[shouldConnectStationIndex].typeName<<endl;
            }
            lastConnectedStationIndex=shouldConnectStationIndex;
        }
    }
    task5out<<"---"<<endl;
    task5out<<"经过以下"<<passedStationsIndexType0.size()<<"个城区基站:"<<endl;
    for(int i=0;i<passedStationsIndexType0.size();i++)
    {
        if(i%10==0)task5out<<"\t";
        task5out<<Stations[passedStationsIndexType0[i]].no<<"  \t";
        if(i%10==9)task5out<<endl;
    }
    task5out<<endl;
    task5out<<"经过以下"<<passedStationsIndexType1.size()<<"个乡镇基站:"<<endl;
    for(int i=0;i<passedStationsIndexType1.size();i++)
    {
        if(i%10==0)task5out<<"\t";
        task5out<<Stations[passedStationsIndexType1[i]].no<<"  \t";
        if(i%10==9)task5out<<endl;
    }
    task5out<<endl;
    task5out<<"经过以下"<<passedStationsIndexType2.size()<<"个高速基站:"<<endl;
    task5out<<"\t";
    for(int i=0;i<passedStationsIndexType2.size();i++)
    {
        task5out<<Stations[passedStationsIndexType2[i]].no<<" ";
    }
    task5out<<endl;
    task5out<<"完成"<<endl;
    return;
}
void ext1Process()//扩展1过程
{
    int validConnections=0;
    ext1out<<"终端正在第1段路径上移动:"<<endl;
    int endTime=11*60+30;//第一段路径时长30min
    double presentX=terminalMovement[1].xs;
    double presentY=terminalMovement[1].ys;//设置好起始坐标
    long double leftEntryTime=0;
    long double rightEntryTime=0;
    long double leftExitTime=0;
    long double rightExitTime=0;//二分法的四个时间
    for(long double globalMapTime=terminalMovement[1].startTime;globalMapTime<=endTime;globalMapTime+=(1.0/60))//分度值为1/60min(1s)
    {
        getCurrentPosition(globalMapTime,1,presentX,presentY);//当前时间的坐标已经存入presentX presentY
        int shouldConnectStationIndex=bestMatchStation(presentX,presentY);
        if(validConnections==0&&shouldConnectStationIndex!=0)//条件：第一次进入有信号区域
        {
            rightEntryTime=globalMapTime;
            leftEntryTime=globalMapTime-(1.0/60);//记录进入瞬间的两个时间边界
            validConnections=1;
        }
        if(validConnections==1&&shouldConnectStationIndex==0)//条件：第一次离开有信号区域
        {
            rightExitTime=globalMapTime;
            leftExitTime=globalMapTime-(1.0/60);//记录离开瞬间的两个时间边界
            validConnections=0;
            break;
        }
    }

    long double midEntryTime=0;
    ext1out<<"对连接上第一个基站的时间二分求精确值"<<endl;
    while(rightEntryTime-leftEntryTime>=1.0/600)//进入阶段二分
    {
        ext1out<<"\tleftTime=";
        printDoubleMinToTime(leftEntryTime,ext1out);
        ext1out<<resetiosflags(ios::fixed);
        ext1out<<"  \trightTime=";
        printDoubleMinToTime(rightEntryTime,ext1out);
        ext1out<<resetiosflags(ios::fixed);
        ext1out<<"\tDelta_t="<<60*(rightEntryTime-leftEntryTime)<<"s."<<endl;
        double x=0;
        double y=0;
        midEntryTime=(rightEntryTime+leftEntryTime)/2.0;
        getCurrentPosition(midEntryTime,1,x,y);
        int matchNo=bestMatchStation(x,y);
        if(matchNo!=0)rightEntryTime=midEntryTime;//连上了
        else if(matchNo==0)leftEntryTime=midEntryTime;//没连上
    }
    ext1out<<"[ANS-Ext/1-1]Precise Time=";
    printDoubleMinToTime(midEntryTime,ext1out);
    ext1out<<"\tDelta_t=(+/-)"<<30*(rightEntryTime-leftEntryTime)<<"s."<<endl;

    ext1out<<endl;

    long double midExitTime=0;
    ext1out<<"对离开第一个基站有效范围的时间二分求精确值"<<endl;
    while(rightExitTime-leftExitTime>=1.0/600)//进入阶段二分
    {
        ext1out<<"\tleftTime=";
        printDoubleMinToTime(leftExitTime,ext1out);
        ext1out<<resetiosflags(ios::fixed);
        ext1out<<"  \trightTime=";
        printDoubleMinToTime(rightExitTime,ext1out);
        ext1out<<resetiosflags(ios::fixed);
        ext1out<<"\tDelta_t="<<60*(rightExitTime-leftExitTime)<<"s."<<endl;
        double x=0;
        double y=0;
        midExitTime=(rightExitTime+leftExitTime)/2.0;
        getCurrentPosition(midExitTime,1,x,y);
        int matchNo=bestMatchStation(x,y);
        if(matchNo!=0)rightExitTime=midExitTime;//连上了
        else if(matchNo==0)leftExitTime=midExitTime;//没连上
    }
    ext1out<<"[ANS-Ext/1-2]Precise Time=";
    printDoubleMinToTime(midExitTime,ext1out);
    ext1out<<"\tDelta_t=(+/-)"<<30*(rightExitTime-leftExitTime)<<"s."<<endl;
    ext1out<<"完成"<<endl;
    return;
}
