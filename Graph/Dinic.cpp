typedef int integer;
vector<int>G[maxn];
struct Edge{
    int from,to;integer cap,flow;
};
struct Dinic
{
    int m,s,t; vector<Edge>edges;
    bool vis[maxn];int d[maxn],cur[maxn];

    void Addedge(int from,int to,int cap){
        edges.push_back((Edge){from,to,cap,0});
        edges.push_back((Edge){to,from,0,0});
        m=edges.size();
        G[from].push_back(m-2);
        G[to].push_back(m-1);
    }
    bool bfs(){
        memset(vis,0,sizeof(vis));
        queue<int>Q; Q.push(s);
        d[s]=0;vis[s]=1;
        while(!Q.empty()){
            int x=Q.front();Q.pop();
            for(int i=0;i<G[x].size();++i){
                Edge &e=edges[G[x][i]];
                if(!vis[e.to]&&e.cap>e.flow){
                    vis[e.to]=1;
                    d[e.to]=d[x]+1;
                    Q.push(e.to);
                }
            }
        }
        return vis[t];
    }
    integer dfs(int x,integer a){
        if(x==t||a==0)return a;
        integer flow=0,f;
        for(int &i=cur[x];i<G[x].size();++i){
            Edge &e=edges[G[x][i]];
            if(d[x]+1==d[e.to]&&(f=dfs(e.to,min(a,e.cap-e.flow)))>0){
                e.flow+=f;edges[G[x][i]^1].flow-=f;
                flow+=f; a-=f;
                if(a==0)break;
            }
        }
        if(flow==0)vis[x]=0;
        return flow;
    }
    integer Maxflow(int s,int t){
        this->s=s;this->t=t;
        integer flow=0;
        while(bfs()){
            memset(cur,0,sizeof(cur));
            flow+=dfs(s,INF);
        }
        return flow;
    }
};