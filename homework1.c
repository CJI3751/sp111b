#include <stdio.h>


// function 

double s (double x){
    return x*x;
    }


double integrate(double a, double b,int n){

    double dx = (b-a)/n;
    double x,sum =0.0;
    for (int i=0;i<n;i++){
        x = a+i*dx;
        sum += s(x)*dx;
    }
    return sum;
}


int main(void){
    double a = 0.0,double b = 1.0, int n = 1000;
    double answer = integrate(s,0.0,2.0,n);
    printf("answer is %f", answer );
}
