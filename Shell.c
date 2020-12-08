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

void shell_sort(int *arr, int N)
{
	int tmp;
	for(int s = N / 2; s > 0; s = s / 2)
    {
        for(int i = s; i < N; i++)
        {
            for(int j = i - s; (j >= 0) && (arr[j] > arr[j + s]); j -= s)
            {
                tmp = arr[j];
				arr[j] = arr[j + s];
				arr[j + s] = tmp;
            }
        }
    }
}

save(int *arr, int N)
{
    FILE* output_file = fopen("output.txt", "w");
    fprintf(output_file, "%d\n", N);
    for (int i = 0; i < N; i++)
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
    shell_sort(arr, N);
    printf("Lead time%: %f", (getTime() - start) * 1000);
    check(arr, N);
    save(arr, N);
    free(arr);
    return 0;
}
