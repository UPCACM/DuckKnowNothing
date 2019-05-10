// time complexity O(log(n))
inline bool solve(ll n,ll &p,ll &q){
    ll N,p1,p2,q1,q2,a0,a1,a2,g1,g2,h1,h2;
    g1=q2=p1=0;
    h1=q1=p2=1;
    a0=a1=sqrt(n*1.0);
    ll ans = a0*a0;
    N = n;
    if(ans==N) return false;
    while(1){
        g2 = a1*h1-g1;
        h2 = (N-g2*g2)/h1;
        a2 = (g2+a0)/h2;
        p = a1*p2+p1;
        q = a1*q2+q1;
        if(p*p==(N*q*q+1)) break;
        g1 = g2;
        h1 = h2;
        a1 = a2;
        p1 = p2;
        p2 = p;
        q1 = q2;
        q2 = q;
    }
    return true;
}//nth xn + yn*sqrt(n)  = (x1+y1*sqrt(n)) ^ n