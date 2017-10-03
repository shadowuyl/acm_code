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
