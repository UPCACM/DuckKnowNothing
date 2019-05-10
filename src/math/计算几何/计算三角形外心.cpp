//C++
float S(float x1,float y1,float x2,float y2,float x3,float y3){
    return ((x1-x3)*(y2-y3)-(y1-y3)*(x2-x3) );
}
 
float cal_center_x(float x1,float y1,float x2,float y2,float x3,float y3){
    return (S(x1*x1+y1*y1,y1, x2*x2+y2*y2, y2,x3*x3+y3*y3,y3)/(2*S(x1,y1,x2,y2,x3,y3)) );
}
 
float cal_center_y(float x1,float y1,float x2,float y2,float x3,float y3){
    return (S(x1, x1*x1+y1*y1, x2, x2*x2+y2*y2, x3, x3*x3+y3*y3) / (2*S(x1,y1,x2,y2,x3,y3)));
}

//Java:
public class Main {
	private static BigDecimal S(BigDecimal x1,BigDecimal y1,BigDecimal x2,BigDecimal y2,BigDecimal x3,BigDecimal y3) {
        return ((x1.subtract(x3)).multiply(y2.subtract(y3)).subtract((y1.subtract(y3)).multiply(x2.subtract(x3))));
    }
    private static BigDecimal cal_center_x(BigDecimal x1,BigDecimal y1,BigDecimal x2,BigDecimal y2,BigDecimal x3,BigDecimal y3) {
        return ((S((x1.multiply(x1)).add((y1.multiply(y1))), y1, (x2.multiply(x2)).add((y2.multiply(y2))), y2, (x3.multiply(x3)).add((y3.multiply(y3))), y3)).divide(S(x1,y1,x2,y2,x3,y3).multiply(BigDecimal.valueOf(2))));
    }
    private static BigDecimal cal_center_y(BigDecimal x1,BigDecimal y1,BigDecimal x2,BigDecimal y2,BigDecimal x3,BigDecimal y3) {
        return ((S(x1, (x1.multiply(x1)).add((y1.multiply(y1))), x2, (x2.multiply(x2)).add((y2.multiply(y2))), x3, (x3.multiply(x3)).add((y3.multiply(y3))))).divide(S(x1,y1,x2,y2,x3,y3).multiply(BigDecimal.valueOf(2))));
    }
}