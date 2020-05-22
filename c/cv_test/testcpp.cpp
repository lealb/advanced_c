#include <iostream>
#include <math.h>
using namespace std;
void swap(int a, int b)
{
    int temp = a;
    a = b;
    b = temp;
}
void solve(int a,int b,int c){
    printf("fun: %d,%d,%d",a,b,c);
    double x1=0,x2=0;
    double flag=b*b-4*a*c;
    if (flag>0)
    {
        x1=(-b+sqrt(flag))/2*a;
        x2=(-b-sqrt(flag))/2*a;
    }
    else if(flag==0){
        x1=x2=-b/2.0*a;
    }
    else if(flag<0){
        // 无实数解
        printf("no");
    }
    printf("x1=%.4lf,x2=%.4lf\n",x1,x2);
    
}
int main()
{
    int a,b,c;
    printf("input a b c:");
    scanf("&a &b &c",a,b,c);
    solve(a,b,c);
    return 0;
}
