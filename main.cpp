#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>

using namespace std;
//动态规划法做的
int uniquePaths(int m, int n) {
    int f[102][102] = {{0}};
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
namespace Beibao
{
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

}//只是为了把背包问题的代码放入模块不影响其他算法

//八皇后问题
//问题：在n×n格的棋盘上放置彼此不受攻击的n个皇后。按照国际象棋的规则，皇后可以攻击与之处在同一行或同一列或同一斜线上的棋子。
//N皇后问题等价于在n×n格的棋盘上放置n个皇后，任何2个皇后不放在同一行或同一列或同一斜线上。
namespace Huanghou
{
const int N = 8;
//用来表示棋盘，0表示没有皇后，1表示有皇后
int Board[N][N] = {{0}};
//方法的数量
int way = 0;
//判断皇后放到这个位置是否可以，即同一行，同一列，对应的斜线上是否已经放了皇后
bool isConflict(int m,int n)
{
    if(m>N || n>N || n<0||m<0) return false;

    //判断当前位置是否有皇后
    if(Board[m][n] == 1) return false;

    //判断行和列是否有皇后
    for(int i=0;i<N;++i)
    {
        if(Board[i][n] == 1 || Board[m][i] == 1) return false;
    }

    //判断斜线上是否有皇后
    for(int i=1;i<N;++i)
    {
        //左上角
        if((m-i)>=0&&(n-i)>=0) //判断位置合法
        {
            if(Board[m-i][n-i]==1)
            {
                return false;
            }
        }
        //右上角
        if((m-i)>=0&&(n+i)<N)
        {
            if(Board[m-i][n+i] == 1)
            {
                return false;
            }
        }
        //左下角
        if((m+i)<N&&(n-i)>=0)
        {
            if(Board[m+i][n-i] == 1)
            {
                return false;
            }
        }
        //右下角
        if((m+i)<N&&(n+i)<N)
        {
            if(Board[m+i][n+i] == 1)
            {
                return false;
            }
        }
    }
    return true;
}

void huanghou(int t)
{
    if(t>N)
    {
        way++;
    }
    else
    {
        for(int i=0;i<N;++i)
        {
            for(int j=0;j<N;++j)
            {
                if(isConflict(i,j))
                {
                    Board[i][j] = 1;
                    huanghou(t+1);
                    Board[i][j] = 0;
                }
            }
        }
    }
}
//阶乘
int jiecheng(int n)
{
    int result = 1;
    for(int i=1;i<=n;++i)
    {
        result *= i;
    }
    return result;
}


//另一种解法：由于性质可了解到每一行只能有一个皇后,因此可以放每一个皇后的时候只遍历当前行即可
void new_huanghou(int t)
{
    if(t>N-1)
    {
        way++;
        return;
    }
    for(int i=0;i<N;i++)
    {
        //因为是一行一行的放，只需要判断前面的行是否有冲突的即可，即前面的行，左上角，右上角
        if(isConflict(t,i))
        {
            Board[t][i] = 1;
            new_huanghou(t+1);
            Board[t][i] = 0;
        }
    }
}

//用一个一维数组来存放每一行皇后的位置
int a[N];
bool isRight(int m,int n)
{
    //判断对角线相等用行的差的绝对值等于列的差的绝对值说明在同一个斜线
    for(int i=0;i<m;++i)
    {
        if(a[i]==n||abs(m-i)==abs(n-a[i]))return false;
    }
    return true;
}

void one_huanghou(int t)
{
    if(t>N-1)
    {
        way++;
        return ;
    }
    for(int i=0;i<N;++i)
    {
        if(isRight(t,i))
        {
            a[t] = i;
            one_huanghou(t+1);
            a[t] = -1;
        }
    }
}

//运行八皇后的函数
void run_huanghou()
{
    for(int i=0;i<N;++i)
    {
        a[i] = -1;
        for(int j=0;j<N;++j)
            Board[i][j] = 0;
    }
    time_t beg = time(NULL);
    way = 0;
//    huanghou(1);//这个要用120
//    new_huanghou(0); //这个一秒都不到
    one_huanghou(0);
    time_t end = time(NULL);

    cout<<"way:"<<way<<" time:"<<end-beg<<endl;
    cout<<"way:"<<way/jiecheng(N)<<" time:"<<end-beg<<endl;
}
}

namespace Lujing
{
//请设计一个函数，用来判断在一个矩阵中是否存在一条包含某字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则之后不能再次进入这个格子。 例如 a b c e s f c s a d e e 这样的3 X 4 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。

bool one_has(char* matrix,int M,int N,char* str,int m,int n,vector<vector<int> >& a,int x)
{
    if(str[x] == '\0') return true;
    if(m>M-1 || n>N-1||m<0||n<0) return false; //不合法
    if(a[m][n] == 1) return false;
    if(matrix[m*N+n] != str[x]) return false;

    bool flag = false;
    a[m][n] = 1;
    //向左走
    if(!flag) 
    {
        flag = one_has(matrix,M,N,str,m,n-1,a,x+1);
    }
    //向右走
    if(!flag) 
    {
        flag = one_has(matrix,M,N,str,m,n+1,a,x+1);
    }
    //向上走
    if(!flag) 
    {
        flag = one_has(matrix,M,N,str,m-1,n,a,x+1);
    }
    //向下走
    if(!flag) 
    {
        flag = one_has(matrix,M,N,str,m+1,n,a,x+1);
    }

    a[m][n] = 0;
    return flag;
}
//回溯法解决，从任意一个点可以开始，然后分别向上下左右四个点走，判断是否匹配
bool hasPath(char* matrix, int rows, int cols, char* str)
{
    //初始化一个数组来表示这个点是否被访问过
    vector<vector<int> > a(rows,vector<int>(cols,0));
    bool flag = false;
    for(int i=0;i<rows;++i)
    {
        for(int j=0;j<cols;++j)
        {
            flag = one_has(matrix,rows,cols,str,i,j,a,0);
            if(flag)
            {
                return true;
            }
        }
    }
    return flag;
}
}
class RobotMove{
//地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？
public:
    bool isRight(int t,int x,int y)
    {
        int res = 0;
        while(x)
        {
            res += x%10;
            x /= 10;
        }
        while(y)
        {
            res += y%10;
            y /= 10;
        }

        return res>t?false:true;
    }
    bool move(int threshold,int M,int N,vector<int>& isOk,int& count,int m,int n)
    {
        if(m>M||m<0||n>N||n<0) return false;
        if(isOk[m*N+n]) return false;
        if(!isRight(threshold,m,n)) return false;

        isOk[m*N+n] = 1;
        count++;
        move(threshold,M,N,isOk,count,m-1,n);
        move(threshold,M,N,isOk,count,m+1,n);
        move(threshold,M,N,isOk,count,m,n+1);
        move(threshold,M,N,isOk,count,m,n-1);
        return true;
    }
    int movingCount(int threshold, int rows, int cols)
    {
        //用来表示是否已经走过这个点
        vector<int> isOk(rows*cols,0);
        int count = 0;
        move(threshold,rows,cols,isOk,count,0,0);
        return count;
    }
};

class Test
{
public:
    int a = 0;
    void print_test()
    {
        cout<<__FUNCTION__<<endl;
        cout<<__func__<<endl;
    }
};

#include <thread>
void threadfun1()
{
    std::cout << "threadfun1 - 1\r\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "threadfun1 - 2" << std::endl;
}

void threadfun2(int iParam, std::string sParam)
{
    std::cout << "threadfun2 - 1" << std::endl;
    cout<<"threadfun2 -1:"<<iParam<<","<<sParam<<endl;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << "threadfun2 - 2" << std::endl;
}

int test_thread()
{
    std::thread t1(threadfun1);
    std::thread t2(threadfun2, 10, "abc");
    t1.join();
    std::cout << "join" << std::endl;
    t2.detach();
    std::cout << "detach" << std::endl;
    return 0;
}

class FindCount {
    //统计一个数字在排序数组中出现的次数。
    //这个因为都是整数，可以换一个角度分别找k-0.5和k+0.5 ，这样就能找到第一个k和第一个大于k的数的下标
public:
    int midSearch(vector<int> &data,double f)
    {
        int beg = 0;
        int end = data.size()-1;
        while(beg <= end)
        {
            int mid = (end+beg)/2;
            if(data[mid]<f)
            {
                beg = mid+1;
            }
            else if(data[mid] > f)
            {
                end = mid-1;
            }
            
        }
        return beg;
    }
    int GetNumberOfK(vector<int> data ,int k) {
        if(data.size()==0) return 0;
        int beg = midSearch(data,k-0.5);
        int end = midSearch(data,k+0.5);
        cout<<beg<<","<<end<<endl;
        return end-beg;
    }
};

class FindMid {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int len1 = nums1.size();
        int len2 = nums2.size();
        vector<int> num3;
        for(int i=0,j=0;i<len1||j<len2;)
        {
            if((i>=len1&&j<len2)||nums1[i]>nums2[j])
            {
                num3.push_back(nums2[j]);
                j++;
            }
            else if((j>=len2&&i<len1) || nums1[i]<=nums2[j])
            {
                num3.push_back(nums1[i]);
                i++;
            }
            
        }
        double result = 0;
        if((len1+len2)%2==0)
        {
            result =  (num3[(len1+len2)/2]+num3[(len1+len2)/2-1])/2;
        }
        else
        {
            result =  num3[(len1+len2)/2];
        }
        return result;
    }
};

class TestF
{
    public:
    int a = 1;
    virtual void print()
    {
        cout <<a<<","<<b<<endl;
    }
    void test()
    {
        cout<<"testf"<<endl;
    }
    private:
    //子类果然无法访问父类的私有成员
    int b = 2;
};
class TestC:public TestF
{
    public:
    void print1()
    {
        cout<<"test:"<<a<<","<<endl;
    }
    void test()
    {
        cout<<"testc"<<endl;
    }
};

int main()
{
//    vector<int> x = {3,4,1,5,2,29,4,33,2};
//    Huanghou::run_huanghou();
//    Test t;
//    t.print_test();
//    test_thread();
//    FindCount f;
//    vector<int> a{3};
//    int k = 3;
//    f.GetNumberOfK(a,k);
//    vector<int> a{1,3};
//    vector<int> b{2};
//    FindMid f;
//    cout<<f.findMedianSortedArrays(a,b);
    TestF *f = new TestC;
    f->print();
    f->test();
}
