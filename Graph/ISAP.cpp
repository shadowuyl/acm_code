typedef long long llong;
typedef int integer;
const int maxn=205;
const int inf=1e9;
int cur[maxn],d[maxn],p[maxn],num[maxn];
bool vis[maxn];
int src,tag,n;//源点，回点，节点数（节点标号0~n-1）

struct Edge{
    int from,to;integer cap,flow;
};
vector<Edge>edges;
vector<int>G[maxn];
void init(){
    edges.clear();
    for(int i=0;i<n;++i)G[i].clear();
}
void AddEdge(int from,int to,integer cap){
    edges.push_back((Edge){from,to,cap,0});
    edges.push_back((Edge){to,from,0,0});
    int tmpm=edges.size();
    G[from].push_back(tmpm-2);
    G[to].push_back(tmpm-1);
}

bool bfs()
{
    memset(vis, 0, sizeof(vis));
    queue<int> Q;
    Q.push(tag);
    vis[tag] = 1;
    d[tag] = 0;
    while (!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (vector<int>::iterator ix = G[u].begin(); ix != G[u].end(); ++ix) {
            Edge &e = edges[(*ix)^1];
            if (!vis[e.from] && e.cap > e.flow) {
                vis[e.from] = true;
                d[e.from] = d[u] + 1;
                Q.push(e.from);
            }
        }
    }
    return vis[src];
}

integer augment()
{
    int u = tag;integer df =inf ;
    while (u != src) {
        Edge &e = edges[p[u]];
        df = min(df, e.cap - e.flow);
        u = edges[p[u]].from;
    }
    u = tag;
    while (u != src) {
        edges[p[u]].flow += df;
        edges[p[u]^1].flow -= df;
        u = edges[p[u]].from;
    }
    return df;
}

integer max_flow()
{
    integer flow = 0;bfs();
    memset(num, 0, sizeof(num));
    for (int i = 0; i < n; i++) num[d[i]]++;
    int u = src;
    memset(cur, 0, sizeof(cur));
    while (d[src] <n) {
        if (u == tag) {
            flow += augment();
            u = src;
        }
        bool advanced = false;
        for (int i = cur[u]; i < G[u].size(); i++) {
            Edge& e = edges[G[u][i]];
            if (e.cap > e.flow && d[u] == d[e.to] + 1) {
                advanced = true;
                p[e.to] = G[u][i];
                cur[u] = i;
                u = e.to;
                break;
            }
        }
        if (!advanced) {
            int tmpm = n - 1;
            for (vector<int>::iterator ix = G[u].begin(); ix != G[u].end(); ++ix)
                if (edges[*ix].cap > edges[*ix].flow)
                    tmpm = min(tmpm, d[edges[*ix].to]);
            if (--num[d[u]] == 0) break;
            num[d[u] = tmpm+1]++;
            cur[u] = 0;
            if (u != src)
                u = edges[p[u]].from;
        }
    }
    return flow;
}
