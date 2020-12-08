#include <conio.h>
#include <math.h>
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
    //n = rand() % 1000;
    n = 10000;
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

void introsort(int* arr, int L, int R, int depth)
{
    int s, hold_l, hold_r, tmp;

    if (L >= R)
    {
        return;
    }

    if (depth <= 0)
    {
        for(int i = L; i < R; i++)
        {
            for(int j = ((R + 1) / 2) - 1 - i / 2; j >= 0; j--)
            {
                if((j * 2) + 2 <= R - i - 1)
                {
                    if(arr[j] < arr[(j * 2) + 2])
                    {
                        tmp = arr[j];
                        arr[j] = arr[(j * 2) + 2];
                        arr[(j * 2) + 2] = tmp;
                    }
                }
                if((j * 2) + 1 <= R - i - 1)
                {
                    if(arr[j] < arr[(j * 2) + 1])
                    {
                        tmp = arr[j];
                        arr[j] = arr[(j * 2) + 1];
                        arr[(j * 2) + 1] = tmp;
                    }
                }

            }
            tmp = arr[0];
            arr[0] = arr[R - i - 1];
            arr[R - i - 1] = tmp;
        }
    }

    s = arr[(L + R) / 2];
    hold_l = L - 1;
    hold_r = R + 1;

    while(1)
    {
        hold_l++;
        while(arr[hold_l] < s)
        {
            hold_l++;
        }
        hold_r--;
        while(arr[hold_r] > s)
        {
            hold_r--;
        }
        if(hold_l >= hold_r)
        {
            break;
        }
        tmp = arr[hold_l];
        arr[hold_l] = arr[hold_r];
        arr[hold_r] = tmp;
    }
    introsort(arr, L, hold_r, depth - 1);
    introsort(arr, hold_r + 1, R, depth - 1);
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
    int N, *arr, depth;
    double start;
    depth = (int)floor(2 * log(N));
    gen();
    init(&arr, &N);
    start = getTime();
    introsort(arr, 0 , N - 1, depth);
    printf("Lead time%: %.5f", (getTime() - start) * 1000);
    save(arr, N);
    check(arr, N);
    free(arr);
    return 0;
}
