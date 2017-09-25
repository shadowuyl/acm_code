typedef int integer;
const integer inf=(1<<30);
const int maxn=200000+5;
integer addv[maxn*4],minv[maxn*4],maxv[maxn*4],setv[maxn*4];//setv初始化-1
integer arr[maxn];
int ql,qr;//询问的区间
int chl,chr;//更新的区间
integer res_min,res_max,res_sum;//每次询问前注意初始化
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

//单点更新
integer query(int o,int L,int R){
    int mid=L+(R-L)/2;integer res=inf;
    if(ql<=L&&qr>=R){
        return minv[o];
    }
    if(ql<=mid)res=min(res,query(o*2,L,mid));
    if(qr>mid)res=min(res,query(o*2+1,mid+1,R));
    return res;
}

int change_index;integer change_val;
void updateOneNode(int o,int L,int R){
    int mid=L+(R-L)/2;
    if(L==R)minv[o]=change_val;
    else{
        if(change_index<=mid)updateOneNode(o*2,L,mid);
        else updateOneNode(o*2+1,mid+1,R);
        minv[o]=min(minv[o*2],minv[o*2+1]);
    }
}


//区间加数
integer addval;//区间add的值
void maintain(int o,int L,int R){
    int lc=o*2,rc=o*2+1;
    if(R>L){
        sumv[o]=sumv[lc]+sumv[rc];
        minv[o]=min(minv[lc],minv[rc]);
        maxv[o]=max(maxv[lc],maxv[rc]);
    }else if(R==L){
        sumv[o]=arr[L];minv[o]=arr[L];maxv[o]=arr[L];
    }
    sumv[o]+=addv[o]*(R-L+1);minv[o]+=addv[o];maxv[o]+=addv[o];
}
void updateIntervalAdd(int o,int L,int R){
    int mid=L+(R-L)/2;
    if(chl<=L&&chr>=R)addv[o]+=addval;
    else{
        if(chl<=mid)updateIntervalAdd(o*2,L,mid);
        if(chr>mid)updateIntervalAdd(o*2+1,mid+1,R);
    }
    maintain(o,L,R);
}
void queryInIntervalAdd(int o,int L,int R,integer accumulation){
    if(ql<=L&&qr>=R){
        res_min=min(res_min,minv[o]+accumulation);
        res_max=max(res_max,maxv[o]+accumulation);
        res_sum+=(accumulation*(R-L+1)+sumv[o]);
    }else{
        int mid=L+(R-L)/2;
        if(ql<=mid)queryInIntervalAdd(o*2,L,mid,accumulation+addv[o]);
        if(qr>mid)queryInIntervalAdd(o*2+1,mid+1,R,accumulation+addv[o]);
    }
}

void pushdown(int o){
    int lc=o*2,rc=o*2+1;
    if(setv[o]>0){
        setv[lc]=setv[rc]=setv[o];
        setv[o]=-1;
    }
}

////区间置数
void maintainIntervalSet(int o,int L,int R){
    if(setv[o]>0){ sumv[o]=setv[o]*(R-L+1); }
    else{
        int lc=o*2,rc=o*2+1;
        if(R>L){ sumv[o]=sumv[lc]+sumv[rc]; }
        else if(R==L){ sumv[o]=arr[L]; }
    }
}
integer change_toval;//区间的数都变为change_toval
void updateIntervalSet(int o,int L,int R){
    int lc=o*2,rc=o*2+1;
    if(chl<=L&&chr>=R)setv[o]=change_toval;
    else{
        pushdown(o);
        int mid=L+(R-L)/2;
        if(chl<=mid)updateIntervalSet(lc,L,mid);else maintainIntervalSet(lc,L,mid);
        if(chr>mid)updateIntervalSet(rc,mid+1,R);else maintainIntervalSet(rc,mid+1,R);
    }
    maintainIntervalSet(o,L,R);
}
void queryInIntervalSet(int o,int L,int R){
    if(setv[o]>=0){
        res_min=min(res_min,setv[o]);
        res_max=max(res_max,setv[o]);
        res_sum+=setv[o]*(min(R,qr)-max(L,ql)+1);
    }else if(ql<=L&&qr>=R){
        res_sum+=sumv[o];
        res_min=min(res_min,minv[o]);
        res_max=max(res_max,maxv[o]);
    }else{
        int mid=L+(R-L)/2;
        if(ql<=mid)queryInIntervalSet(o*2,L,mid);
        if(qr>mid)queryInIntervalSet(o*2+1,mid+1,R);
    }
}