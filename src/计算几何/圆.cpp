namespace _circle{
	struct circle{
		point o;
		double r;
		circle(point _o=point(0,0),double _r=0.0):o(_o),r(_r){}
	};
	void point_of_circle_across_line(point a,point b,circle o,point ret[],int &num){///直线和圆的交点
		double x0 = o.o.x , y0 = o.o.y;
		double x1 = a.x , y1 = a.y;
		double x2 = b.x , y2 = b.y;
		double r = o.r;
		double dx = x2-x1 , dy = y2-y1;
		double A = dx*dx+dy*dy;
		double B = 2*dx*(x1-x0)+2*dy*(y1-y0);
		double C = (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
		double delta = B*B-4*A*C;
		num = 0;
		if(cmp(delta)>=0){
			double t1 = (-B-sqrt(delta))/(A*2);
			double t2 = (-B+sqrt(delta))/(A*2);
			ret[num++] = point(x1+t1*dx,y1+t1*dy);
			ret[num++] = point(x1+t2*dx,y1+t2*dy);
		}
	}
	void point_of_circle_across_segment(point a,point b,circle o,point ret[],int &num){///线段和圆的交点
		double x0 = o.o.x , y0 = o.o.y;
		double x1 = a.x , y1 = a.y;
		double x2 = b.x , y2 = b.y;
		double r = o.r;
		double dx = x2-x1 , dy = y2-y1;
		double A = dx*dx+dy*dy;
		double B = 2*dx*(x1-x0)+2*dy*(y1-y0);
		double C = (x1-x0)*(x1-x0)+(y1-y0)*(y1-y0)-r*r;
		double delta = B*B-4*A*C;
		num = 0;
		if(cmp(delta)>=0){
			double t1 = (-B-sqrt(delta))/(A*2);
			double t2 = (-B+sqrt(delta))/(A*2);
			if(cmp(t1-1)<=0&&cmp(t1)>=0)
				ret[num++] = point(x1+t1*dx,y1+t1*dy);
			if(cmp(t2-1)<=0&&cmp(t2)>=0)
				ret[num++] = point(x1+t2*dx,y1+t2*dy);
		}
	}
	circle outer_circle_of_triangle(point t0,point t1,point t2){///三角形外接圆
		circle tmp;
		double a=(t0-t1).len();
		double b=(t0-t2).len();
		double c=(t1-t2).len();
		tmp.r=a*b*c/4/triangle(t0,t1,t2).area();
		double a1=t1.x-t0.x;
		double b1=t1.y-t0.y;
		double c1=(a1*a1+b1*b1)/2;
		double a2=t2.x-t0.x;
		double b2=t2.y-t0.y;
		double c2=(a2*a2+b2*b2)/2;
		double d=a1*b2-a2*b1;
		tmp.o.x=t0.x+(c1*b2-c2*b1)/d;
		tmp.o.y=t0.y+(a1*c2-a2*c1)/d;
		return tmp;
	}
	circle min_circle_cover(point p[],int n){///最小圆覆盖
		random_shuffle(p,p+n);//随机排序取点
		circle ret;
		ret.o=p[0];
		ret.r=0;
		for(int i=1;i<n;i++){
			if((p[i]-ret.o).len()>ret.r+eps){
				ret.o=p[i];
				ret.r=0;
				for(int j=0;j<i;j++){
					if((p[j]-ret.o).len()>ret.r+eps){
						ret.o = (p[i]+p[j])/2;
						ret.r=(p[i]-p[j]).len()/2;
						for(int k=0;k<j;k++)
							if((p[k]-ret.o).len()>ret.r+eps)
								ret=outer_circle_of_triangle(p[i],p[j],p[k]);
					}
				}
			}
		}
		return ret;
	}
	double area_circle_across_circle(circle a, circle b) {///圆的交
		double d = (a.o-b.o).len();
		if (d >= a.r + b.r)
			return 0;
		if (d <= fabs(a.r - b.r)) {
			double r = a.r < b.r ? a.r : b.r;
			return pi * r * r;
		}
		double ang1 = acos((a.r * a.r + d * d - b.r * b.r) / 2. / a.r / d);
		double ang2 = acos((b.r * b.r + d * d - a.r * a.r) / 2. / b.r / d);
		double ret = ang1 * a.r * a.r + ang2 * b.r * b.r - d * a.r * sin(ang1);
		return ret;
	}
	bool point_inon_circle(point p,circle c){
		double dis = (p-c.o).len();
		return dis<=c.r;
	}
}
using namespace _circle;
