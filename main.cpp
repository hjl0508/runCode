#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;
//动态规划法做的
int uniquePaths(int m, int n) {
    int f[102][102] = {0};
    for(int i=1;i<=m;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==1&&j==1)
            {
                f[1][1] = 1;
            }
            else
            {
                f[j][i] = f[j-1][i] + f[j][i-1];
                cout<<"i:"<<i<<",j:"<<j<<endl;
                cout<<"f[j-1][i]"<<f[j-1][i]<<",f[j][i-1]"<<f[j][i-1]<<endl;
            }
        }
    }
    return f[n][m];
}
//字符串复制，基础版本
void mycopy(char* dst,const char* src)
{
    assert(src);
    assert(dst);
    while(*src != '\0')
    {
        *dst++ = *src++;
    }
}
#pragma pack(4)
struct testS
{
    int x;
    double y;
    char z;
    bool a;
};

//堆排序
//调整堆的某一个节点，将数组当成一个完全二叉树来调整，让所有的孩子节点小于自己的父节点
void adjustHeap(vector<int>& a,int length,int index)
{
    //堆是把数组当成一个完全二叉树来排列，因此做孩子为2*i+1,右孩子下标为2*i+2
    int left = 2*index + 1;
    int right = 2*index + 2;
    int tmp =  index;
    //判断父节点和子节点的大小
    if(left < length && a[left] > a[tmp])
    {
        tmp = left;
    }
    if(right < length && a[right] > a[tmp])
    {
        tmp = right;
    }

    //如果子节点大于父节点，则让大的节点当父节点，并且继续调整被交换后的节点，防止新的子节点小于其子节点的子节点。
    if(tmp != index)
    {
        int atmp = a[index];
        a[index] = a[tmp];
        a[tmp] = atmp;
        adjustHeap(a,length,tmp);
    }
}

void heapSort(vector<int>& a)
{
    int length = a.size();
    //从最后一个有子节点的节点开始调整。完全二叉树的特性中间节点左侧即为上述节点
    for(int i = length/2 -1;i >= 0;--i)
    {
        adjustHeap(a,length,i);
    }
    //构建完大顶堆，然后进行堆排序
    //堆排序的过程为，每次把堆顶的最大值和最后一个值调换，然后排除最后一个值重新调整。
    //这样最后出来的就是有序队列
    for(int len = length-1;len>=0;--len)
    {
        int tmp = a[len];
        a[len] = a[0];
        a[0] = tmp;
        adjustHeap(a,len,0);
    }
}

//快速排序
void oneSort(vector<int>&a,int beg,int end)
{
    if(beg>=end) return;

    int tmp = a[beg];
    int t_beg = beg;
    int t_end = end;
    while(beg<end)
    {
        while(end>beg&&a[end]>=tmp) end--;
        a[beg] = a[end];
        while(end>beg&&a[beg]<=tmp) beg++;
        a[end] = a[beg];
    }
    
    a[beg] = tmp;
    oneSort(a,t_beg,beg-1);
    oneSort(a,beg+1,t_end);
}
void fastSort(vector<int>& a)
{
    int len = a.size();
    int beg = 0;
    int end = len -1;
    oneSort(a,beg,end);
}

//回溯法解决0-1背包问题
//将不同价值的物品放入固定容量的背包，如何使背包中物品价值最高
//结果集是一个完全二叉树，遍历一遍
//回溯法一般就是用递归，深度遍历结果集合，试探性的解决问题和剪枝
const int N = 3; //物品的总数量
const int C = 16; //背包的总重量

int w[N] = {10,8,5}; //每个物品的重量
int v[N] = {5,4,1}; //物品的价值

int all_w = 0; //总重量
int all_v = 0; //总价值
int best_v = 0; //最优解
int bestx[N];
int x[N] = {0,0,0}; //物品是否放入背包，0：不放，1：放

void beibao(int t)
{
    if(t>N-1)
    {
        //遍历到最后一个物品，查看最优解
        if(best_v < all_v)
        {
            best_v = all_v;
            for(int i=0;i<N;++i)bestx[i] = x[i];
        }
    }
    else
    {
        //遍历当前节点的子节点
        for(int i=0;i<=1;i++)
        {
            x[t] = i;
            //不放入背包
            if(i == 0)
            {
                beibao(t+1);
            }
            else
            {
                if(all_w + w[t] <= C)
                {
                    all_w += w[t];
                    all_v += v[t];
                    beibao(t+1);
                    all_w -= w[t];
                    all_v -= v[t];
                }
            }
        }
    }
}

int main()
{
    //cout<<uniquePaths(1,2)<<endl;
    cout<<sizeof(testS)<<endl;
    //const char* a = "test";
    //char* b = new char[10];
    //mycopy(b,a);
    //cout<<"test:"<<b<<endl;
    vector<int> x = {3,4,1,5,2,29,4,33,2};
    //heapSort(x);
    beibao(0);
    for(auto v:bestx)cout<<v<<",";
}