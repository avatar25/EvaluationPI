#include <stdio.h>
#include <omp.h>
#include <stdlib.h>
#include <math.h>

void FirstMethod(int N);
void SecondMethod(int N);
void ThirdMethod(int N);
int main()
{
    int N;
    printf("Enter the number of iterations: ");
    scanf("%d", &N);
    printf("\nThe estimated value of pi: \n");
    omp_set_num_threads(20);
    double start, end;
#pragma omp parallel sections
{
#pragma omp section
    {
        start = omp_get_wtime();
        FirstMethod(N);
        end = omp_get_wtime();
        printf("\nTime to run 4*(1-1/3+1/5-1/7+1/9....) method in parallel: %lf seconds\n\n", end - start);
    }
#pragma omp section
    {
        start = omp_get_wtime();
        SecondMethod(N);
        end = omp_get_wtime();
        printf("\nTime to run f(x) = 4/(1+x*x) method in parallel: %lf seconds\n\n", end - start);
    }
#pragma omp section
    {
        start = omp_get_wtime();
        ThirdMethod(N);
        end = omp_get_wtime();
        printf("\nTime to monte carlo method in parallel: %lf seconds\n\n", end - start);
    }
}
    return 0;
}

void FirstMethod(int N)
{
    double PI;
    double b;
    double a;
    double sum;
    int r1;
    int n = 0;

#pragma omp parallel for schedule(dynamic)
        for(int i=1;i<N;i=i+2)
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
        printf("\nUsing 4*(1-1/3+1/5-1/7+1/9....) method: %.20lf", PI);

}

void SecondMethod(int N)
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
    printf("\nUsing f(x) = 4/(1+x*x) method: %.20lf", pi);
}

void ThirdMethod(int N)
{
    double rand_x, rand_y, origin_dist, Pi;
    int circle_points = 0, square_points = 0;
#pragma omp parallel for schedule(static)
    for (int i = 0; i < (N * N); i++) {

        rand_x = (double)(rand() % (N + 1)) / N;
        rand_y = (double)(rand() % (N + 1)) / N;


        origin_dist = rand_x * rand_x + rand_y * rand_y;

        if (origin_dist <= 1)
            circle_points++;

        square_points++;
#pragma omp critical
        Pi = (double)(4 * circle_points) / square_points;
    }
        printf("\nUsing monte carlo method: %.20lf", Pi);

}
