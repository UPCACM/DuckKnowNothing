// 调用asr(积分左端点，积分右端点，精度）返回积分结果
namespace Simpson_Integral {
	double F(double x) {
		return b/a*sqrt(a*a-x*x);
	}
	double simpson(double a,double b){
		double c = a + (b-a)/2;
		return (F(a)+4*F(c)+F(b))*(b-a)/6;
	}
	double asr(double a,double b,double eps,double A){
		double c = a + (b-a)/2;
		double L = simpson(a,c), R = simpson(c,b);
		if(fabs(L + R - A) <= 15*eps)return L + R + (L + R - A)/15.0;
		return asr(a,c,eps/2,L) + asr(c,b,eps/2,R);
	}
	double asr(double a,double b,double eps){
		return asr(a,b,eps,simpson(a,b));
	}
}
