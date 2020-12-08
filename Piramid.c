#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

double getTime()
{
    LARGE_INTEGER freq, val;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&val);
    return ((double)val.QuadPart / (double)freq.QuadPart);
}

void gen()
{
    int a, n;
    FILE* input_file = fopen("input.txt", "w");
    srand(time(NULL));
    n = rand() % 1000;
    fprintf(input_file, "%d\n", n);
    for(int i = 0; i < n; i++)
    {
        a = rand() % 1000;
        fprintf(input_file, "%d ", a);
    }
    fclose(input_file);
}

void init(int** ret_arr, int* ret_N)
{
    int N;
    FILE* input_file = fopen("input.txt", "r");
    fscanf(input_file, "%d", &N);
    int* arr = malloc(sizeof(int) * N);
    for(int i = 0; i < N; i++)
    {
        fscanf(input_file, "%d", &arr[i]);
    }
    fclose(input_file);

    *ret_arr = arr;
    *ret_N = N;
}

void base(int *arr, int begin, int end)
{
    int max, tmp, flag = 1;
    while((begin * 2 <= end) && (flag))
    {
        if (begin * 2 == end)
        {
            max = begin * 2;
        }
        else if (arr[begin * 2] > arr[(begin * 2) + 1])
        {
            max = begin * 2;
        }
        else
        {
            max = (begin * 2) + 1;
        }

        if (arr[begin] < arr[max])
        {
            int tmp = arr[begin];
            arr[begin] = arr[max];
            arr[max] = tmp;
            begin = max;
        }
        else
        {
            flag = 0;
        }
    }
}

void piramid_sort(int *arr, int N)
{
    int tmp;
    for(int i = (N / 2) - 1; i >= 0; i--)
    {
        base(arr, i, N - 1);
    }
    for(int i = N - 1; i >= 1; i--)
    {
        tmp = arr[0];
        arr[0] = arr[i];
        arr[i] = tmp;
        base(arr, 0, i - 1);
    }
}

save(int *arr, int N)
{
    FILE* output_file = fopen("output.txt", "w");
    fprintf(output_file, "%d\n", N);
    for(int i = 0; i < N; i++)
    {
        fprintf(output_file, "%d ", arr[i]);
    }
    fclose(output_file);
}

check(int *arr, int N)
{
    for(int i = 1; i < N; i++)
    {
        if (arr[i-1] > arr[i])
        {
            printf("Wrong!");
        }
    }
}

int main()
{
    int N, *arr;
    double start;
    gen();
    init(&arr, &N);
    start = getTime();
    piramid_sort(arr, N);
    printf("Lead time%: %lf", (getTime() - start) * 1000);
    check(arr, N);
    save(arr, N);
    free(arr);
    return 0;
}
