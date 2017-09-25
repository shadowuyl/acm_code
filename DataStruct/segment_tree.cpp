typedef int integer;
const integer inf=(1<<30);
const int maxn=200000+5;
integer addv[maxn*4],minv[maxn*4],maxv[maxn*4],setv[maxn*4];
integer arr[maxn];
void build(int o,int L,int R){
    int mid=L+(R-L)/2;
    if(L==R){
        minv[o]=arr[L];
        return;
    }
    build(o*2,L,mid);
    build(o*2+1,mid+1,R);
    minv[o]=min(minv[o*2],minv[o*2+1]);
}

int ql,qr;//询问区间
integer query(int o,int L,int R){
    int mid=L+(R-L)/2;integer res=inf;
    if(ql<=L&&qr>=R){
        return minv[o];
    }
    if(ql<=mid)res=min(res,query(o*2,L,mid));
    if(qr>mid)res=min(res,query(o*2+1,mid+1,R));
    return res;
}

int change_index;integer change_val;//单点修改
void updateOneNode(int o,int L,int R){
    int mid=L+(R-L)/2;
    if(L==R)minv[o]=change_val;
    else{
        if(change_index<=mid)updateOneNode(o*2,L,mid);
        else updateOneNode(o*2+1,mid+1,R);
        minv[o]=min(minv[o*2],minv[o*2+1]);
    }
}