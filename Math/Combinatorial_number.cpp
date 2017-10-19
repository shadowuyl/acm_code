// 组合数公式：C(n,k)=n!/(k!*(n-k)!),n<=1e4
#define mod 1000000007
#define maxn 1011
#define llong long long
using namespace std;
llong c[maxn][maxn];
void init(int n){
    c[0][0]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++)
            c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod;
}

// n<=1e9,k<=1e6，适用于少量组合数计算
#define mod 1000000007
llong mul(llong x,llong y,llong z){return (x*y-(llong )(x/(long double)z*y+1e-3)*z+z)%z;}
llong pow_mod(llong a,llong b,llong M) {llong res=1;a%=M;for(;b;b>>=1){if(b&1)res=mul(res,a,M);a=mul(a,a,M);}return res;}
llong C(llong n,llong k){
    llong i,ans=1,t=1;
    for(i=1;i<=k;i++){
        ans=ans*(n-i+1)%mod;
        t=t*i%mod;
    }
    return ans*pow_mod(t,mod-2,mod)%mod;
}

// n<=1e9,k<=1e6，适用于较多量组合数计算
#define maxx 111111
#define mod 1000000007
llong inv[maxx];
void ni(int n){
    inv[1]=1;
    for(int i=2;i<=n;i++) inv[i]=(mod-mod/i*inv[mod%i]%mod)%mod;
}
llong C(llong n,llong k){
    llong ans=1;
    for(llong i=1;i<=k;i++)
        ans=ans*((n-i+1)%mod)%mod*inv[i]%mod;
    return ans;
}

// n<=1e6,适合少量组合数计算
#define mod 1000000007
#define maxx 111111
llong f[maxx]={1};
llong mul(llong x,llong y,llong z){return (x*y-(llong )(x/(long double)z*y+1e-3)*z+z)%z;}
llong pow_mod(llong a,llong b,llong M) {llong res=1;a%=M;for(;b;b>>=1){if(b&1)res=mul(res,a,M);a=mul(a,a,M);}return res;} 
void init(int n){
    for(int i=1;i<=n;i++) f[i]=f[i-1]*i%mod; 
}
llong C(llong n,llong k){
    return f[n]*pow_mod(f[k],mod-2,mod)%mod*pow_mod(f[n-k],mod-2,mod)%mod;
}

// n<=1e6,适合少量组合数计算
#define mod 1000000007
#define maxx 111111
llong f[maxx]={1},inv[maxx];
llong mul(llong x,llong y,llong z){return (x*y-(llong )(x/(long double)z*y+1e-3)*z+z)%z;}
llong pow_mod(llong a,llong b,llong M) {llong res=1;a%=M;for(;b;b>>=1){if(b&1)res=mul(res,a,M);a=mul(a,a,M);}return res;} 
void init(int n){
    for(int i=1;i<=n;i++) f[i]=f[i-1]*i%mod;
    for(int i=0;i<=n;i++) inv[i]=pow_mod(f[i],mod-2,mod); 
}
llong C(llong n,llong k){
    return f[n]*inv[n-k]%mod*inv[k]%mod;
}

// n,m<=1e18,mod<=1e5,并且是素数。使用Lucas定理。
llong pow_mod(llong a,llong b,llong M) {llong res=1;a%=M;for(;b;b>>=1){if(b&1)res=res*a%M;a=a*a%M;}return res;}
llong C(llong n,llong k,llong mod){
    llong i,ans=1,t=1;
    if(k>n) return 0;
    for(i=1;i<=k;i++){
        ans=ans*(n-i+1)%mod;
        t=t*i%mod;
    }
    return ans*pow_mod(t,mod-2,mod)%mod;
}
llong Lucas(llong n,llong m,llong p){
    if(m==0) return 1;
    return C(n%p,m%p,p)*Lucas(n/p,m/p,p)%p;
}

// n,m<=1e18,mod<=1e18,mod为若干个互不相同的质数的乘积且pi<=1e5使用Lucas定理+中国剩余定理
inline llong mul(llong x,llong y,llong z){return (x*y-(llong )(x/(long double)z*y+1e-3)*z+z)%z;}
llong pow_mod(llong a,llong b,llong M) {llong res=1;a%=M;for(;b;b>>=1){if(b&1)res=res*a%M;a=a*a%M;}return res;}
llong C(llong n,llong k,llong mod){
    llong i,ans=1,t=1;
    if(k>n) return 0;
    for(i=1;i<=k;i++){
        ans=ans*(n-i+1)%mod;
        t=t*i%mod;
    }
    return ans*pow_mod(t,mod-2,mod)%mod;
}
llong Lucas(llong n,llong m,llong p){
    if(m==0) return 1;
    return C(n%p,m%p,p)*Lucas(n/p,m/p,p)%p;
}
llong Extended_Euclid(llong a,llong b,llong  &x,llong  &y)
{
    llong d;
    if(b==0)
    {
        x=1;y=0;
        return a;
    }
    d=Extended_Euclid(b,a%b,y,x);
    y-=a/b*x;
    return d;
}
llong Chinese_Remainder(llong a[],llong w[],llong len)
{
    llong i,d,x,y,m,n,ret;
    ret=0;
    n=1;
    for(i=0;i<len;i++) n*=w[i];
    for(i=0;i<len;i++)
    {
        m=n/w[i];
        d=Extended_Euclid(w[i],m,x,y);
        ret=(ret+mul(mul(y,m,n),a[i],n))%n;
    }
    return (n+ret%n)%n;
}
llong gao(llong n,llong m,llong k){
    for(llong i=0;i<k;i++)
        t[i]=Lucas(n,m,p[i]);
    return Chinese_Remainder(t,p,k);
}





