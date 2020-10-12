#include <stdio.h>
#include <omp.h>
#include <math.h>

double  FirstMethod(int N);
int main()
{
    // 4[1-1/3+1/5-1/7+1/9....]
    int N;
    printf("Enter the number of iterations for first method: ");
    scanf("%d", &N);
#pragma omp parallel sections
{
#pragma omp section
    {
        FirstMethod(N);
    }
#pragma omp section
    {


    }
}
    return 0;
}

double FirstMethod(int N)
{
    double PI;
    double b;
    double a;
    double sum;
    int r1;
    int n = 0;
    for(float i=1;i<N;i=i+2)
    {
       // printf("\n%d ",i);
        b = i;
        a = 1/b;
        //printf("%lf",a);
        r1 = pow(-1,n);
        a = r1*a;
        n=n+1;
        sum=sum+a;
    }
    PI = 4 * sum;
    printf("\nThe sum is: %lf", sum);
    printf("\nThe estimated value of pi is %lf", PI);
}
