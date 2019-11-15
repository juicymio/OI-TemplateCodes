#include<cstdio>
const int MAXN = 500000+10;
int A[MAXN];
int T[MAXN];
// long long cnt = 0;
void merge_sort(int l,int r)
{
    if(r - l > 1)
    {
        int mid = l + (r - l) / 2;
        int x = l,y = mid,i = l;
        merge_sort(l,mid);
        merge_sort(mid,r);
        while(x < mid || y < r)
        {
            if(y >= r || (x < mid && A[x] < A[y]))
            {
                T[i ++] = A[x ++];
            }
            else
            {
                T[i ++] = A[y ++];
                //cnt += mid - x;
            }
        }
        for(int i = l;i < r;i ++)
        {
            A[i] = T[i];
        }
    }
}
int main()
{
    freopen("m.in","r",stdin);
    freopen("m.out","w",stdout);
    int n;
    scanf("%d",&n);
    for(int i = 0;i < n;i ++)
    {
        scanf("%d",&A[i]);
    }
    merge_sort(0,n);
    for(int i = 0;i < n;i ++)
    {
        printf("%d ",A[i]);
    }
    return 0;
}
