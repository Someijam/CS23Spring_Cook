#include"customHeaders.h"//其他头文件在此文件中

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
        cerr<<"["<<fDate<<" "<<fTime<<"]"<<"[TDIV/ERR]此种情况绝对不会出现，除非是见鬼了：尝试将四叉树的非叶节点再次四分"<<endl;
        exit(0);
    }
    for(int i=0;i<4;i++)
    {
        leaf->children[i]=new QuadTreeNode;//此处动态分配了内存
        leaf->children[i]->isLeaf=true;
        leaf->children[i]->level=leaf->level+1; 
        leaf->children[i]->parent=leaf;
        for(int j=0;j<4;j++)
        {
            leaf->children[i]->children[j]=NULL;
        }
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
        cerr<<"["<<fDate<<" "<<fTime<<"]"<<"[STAD/ERR]此种情况绝对不会出现，除非是见鬼了：insertTarget->includedStationNo.size()="<<insertTarget->includedStationNo.size()<<endl;
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
        cout<<"["<<fDate<<" "<<fTime<<"]"<<"[Main/INFO]Deleted a stem in level#"<<head->level<<endl;
        delete head;//MapRoot不是动态分配，不显式删除
        head=NULL;
    }
    return;
}

