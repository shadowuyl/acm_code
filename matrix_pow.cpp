llong mod=998244353;
const int N=2;
struct Matrix{
    llong mat[N][N];
    Matrix(){memset(mat,0,sizeof(mat));}
    Matrix(llong argmat[][N]){
        for(int i=0;i<N;++i)
            for(int j=0;j<N;++j)mat[i][j]=(argmat[i][j]+mod)%mod;
    }
};
Matrix mulmat(Matrix a,Matrix b) {
    Matrix res;
    for(int i=0;i<N;++i){
        for(int j=0;j<N;++j){
            for(int k=0;k<N;++k){
                res.mat[i][j]=(res.mat[i][j]+(a.mat[i][k]*b.mat[k][j])%mod)%mod;
            }
        }
    }
    return res;
}
Matrix powmat(Matrix a,llong inx){
    Matrix res;
    for(int i=0;i<N;++i)res.mat[i][i]=1;
    while(inx>0){
        if(inx&1)res=mulmat(res,a);
        a=mulmat(a,a);
        inx=(llong)inx>>1;
    }
    return res;
}
