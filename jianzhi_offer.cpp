//这里面放剑指offer和leetcode里面的题
//里面题目描述，解题思路，代码
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;

//1.二维数组中的查找
/*
*在一个二维数组中（每个一维数组的长度相同），每一行都按照从左到右递增的顺序排序，每一列都按照从上到下递增的顺序排序。请完成一个函数，输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
解题思路：从左上角或者右下角开始每次排除一行或者一列，比如左上角的值为x，t大于x则排除这一行，t小于x则排除这一列，以此类推
 */
class offer1DoubleArray
{
    public:
    bool Find(int target,vector<vector<int> > array)
    {
        if(array.size() == 0)return false;
        int m = array.size();
        int n = array[0].size();
        int i = 0;
        int j = n - 1;
        while(i<m&&j>=0)
        {
            int x = array[i][j];
            if(target > x)
            {
                i++;
            }
            if(target < x)
            {
                j--;
            }
            else
            {
                return true;
            }
        }
        return false;
    }
};
/*
1.替换空格
请实现一个函数，将一个字符串中的每个空格替换成“%20”。例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy。
解题思路：从前面开始替换的话需要移动的太多，因此从后面开始替换，先遍历求出空格的数量，然后算出替换后的字符串长度，从后面开始替换即可
 */
class offer1ReplaceSpace
{
    public:
    void replaceSpace(char *str,int length)
    {
        int count = 0;
        int len = 0;
        char* p = str;
        while(*p != '\0')
        {
            if(*p==' ')
            {
                count++;
            }
            p++;
            len++;
        }
        int new_len = len+ count*2;
        if(new_len > length) return;
        while(len >= 0)
        {
            if(str[len] == ' ')
            {
                str[new_len--] = '0';
                str[new_len--] = '2';
                str[new_len--] = '%';
            }
            else
            {
                str[new_len--] = str[len];
            }
            len--;
        }
    }
};

 struct ListNode 
 {
    int val;
    struct ListNode *next;
    ListNode(int x) :
            val(x), next(NULL) {}
};
/*
3.从尾到头打印链表
输入一个链表，按链表值从尾到头的顺序返回一个ArrayList。
解题思路：链表反转，用一个临时变量，或者用栈，再或者用递归
 */
class offer3FanZhuan
{
    public:
    vector<int> printListFromTailToHead(ListNode* head)
    {
        vector<int> result;
        if(head == NULL) return result;
        ListNode *p = NULL;
        ListNode *n = head;
        while(n->next)
        {
            ListNode* tmp = n->next;
            n->next = p;
            p = n;
            n = tmp;
        }
        n->next = p;
        p = n;
        while(p)
        {
            result.push_back(p->val);
            p = p->next;
        }
        return result;
    }
};

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
/*
4.重建二叉树
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。假设输入的前序遍历和中序遍历的结果中都不含重复的数字。例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回。
解题思路：这个问题涉及到二叉树的前序和中序遍历的特点，前序遍历，第一个肯定是根节点，中序遍历则跟节点在中间，前：根|所有左|所有右，中序遍历：所有左|根|所有右，用这个特点，先从前序找到跟节点，然后从中序遍历找到左边所有的数，和右边所有的数，然后左边是一个子树，右边是另一个子树，递归创建即可
 */
class offer4RebuildTree{
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.size()==0||vin.size()==0)return NULL;
        int val = pre[0];
        TreeNode* head = new TreeNode(val);
        int left_count = 0;
        for(int i=0;i<vin.size();++i)
        {
            if(vin[i] == val)
            {
                left_count = i;
                break;
            }
        }
        vector<int> left_pre;
        vector<int> left_vin;
        vector<int> right_pre;
        vector<int> right_vin;
        for(int i=0;i<left_count;++i)
        {
            left_pre.push_back(pre[i+1]);
            left_vin.push_back(vin[i]);
        }
        for(int i=left_count;i<vin.size();++i)
        {
            right_vin.push_back(vin[i]);
            right_pre.push_back(pre[i]);
        }
        head->left = reConstructBinaryTree(left_pre,left_vin);
        head->right = reConstructBinaryTree(right_pre,right_vin);
        return head;
    }
};