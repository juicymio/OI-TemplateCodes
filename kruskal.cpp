#include<cstdio>
#include<cstring>
#include<algorithm>

struct edge
{
    int u,v,w;
};
bool cmp(edge a,edge b)
{
    return a.w < b.w;
}
edge e[100000+10];
int fa[300+10];
int find(int x)
{
    if(fa[x] != x)
        fa[x] = find(fa[x]);
    return fa[x];
}
void unionSet(int x,int y)
{
    x = find(x),y = find(y);
    if(x != y)
        fa[x] = y;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i = 0;i < m;i ++)
    {
        scanf("%d%d%d",&e[i].u,&e[i].v,&e[i].w);
    }
    for(int i = 0;i <= n;i ++)
        fa[i] = i;
    std::sort(e,e+m,cmp);
    int cnt = 0,maxw = 0;
    for(int i = 0;i < m;i ++)
    {
        if(find(e[i].u) != find(e[i].v))
        {
            cnt ++;
            unionSet(e[i].u,e[i].v);
        }
        if(cnt == n - 1)
        {
            maxw = e[i].w;
            break;
        }
    }
    printf("%d %d",cnt,maxw);
    return 0;
}