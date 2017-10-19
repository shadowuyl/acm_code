//单个欧拉函数
llong euler(llong x)
{
    llong res = x;
    for(int i = 2; i*i <= x; i++){
        if(x % i == 0){
            res -= res/i;
            while(x % i == 0)x /= i;
        }
    }
    if(x > 1)res -= res/x;
    return res;
}

// (x^y)%z
llong pow_mod(llong x,llong y,llong z){
    llong tmp=x,res=1;
    while(y>0){
        if(y&1)res=(res*tmp)%z;
        tmp=(tmp*tmp)%z;
        y=y/2;
    }
    return res%z;
}


//not tested
// O(N) 预处理质数
//MyCode
vector<int>Prime;
bool vis[maxn];
void getPrime()
{
    memset(vis,0,sizeof(vis));
    int n=1299709;
    int m=sqrt(m+0.5);
    for(int i=2;i<=m;++i){
        if(!vis[i]){
            Prime.push_back(i);
            for(int j=i*i;j<=n;j+=i)vis[j]=1;
        }
    }
}

//哈尔滨
vector <int> prime;
bool is_prime[MAXN];
void prime_table(){
    for(int i = 0; i < MAXN; i ++) is_prime[i] = true;
    for(int i = 2 ; i < MAXN; i ++){
        if(is_prime[i]) prime.pb(i);
        for(int j = 0; j < prime.size() && i * prime[j] < MAXN; j ++){
            is_prime[i * prime[j]] = false;
            if(i % prime[j] == 0) break;
        }
    }
}

// 快速幂

#define llong long long

llong pow_mod(llong x, llong y, llong z) {
    llong res = 1;
    while(y) {
       if(y & 1) res *= x, res %= z;
       x *= x, x %= z, y >>= 1;
    }
    return res % z;
}

// 扩展欧几里得

void ext_gcd(llong a, llong b, llong &d, llong &x, llong &y) {
     if(!b) {d = a, x = 1, y = 0;}
     else {ext_gcd(b, a % b, d, y, x), y -= x * (a / b);}
}

// 用扩展欧几里得求逆元

llong inv(llong a, llong c) {
    llong d, x, y;
    ext_gcd(a, c, d, x, y);
    return (x + c) % c;
}

//线性同余方程组
    int k;
    while(scanf("%d",&k)!=EOF){
        llong a1,a2,r1,r2;
        int fg=0;
        scanf("%llongd%llongd",&a1,&r1);
        for(int i=1;i<k;i++){
            scanf("%llongd%llongd",&a2,&r2);
            llong d,x1,x2;
            llong c=r2-r1;
            ext_gcd(a1,a2,d,x1,x2);
            if(c%d!=0){
                fg=1;
            }
            llong t=a2/d;
            x1=(x1*(c/d)%t+t)%t;//注意
            r1=a1*x1+r1;
            a1=a1*(a2/d);
        }
        if(fg)printf("-1\n");
        else printf("%llongd\n",r1);
    }
