#include<cstdio>
#include<vector>
#include<queue>
#include<cstring>


const int MAXN = 100000+10;
struct node
{
    int u,d;
    bool operator<(const node& rhs)const
    {
        return d > rhs.d;
    }
    node(int u,int d):u(u),d(d){};
};
struct edge
{
    int v,w;
    edge(int v,int w):v(v),w(w){};
};
int n,m,s;
std::vector<edge> G[MAXN];
int dis[MAXN];
void addEdge(int u,int v,int w)
{
    G[u].push_back(edge(v,w));
}
void dijkstra()
{
    std::priority_queue<node> Q;
    memset(dis,0x3f,sizeof(dis));
    dis[s] = 0;
    node cur(s,dis[s]);
    Q.push(cur);
    while(!Q.empty())
    {
        cur = Q.top();
        Q.pop();
        int& u = cur.u;
        int& d = cur.d;
        if(d != dis[u])
            continue;
        for(int i = 0;i < (int)G[u].size();i ++)
        {
            int& v = G[u][i].v;
            int& w = G[u][i].w;
            if(dis[v] > dis[u] + w)
            {
                dis[v] = dis[u] + w;
                Q.push(node(v,dis[v]));
            }
        }
    }
    
}
int main()
{
    scanf("%d%d%d",&n,&m,&s);
    for(int i = 0;i < m;i ++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        addEdge(u,v,w);
    }
    dijkstra();
    for(int i = 1;i <= n;i ++)
    {
        if(dis[i] < 0x3f3f3f3f)
            printf("%d\n",dis[i]);
        else
            printf("Cannot reach.\n");
    }
    return 0;
}
