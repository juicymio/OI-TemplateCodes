#include<cstdio>
const int MAXN = 50000+10;
int tree[MAXN];
int n;
int lowbit(int x)
{
    return x & -x;
}
void add(int i,int x)
{
    while(i < n)
    {
        tree[i] += x;
        i += lowbit(i);
    }
    return;
}
int sum(int i)
{
    int ans = 0;
    while(i >= 0)
    {
        ans += tree[i];
        i -= lowbit(i);
    }
    return ans;
}//支持单点修改区间查询或区间修改单点查询(差分)
