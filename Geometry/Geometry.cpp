#include <bits/stdc++.h>
using namespace std;
typedef double dble;
const dble PI = acos(-1.0);
const dble MAXN = 1000000.0;
struct Point{
    dble x,y;
    Point(dble x=0,dble y=0):x(x),y(y){}
};
typedef Point Vec;
Vec operator +(Vec A,Vec B){return Vec(A.x+B.x,A.y+B.y);}
Vec operator -(Point A,Point B){return Vec(A.x-B.x,A.y-B.y);}
Vec operator *(Vec A,dble p){return Vec(A.x*p,A.y*p);}
Vec operator /(Vec A,dble p){return Vec(A.x/p,A.y/p);}
bool operator <(const Point& a,const Point& b){
    return a.x<b.x || (a.x == b.x && a.y<b.y);
}
const dble EPS = 1e-10;
int dcmp(dble x){ if(fabs(x)<EPS) return 0;else return x<0? -1: 1; }
bool operator == (const Point& a,const Point &b){ return dcmp(a.x-b.x)==0 &&dcmp(a.y-b.y) == 0; }
dble ang(Vec v){return atan2(v.y,v.x);}

struct Line{
    Point P;
    Vec v;
    dble ang;
    Line(){}
    Line(Point P,Vec v):P(P),v(v){ang  = atan2(v.y,v.x);}
    bool operator < (const Line& L) const { return ang < L.ang; }
    Point point(dble a){ return P+v*a; }
};

struct Circle{
    Point c;
    dble r;
    Circle(Point c,dble r):c(c),r(r){}
    Point point(dble a){ return Point(c.x+cos(a)*r,c.y + sin(a)*r); }
};

dble Dot(Vec A,Vec B){return A.x*B.x+A.y*B.y;}
dble Length(Vec A){ return sqrt(Dot(A,A));}
dble Angle(Vec A,Vec B){return acos(Dot(A,B)/Length(A)/Length(B));}

dble Cross(Vec A,Vec B){return A.x*B.y - A.y*B.x;}
dble Area2(Point A,Point B,Point C){return Cross(B-A,C-A);}
//rad是弧度 逆时针旋转
Vec Rotate(Vec A,dble rad){ return Vec(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad)); }
//逆时针旋转90°的单位法向量
Vec Normal(Vec A){
    dble L = Length(A);
    return Vec(-A.y/L,A.x/L);
}
/*=====以上为叉积的基本运算=====*/


//P+tv和Q+tw两条直线的交点,确保有唯一交点
Point GetlineIntersection(Line a,Line b){
    Point P = a.P,Q = b.P;
    Vec v = a.v,w = b.v;
    Vec u = P-Q;
    dble t = Cross(w,u)/Cross(v,w);
    return a.point(t);
}
//点到直线的距离
dble DistanceToLine(Point P,Line a){
    Point A = a.P,B = a.P + a.v;
    Vec v1 = B-A,v2 = P-A;
    return fabs(Cross(v1,v2)/Length(v1));//不取绝对值那么得到的是有向距离
}
//点到线段的距离
dble DistanceToSegment(Point P,Point A,Point B){
    if(A == B)return Length(P-A);
    Vec v1 = B - A, v2 = P - A, v3 = P - B;
    if(dcmp(Dot(v1,v2))<0)return Length(v2);
    else if(dcmp(Dot(v1,v3)>0)) return Length(v3);
    else return fabs(Cross(v1,v2))/Length(v1);
}
//点在直线上的投影
Point GetLineProjection(Point P,Line a){
    Point A = a.P,B = a.P + a.v;
    Vec v = B - A;
    return A + v*(Dot(v,P-A) / Dot(v,v));
}
//判断两条线段是否相交 此处必须为规范相交
bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
    dble c1 = Cross(a2-a1,b1-a1),c2 = Cross(a2-a1,b2-a1);
    dble c3 = Cross(b2-b1,a1-b1),c4 = Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
//如果允许端点相交，则用以下代码，判断一个点是否在一条线段上
bool OnSegment(Point p,Point a1,Point a2){
    return dcmp(Cross(a1-p,a2-p)) == 0 && dcmp(Dot(a1-p,a2-p))<0;
}
/*=========以上为点和直线，直线和直线关系的内容========*/


//多边形有向面积
dble PolygonArea(vector<Point> p){
    int n = p.size();
    dble area = 0;
    for(int i=1;i<n-1;i++)
        area += Cross(p[i] - p[0],p[i+1]-p[0]);
    return area/2;
}
//多边形周长
dble PolygonZhouc(vector<Point> p){
    int n = p.size();
    dble ans = 0;
    for(int i=0;i<n-1;i++)
        ans+= Length(p[i+1]-p[i]);
    ans+=Length(p[0]-p[n-1]);
    return ans;
}
dble isint(dble x){
    return fabs(x - (int)(x+0.5))<EPS;
}
/*========多边形面积等内容=========*/

bool OnLeft(Line L,Point P){
    return Cross(L.v,P - L.P)>=0;          //如果线上的点不算就改成>
}
Point GetIntersection(Line a, Line b){
    Vec u = a.P - b.P;
    dble t = Cross(b.v,u)/Cross(a.v,b.v);
    return a.P+a.v*t;
}
int HalfplaneIntersection(Line* L,int n,Point* poly){
    sort(L,L+n);
    int first,last;
    Point *p = new Point[n];
    Line *q = new Line[n];
    q[first = last = 0] = L[0];
    for(int i=1;i<n;i++){
        while(first<last && !OnLeft(L[i],p[last-1]))last--;
        while(first<last && !OnLeft(L[i],p[first]))first++;
        q[++last] = L[i];
        if(fabs(Cross(q[last].v,q[last-1].v))<EPS){
            last--;
            if(OnLeft(q[last],L[i].P))q[last] = L[i];
        }
        if(first<last) p[last-1] = GetIntersection(q[last-1],q[last]);
    }
    while(first<last && !OnLeft(q[first],p[last-1]))last -- ;
    if(last-first<=1)return 0;
    p[last] = GetIntersection(q[last],q[first]);
    int m = 0;
    for(int i=first;i<=last;i++)poly[m++] = p[i];
    return m;
}
/*=========半平面交所需函数及主过程=========*/

vector<Point> ConvexHull(vector<Point> p){
    sort(p.begin(),p.end());
    //删除重复点
    p.erase(unique(p.begin(),p.end()),p.end());
    int n = p.size();
    vector<Point> ch(n+1);
    int m = 0;
    for(int i=0;i<n;i++){
        while(m>1 && Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2]) <= 0) m--;         //若需要把边线上的点也算上，把等号去掉
        ch[m++] = p[i];
    }
    int k = m;
    for(int i = n-2;i>=0;i--){
        while(m > k && Cross(ch[m-1] - ch[m-2] , p[i]-ch[m-2] ) <= 0)m--;
        ch[m++] = p[i];
    }
    if(n > 1)m--;
    ch.resize(m);
    return ch;
}
/*=============以上为凸包==========*/

dble earthdis(Point a,Point b){
    dble x1=PI*a.x/180.0;
    dble y1=PI*a.y/180.0;
    dble x2=PI*b.x/180.0;
    dble y2=PI*b.y/180.0;
    return acos(cos(x1-x2)*cos(y1)*cos(y2)+sin(y1)*sin(y2));
}
/*=======给出经纬度，算出球体上两点之间的角度=====*/


//判断圆和直线交点
int getLineCircleIntersection(Line L, Circle C, dble& t1,dble& t2,vector<Point>& sol){
    dble a = L.v.x, b = L.P.x-C.c.x, c = L.v.y, d = L.P.y - C.c.y;
    dble e = a*a+c*c,f = 2*(a*b+c*d),g = b*b-C.r*C.r;
    dble delta = f*f - 4*e*g;             //判别式
    if(dcmp(delta) < 0)return 0;              //相离
    if(dcmp(delta) == 0){                   //相切
        t1 = t2 = -f/(2*e);sol.push_back(L.point(t1));
        return 1;
    }
    //相交
    t1 = (-f - sqrt(delta)) / (2*e); sol.push_back(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2*e); sol.push_back(L.point(t2));
    return 2;
}
//判断两圆相交
int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol){
    dble d = Length(C1.c-C2.c);
    if(dcmp(d)==0){
        if(dcmp(C1.r-C2.r)==0)return -1;//重合
        return 0;
    }
    if(dcmp(C1.r + C2.r -d) < 0) return 0;
    if(dcmp(fabs(C1.r-C2.r)-d)>0)return 0;

    dble a = ang(C2.c - C1.c);
    dble da = acos((C1.r * C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
    Point p1 = C1.point(a-da),p2 = C1.point(a+da);

    sol.push_back(p1);
    if(p1 == p2)return 1;
    sol.push_back(p2);
    return 2;
}
//过点p到圆C的切线
int getTangents(Point p,Circle c,vector<Line> L){
    Vec u = C.c - p , temp;
    dble dist = Length(u);
    if(dist < C.r) return 0;
    else if(dcmp(dist - C.r) == 0){
        temp = Rotate(u,PI/2);
        L.push_back(Line(p,temp));
        return 1;
    }else {
        dble ang = asin(C.r/dist);
        temp = Rotate(u,-ang),L.push_back(Line(p,temp));
        temp = Rotate(u,+ang),L.push_back(Line(p,temp));
        return 2;
    }
}
/*==========以上为圆的常用函数及计算==========*/

// 三角形
// 1、重心到顶点的距离与重心到对边中点的距离之比为2︰1。
// 2、重心和三角形3个顶点组成的3个三角形面积相等。即重心到三条边的距离与三条边的长成反比。
// 3、重心到三角形3个顶点距离的平方和最小。
// 4、在平面直角坐标系中，重心的坐标是顶点坐标的算术平均，即其重心坐标为（(X1+X2+X3)/3，（Y1+Y2+Y3)/3。

int main()
{
    return 0;
}
