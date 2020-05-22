#include <stdio.h>
#include<math.h>
void swap(int a, int b)
{
    int temp;
    temp = a;
    a = b;
    b = temp;
}
/**
 * 数学归纳法与递归
 */
void prove(int n)
{
    int k;
    printf("现在证明P(%d)成立\n", n);
    k = 0;
    printf("根据步骤1得出P(%d)成立\n", k);
    while (k < n)
    {
        printf("根据步骤2可以说“若P(%d)成立,则P(%d)也成立”\n", k, k + 1);
        printf("因此可以说“P(%d)是成立的”\n", k + 1);
        k += 1;
    }
}
void solve(int a,int b,int c){
    printf("fun: %dx^2+%dx+%d\n",a,b,c);
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
        printf("no\n");
    }
    printf("slove: x1=%.4lf,x2=%.4lf\n",x1,x2);
}
int main()
{
    int a ,b,c;
    // printf("input a b c:");
    // scanf("%d%d%d",&a,&b,&c);
    // solve(a,b,c);
    prove(3);
    return 0;
}
