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
    for (int i = 0; i < n; i++)
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
    for (int i = 0; i < N; i++)
    {
        fscanf(input_file, "%d", &arr[i]);
    }
    fclose(input_file);

    *ret_arr = arr;
    *ret_N = N;
}

void quick_sort(int* arr, int L, int R)
{
    int i, j, s, tmp;
    i = L;
    j = R;
    s = arr[i + (j - i) / 2];
    while(i <= j)
    {
        while(arr[i] < s)
        {
            i++;
        }
        while(arr[j] > s)
        {
            j--;
        }

        if (i <= j)
        {
            tmp = arr[i];
            arr[i] = arr[j];
            arr[j] = tmp;
            i++;
            j--;
        }
    }
    if (L < j)
    {
        quick_sort(arr, L, j);
    }
    if (i < R)
    {
        quick_sort(arr, i, R);
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
    quick_sort(arr, 0, N-1);
    printf("Lead time%: %lf", (getTime() - start) * 1000);
    check(arr, N);
    save(arr, N);
    free(arr);
    return 0;
}
