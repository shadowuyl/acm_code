const int maxn=50000+10;
typedef long long llong;
int head[maxn],edgeCnt;
struct Edge{
    int to,nxt;
};
Edge edges[maxn*2];
void addEdge(int u,int v){
    ++edgeCnt;
    edges[edgeCnt].to=v;
    edges[edgeCnt].nxt=head[u];
    head[u]=edgeCnt;
}
int son[maxn],deep[maxn],top[maxn],fa[maxn],num[maxn],chainid[maxn],chainInx;//num-子树大小，son-重儿子，chainid-树剖后节点标号
int arr[maxn];
int n,m;
void init(){
    memset(num,0,sizeof(num));
    memset(deep,-1,sizeof(deep));
    memset(son,-1,sizeof(son));
    memset(fa,-1,sizeof(fa));
    chainInx=1;
    edgeCnt=0;
    memset(head,-1,sizeof(head));
    for(int i=1;i<=n;++i){
        edges[i].to=0;edges[i].nxt=0;
    }
}
void dfs1(int curnode,int prenode){
    int tmp=-1,tmpinx=-1;
    for(int i=head[curnode];i!=-1;i=edges[i].nxt){
        int v=edges[i].to;
        if(v==prenode)continue;
        deep[v]=deep[curnode]+1;
        fa[v]=curnode;
        dfs1(v,curnode);
        num[curnode]+=num[v];
        if(tmp<num[v]){
            tmpinx=v;tmp=num[v];
        }
    }
    son[curnode]=tmpinx;
}
void dfs2(int curnode,int topnode){
    top[curnode]=topnode;
    chainid[curnode]=chainInx++;
    if(son[curnode]!=-1){dfs2(son[curnode],topnode);}
    else return;
    for(int i=head[curnode];i!=-1;i=edges[i].nxt){
        int v=edges[i].to;
        if(v==fa[curnode]||v==son[curnode])continue;
        dfs2(v,v);
    }
}
