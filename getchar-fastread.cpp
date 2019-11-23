#include<cstdio>
int read()
{
    char c;
    int f = 1;
    int ans = 0;
    do
    {
        c = getchar();
        if(c == '-')
            f = -1;
    }
    while(c < '0' || c > '9');
    do
    {
        ans = ans * 10 + c - '0';
        c = getchar();
    }
    while(c >= '0' && c <= '9');
    return f*ans;
}
int main()
{
    freopen("f.out","w",stdout);
    int n;
    n = read();
    printf("%d",n);
    return 0;
}
