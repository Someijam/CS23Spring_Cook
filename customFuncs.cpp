#include"customHeaders.h"//其他头文件在此文件中

using namespace std;

int QuadTreeNode::quarterWidth()//当前节点四分之一边长
{
    return pow(2,BORDER_EXP-1-(this->level));
}

QuadTreeNode* QuadTreeNode::northNode()//北侧区块
{
    int targetX=this->prefix.first;
    int targetY=this->prefix.second+1;
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
QuadTreeNode* QuadTreeNode::southNode()//南侧区块
{
    int targetX=this->prefix.first;
    int targetY=this->prefix.second-1;
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

void addStationToTree(Station st)//将基站st添加到四叉树
{
    QuadTreeNode* insertTarget=&MapRoot;
    while(!insertTarget->isLeaf)
    {
        insertTarget=insertTarget->children[defineWhichQuadrant(&st,insertTarget)];
    }
    //将insertTargrt定位到需要插入的位置
    if((insertTarget->includedStationNo.size()<MAX_UNIT_NUNS)&&(insertTarget->includedStationNo.size()>=0))
    {
        insertTarget->includedStationNo.push_back(st.no);
    }//叶节点没有满则继续插入
    else if(insertTarget->includedStationNo.size()==MAX_UNIT_NUNS)
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
        setDateTime();//更新日志文件里的时间
        logout<<"["<<fTime<<"]"<<"[STAD/ERR]此种情况绝对不会出现，除非是见鬼了：insertTarget->includedStationNo.size()="<<insertTarget->includedStationNo.size()<<endl;
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
        delete head;//MapRoot不是动态分配，不显式删除
        head=NULL;
    }
    return;
}

void task1Traverse()//任务1:遍历西北角和东南角的基站
{
    task1out<<"西北角区块基站数据："<<endl;
    QuadTreeNode* NWPartRoot=MapRoot.children[1];
    task1PreOrderTraverse_2(NWPartRoot);
    task1out<<"东南角区块基站数据："<<endl;
    QuadTreeNode* SEPartRoot=MapRoot.children[3];
    task1PreOrderTraverse_3(SEPartRoot);
    task1out<<"完成。"<<endl;
    return;
}

void task1PreOrderTraverse_2(QuadTreeNode* T)//一直往西北找的最小区域，备用
{
    if(!T)return;
    else
    {
        if(T->isLeaf)
        {
            if(!task1_2Finished)
            {
                for(int i=0;i<T->includedStationNo.size();i++)
                {
                    if(T->includedStationNo.size()>0&&i==0)
                    {
                        NW_estChunk=T;//记录最西北的区块的地址供后续任务使用
                        task1out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
                        task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
                        // task1out<<"#1/4Width="<<T->quarterWidth()<<" Center("<<T->x<<","<<T->y<<")"<<endl;
                    }
                    if(Stations[T->includedStationNo[i]].x!=0&&Stations[T->includedStationNo[i]].y!=0)
                    {
                        task1out<<"\t基站#"<<Stations[T->includedStationNo[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationNo[i]].x<<","<<Stations[T->includedStationNo[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationNo[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationNo[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
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

void task1PreOrderTraverse_3(QuadTreeNode* T)//一直往东南找的最小区域，备用
{
    if(!T)return;
    else
    {
        if(T->isLeaf)
        {
            if(!task1_3Finished)
            {
                for(int i=0;i<T->includedStationNo.size();i++)
                {
                    if(T->includedStationNo.size()>0&&i==0)
                    {
                        SE_estChunk=T;//记录最东南区块的地址
                        task1out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
                        task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
                        // task1out<<"#1/4Width="<<T->quarterWidth()<<" Center("<<T->x<<","<<T->y<<")"<<endl;
                    }
                    if(Stations[T->includedStationNo[i]].x!=0&&Stations[T->includedStationNo[i]].y!=0)
                    {
                        task1out<<"\t基站#"<<Stations[T->includedStationNo[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationNo[i]].x<<","<<Stations[T->includedStationNo[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationNo[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationNo[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
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

void task2PreOrderTraverse_1(QuadTreeNode* T)//任务2:遍历最西北角东侧子区域
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->westNode()==NW_estChunk))
        {
            task2out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
            // task2out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
            for(int i=0;i<T->includedStationNo.size();i++)
            {
                if(Stations[T->includedStationNo[i]].x!=0&&Stations[T->includedStationNo[i]].y!=0)
                {
                    task2out<<"\t基站#"<<Stations[T->includedStationNo[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationNo[i]].x<<","<<Stations[T->includedStationNo[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationNo[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationNo[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                }
            }
            if(T->includedStationNo.size()==0)task2out<<"\t此区块由其父节点分裂产生，但是没有基站"<<endl;
        }
        for(int i=0;i<4;i++)
        {
            task2PreOrderTraverse_1(T->children[i]);
        }
    }
    return;
}

void task2PreOrderTraverse_2(QuadTreeNode* T)//任务2:遍历最西北角南侧子区域
{
    if(!T)return;
    else
    {
        if(T->isLeaf&&(T->northNode()==NW_estChunk))
        {
            task2out<<"#Lv."<<T->level<<" 区块：("<<T->x-2*T->quarterWidth()<<"<=x<="<<T->x+2*T->quarterWidth()<<"),\t ("<<T->y-2*T->quarterWidth()<<"<=y<="<<T->y+2*T->quarterWidth()<<")"<<endl;
            // task1out<<"X:"<<T->prefix.first<<'\t'<<"Y:"<<T->prefix.second<<endl;
            for(int i=0;i<T->includedStationNo.size();i++)
            {
                if(Stations[T->includedStationNo[i]].x!=0&&Stations[T->includedStationNo[i]].y!=0)
                {
                    task2out<<"\t基站#"<<Stations[T->includedStationNo[i]].no<<":"<<"\t"<<"坐标("<<Stations[T->includedStationNo[i]].x<<","<<Stations[T->includedStationNo[i]].y<<")"<<"\t"<<"类别:"<<Stations[T->includedStationNo[i]].typeName<<"\t"<<"相对强度:"<<setiosflags(ios::fixed)<<setprecision(4)<<Stations[T->includedStationNo[i]].baseStrength<<resetiosflags(ios::fixed)<<endl;
                }
            }
            if(T->includedStationNo.size()==0)task2out<<"\t此区块由其父节点分裂产生，但是没有基站"<<endl;
        }
        for(int i=0;i<4;i++)
        {
            task2PreOrderTraverse_2(T->children[i]);
        }
    }
    return;
}

void task2Process()
{
    //最西北角的东侧
    task2out<<"最西北角的东侧有以下树叶区块:"<<endl;
    QuadTreeNode* NW_E=NW_estChunk->eastNode();
    if(NW_E)task2PreOrderTraverse_1(NW_E);
    task2out<<"---"<<endl;
    task2out<<endl;
    //最西北角的南侧
    task2out<<"最西北角的南侧有以下树叶区块:"<<endl;
    QuadTreeNode* NW_S=NW_estChunk->southNode();
    if(NW_S)task2PreOrderTraverse_2(NW_S);
    task2out<<"---"<<endl;
    task2out<<endl;
    //最东南角的西北侧
    task2out<<"最东南角的西北侧:"<<endl;
    // if(SE_estChunk->eastNode()->northNode())task1PreOrderTraverse_1(SE_estChunk->eastNode()->northNode());
    task2out<<"---"<<endl;
    task2out<<endl;
    //最东南角西北侧的再北侧
    task2out<<"最东南角西北侧的再北侧:"<<endl;
    // if(SE_estChunk->eastNode()->northNode()->northNode())task1PreOrderTraverse_1(SE_estChunk->eastNode()->northNode()->northNode());
    task2out<<"---"<<endl;
    return;
}

