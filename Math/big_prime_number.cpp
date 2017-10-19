// Miller_Rabin 算法进行素数测试
//速度快，而且可以判断 <2^63的数
//****************************************************************
const int S=20;//随机算法判定次数，S越大，判错概率越小


//计算 (a*b)%c.   a,b都是long long的数，直接相乘可能溢出的
//  a,b,c <2^63
llong mult_mod(llong a,llong b,llong c)
{
    a%=c;
    b%=c;
    llong ret=0;
    while(b)
    {
        if(b&1){ret+=a;ret%=c;}
        a<<=1;
        if(a>=c)a%=c;
        b>>=1;
    }
    return ret;
}



//计算  x^n %c
llong pow_mod(llong x,llong n,llong mod)//x^n%c
{
    if(n==1)return x%mod;
    x%=mod;
    llong tmp=x;
    llong ret=1;
    while(n)
    {
        if(n&1) ret=mult_mod(ret,tmp,mod);
        tmp=mult_mod(tmp,tmp,mod);
        n>>=1;
    }
    return ret;
}





//以a为基,n-1=x*2^t      a^(n-1)=1(mod n)  验证n是不是合数
//一定是合数返回true,不一定返回false
bool check(llong a,llong n,llong x,llong t)
{
    llong ret=pow_mod(a,x,n);
    llong last=ret;
    for(int i=1;i<=t;i++)
    {
        ret=mult_mod(ret,ret,n);
        if(ret==1&&last!=1&&last!=n-1) return true;//合数
        last=ret;
    }
    if(ret!=1) return true;
    return false;
}

// Miller_Rabin()算法素数判定
//是素数返回true.(可能是伪素数，但概率极小)
//合数返回false;

bool Miller_Rabin(llong n)
{
    if(n<2)return false;
    if(n==2)return true;
    if((n&1)==0) return false;//偶数
    llong x=n-1;
    llong t=0;
    while((x&1)==0){x>>=1;t++;}
    for(int i=0;i<S;i++)
    {
        llong a=rand()%(n-1)+1;//rand()需要stdlib.h头文件
        if(check(a,n,x,t))
            return false;//合数
    }
    return true;
}


//************************************************
//pollard_rho 算法进行质因数分解
//************************************************
llong factor[100];//质因数分解结果（刚返回时是无序的）
int tol;//质因数的个数。数组小标从0开始

llong gcd(llong a,llong b)
{
    if(a==0)return 1;//???????
    if(a<0) return gcd(-a,b);
    while(b)
    {
        llong t=a%b;
        a=b;
        b=t;
    }
    return a;
}

llong Pollard_rho(llong x,llong c)
{
    llong i=1,k=2;
    llong x0=rand()%x;
    llong y=x0;
    while(1)
    {
        i++;
        x0=(mult_mod(x0,x0,x)+c)%x;
        llong d=gcd(y-x0,x);
        if(d!=1&&d!=x) return d;
        if(y==x0) return x;
        if(i==k){y=x0;k+=k;}
    }
}
//对n进行素因子分解
void findfac(llong n)
{
    if(Miller_Rabin(n))//素数
    {
        factor[tol++]=n;
        return;
    }
    llong p=n;
    while(p>=n)p=Pollard_rho(p,rand()%(n-1)+1);
    findfac(p);
    findfac(n/p);
}
int main()
{
   // srand(time(NULL));//需要time.h头文件  //POJ上G++要去掉这句话
    int T;
    llong n;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%I64d",&n);
        if(Miller_Rabin(n))
        {
            printf("Prime\n");
            continue;
        }
        tol=0;
        findfac(n);
        llong ans=factor[0];
        for(int i=1;i<tol;i++)
          if(factor[i]<ans)
             ans=factor[i];
        printf("%I64d\n",ans);
    }
    return 0;
}