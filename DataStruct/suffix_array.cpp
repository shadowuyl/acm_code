const int maxn=1e5+5;
int t1[maxn],t2[maxn],c[maxn];
int sa[maxn],rankth[maxn],height[maxn];
//rankth(1~n) 下标从1开始，sa(0~n-1)下标从0开始，height下标从2开始(height[i]表示第i大的后缀和第i-1大的后缀的lcp)
void build_sa(int s[],int n,int m)
{
    memset(height,0,sizeof(height));
    memset(rankth,0,sizeof(rankth));
    memset(sa,0,sizeof(sa));
	memset(c,0,sizeof(c));
    int i,j,p,*x=t1,*y=t2;
    for(i=0;i<m;i++)c[i]=0;
    for(i=0;i<n;i++)c[x[i]=s[i]]++;
    for(i=1;i<m;i++)c[i]+=c[i-1];
    for(i=n-1;i>=0;i--)sa[--c[x[i]]]=i;
    for(j=1;j<=n;j<<=1)
    {
        p=0;
        for(i=n-j;i<n;i++)y[p++]=i;
        for(i=0;i<n;i++)if(sa[i]>=j)y[p++]=sa[i]-j;
        for(i=0;i<m;i++)c[i]=0;
        for(i=0;i<n;i++)c[x[y[i]]]++;
        for(i=1;i<m;i++)c[i]+=c[i-1];
        for(i=n-1;i>=0;i--)sa[--c[x[y[i]]]]=y[i];
        swap(x,y);
        p=1;x[sa[0]]=0;
        for(i=1;i<n;i++)
            x[sa[i]]=y[sa[i-1]]==y[sa[i]]&&y[sa[i-1]+j]==y[sa[i]+j]?p-1:p++;
        if(p>=n)break;
        m=p;
    }
}
void getHeight(int s[],int n)
{
    int i,j,k=0;
    for(i=0;i<=n;i++)rankth[sa[i]]=i;
    for(i=0;i<n;i++)
    {
        if(k)k--;
        j=sa[rankth[i]-1];
        while(s[i+k]==s[j+k])k++;
        height[rankth[i]]=k;
    }
}
int loglen[maxn],multip[20][maxn];
void initRMQ(int n)
{
    loglen[0]=-1;
    for(int i=1;i<=n;i++)
        loglen[i]=((i&(i-1))==0)?loglen[i-1]+1:loglen[i-1];
    for(int i=1;i<=n;i++)multip[0][i]=i;
    for(int i=1;i<=loglen[n];i++)
        for(int j=1;j+(1<<i)-1<=n;j++)
        {
            int a=multip[i-1][j];
            int b=multip[i-1][j+(1<<(i-1))];
            if(height[a]<height[b])multip[i][j]=a;
            else multip[i][j]=b;
        }
}
int askRMQ(int a,int b)
{
    int t;
    t=loglen[b-a+1];
    b-=(1<<t)-1;
    a=multip[t][a];b=multip[t][b];
    return height[a]<height[b]?a:b;
}
int lcp(int a,int b)
{
    a=rankth[a];b=rankth[b];
    if(a>b)swap(a,b);
    return height[askRMQ(a+1,b)];
}
char str[maxn];
int num[maxn];
//num(0~n-1)
int main(){
    cin>>str;int n=strlen(str);int valmax=0;
    for(int i=0;i<=n;++i){num[i]=str[i];valmax=max(valmax,num[i]);}
    build_sa(num,n+1,valmax+5);
    getHeight(num,n);
    initRMQ(n);
}
