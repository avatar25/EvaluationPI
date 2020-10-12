#include <stdio.h>
#include <omp.h>
#include <math.h>

double  FirstMethod(int N);
double SecondMethod(int N);
int main()
{
    // 4[1-1/3+1/5-1/7+1/9....]
    int N;
    printf("Enter the number of iterations: ");
    scanf("%d", &N);
    printf("\nThe estimated value of pi: \n");
#pragma omp parallel sections
{
#pragma omp section
    {
        FirstMethod(N);
    }
#pragma omp section
    {
        SecondMethod(N);
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
    printf("\nUsing first method: %lf", PI);
}

double SecondMethod(int N)
{
    float x=0;
    float sum = 0.0;
    float step;
    double aux;
    double pi;
    step = 1.0/N;
#pragma omp parallel private(pi,x,aux) shared(sum)
    {
#pragma omp for schedule(static)
        for (int i=0; i<N; i=i+1){

            x=(i+0.5)*step;
            aux=4.0/(1.0+x*x);
#pragma omp critical
            sum = sum + aux;
        }
    }
    pi=step*sum;
    printf("\nUsing second method: ");
    printf("%lf", pi);
}

