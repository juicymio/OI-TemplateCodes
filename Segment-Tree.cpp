#include<cstdio>
#include<cmath>
#include<algorithm>

const int INF = 1e9+7;
const int N = 100000;
int MOD;
int a[N];
long long read()
{
    char c;
    long long f = 1;
    long long ans = 0;
    do
    {
        c = getchar();
        if(c == '-')
            f = -1;
    } while (c < '0' || c > '9');
    do
    {
        ans = (ans << 3) + (ans << 1) + c - '0';
        c = getchar();
    } while (c >= '0' && c <= '9');
    return f * ans;
}

/*one lazy tag
struct segmentTree
{
#define lson (o << 1)
#define rson (o << 1 | 1)
    long long sumv[N<<2];
    long long addv[N<<2];
    int left[N<<2],right[N<<2];
    long long minv[N*4];
    inline void pushup(int o)
    {
        //minv[o] = std::min(minv[lson],minv[rson]);
        sumv[o] = sumv[lson] + sumv[rson];
    }
    inline void pushdown(int o)
    {
        if(!addv[o])
            return;
        addv[lson] += addv[o];
        addv[rson] += addv[o];
        sumv[lson] += (right[lson] - left[lson] + 1) * addv[o];
        sumv[rson] += (right[rson] - left[rson] + 1) * addv[o];
        addv[o] = 0;
    }
    inline void build(int o,int l,int r)
    {
        addv[o] = 0;
        left[o] = l,right[o] = r;
        if(l == r)
        {
            sumv[o] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lson,l,mid);
        build(rson,mid+1,r);
        pushup(o);
    }
    inline void optadd(int o,int l,int r,int ql,int qr,int v)
    {
        if(ql <= l && qr >= r)
        {
            addv[o] += v;
            sumv[o] += (right[o]-left[o]+1)*v;
            return;
        }
        int mid = (l+r) >> 1;
        pushdown(o);
        if(ql <= mid)
            optadd(lson,l,mid,ql,qr,v);
        if(qr > mid)
            optadd(rson,mid+1,r,ql,qr,v);
        pushup(o);
    }
    inline long long querysum(int o,int l,int r,int ql,int qr)
    {
        if(ql <= l && qr >= r)
        {
            return sumv[o];
        }
        int mid = (l+r) >> 1;
        pushdown(o);
        long long ans = 0;
        if(ql <= mid)
        {
            ans += querysum(lson,l,mid,ql,qr); 
        }
        if(qr > mid)
        {
            ans += querysum(rson,mid+1,r,ql,qr);
        }
        return ans;
    }
    inline int querymin(int o,int l,int r,int ql,int qr)
    {
        if(ql <= l && qr >= r)
        {
            return minv[o];
        }
        int mid = (l + r) >> 1,ans = INF;
        if(ql <= mid)
        {
            ans = std::min(ans,querymin(lson,l,mid,ql,qr));
        }
        if(qr > mid)
        {
            ans = std::min(ans,querymin(rson,mid+1,r,ql,qr));
        }
        return ans;
    }
    
};
*/

/* two lazy tag*/
struct segmentTree
{
#define lson (o << 1)
#define rson (o << 1 | 1)
    long long mulv[N<<2];
    long long sumv[N<<2];
    long long addv[N<<2];
    int left[N<<2],right[N<<2];
    //long long minv[N*4];
    inline void pushup(int o)
    {
        //minv[o] = std::min(minv[lson],minv[rson]);
        sumv[o] = (sumv[lson] + sumv[rson]) % MOD;
    }
    inline void pushdown(int o)
    {
        if(!addv[o] && mulv[o] == 1)
            return;
        mulv[lson] = (mulv[lson]*mulv[o])%MOD;
        mulv[rson] = (mulv[rson]*mulv[o])%MOD;
        addv[lson] = (addv[lson]*mulv[o]+addv[o])%MOD;
        addv[rson] = (addv[rson]*mulv[o]+addv[o])%MOD;
        sumv[lson] = (sumv[lson]*mulv[o]+addv[o]*(right[lson]-left[lson]+1))%MOD;
        sumv[rson] = (sumv[rson]*mulv[o]+addv[o]*(right[rson]-left[rson]+1))%MOD;
        addv[o] = 0;
        mulv[o] = 1;
    }
    inline void build(int o,int l,int r)
    {
        addv[o] = 0,mulv[o] = 1;
        left[o] = l,right[o] = r;
        if(l == r)
        {
            sumv[o] = a[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lson,l,mid);
        build(rson,mid+1,r);
        pushup(o);
    }
    inline void optadd(int o,int l,int r,int ql,int qr,int v)
    {
        if(ql <= l && qr >= r)
        {
            addv[o] += v;
            sumv[o] += (right[o]-left[o]+1)*v;
            addv[o] = addv[o] % MOD;
            sumv[o] = sumv[o] % MOD;
            return;
        }
        int mid = (l+r) >> 1;
        pushdown(o);
        if(ql <= mid)
            optadd(lson,l,mid,ql,qr,v);
        if(qr > mid)
            optadd(rson,mid+1,r,ql,qr,v);
        pushup(o);
    }
    inline void optmul(int o,int l,int r,int ql,int qr,int v)
    {
        if(ql <= l && qr >= r)
        {
            mulv[o] *= v;
            mulv[o] = mulv[o] % MOD;
            addv[o] *= v;
            addv[o] = addv[o] % MOD;
            sumv[o] *= v;
            sumv[o] = sumv[o] % MOD;
            return;
        }
        pushdown(o);
        int mid = (l+r) >> 1;
        if(ql <= mid)
            optmul(lson,l,mid,ql,qr,v);
        if(qr > mid)
            optmul(rson,mid+1,r,ql,qr,v);
        pushup(o);
    }
    inline long long querysum(int o,int l,int r,int ql,int qr)
    {
        if(ql <= l && qr >= r)
        {
            return sumv[o];
        }
        int mid = (l+r) >> 1;
        pushdown(o);
        long long ans = 0;
        if(ql <= mid)
        {
            ans = (ans + querysum(lson,l,mid,ql,qr)) % MOD; 
        }
        if(qr > mid)
        {
            ans = (ans + querysum(rson,mid+1,r,ql,qr)) % MOD;
        }
        return ans % MOD;
    }
};
segmentTree st;
int main()
{
    int n,m;
    n = read(),m = read(),MOD = read();
    //printf("%d %d",n,m);
    for(int i = 1;i <= n;i ++)
    {
        a[i] = read();
        //printf("%d ",a[i]);
    }
    st.build(1,1,n);
    for(int i = 1;i <= m;i ++)
    {
        int opt = read();
        if(opt == 1)
        {
            int x = read(),y = read();
            long long k = read();
            st.optmul(1,1,n,x,y,k);
        }
        else if(opt == 2)
        {
            int x = read(),y = read();
            long long k = read();
            st.optadd(1,1,n,x,y,k);
        }
        else if(opt == 3)
        {
            int x = read(),y = read();
            long long ans = st.querysum(1,1,n,x,y);
            printf("%lld\n",ans);
        }
    }
    return 0;
}