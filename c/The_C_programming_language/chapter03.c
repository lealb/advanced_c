#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getNums(int min, int max)
{
    srand((unsigned)time(NULL));
    return rand() % (max - min + 1) + min;
}
/**
 * @x 查找值
 * @v 数组
 */
int binsearch(int x, int *v)
{
    int low, high, mid;

    low = 0;
    printf("%d\n",sizeof(v));
    printf("%d\n",sizeof(v) / sizeof(v[0]));
    high = sizeof(v) / sizeof(v[0]) - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
        {
            high = mid - 1;
        }
        else if (x > v[mid])
        {
            low = mid + 1;
        }
        else
        {
            return mid;
        }
        return -1;
    }
}

int main(int argc, char const *argv[])
{
    // printf("%d", getNums(10, 100));
    int arr[] = {1, 2, 3, 4, 7, 98, 0, 12, 35, 99, 14};
    printf("%d\n",sizeof(arr) / sizeof(arr[0]));
    printf("%d\n", binsearch(3, arr));
    return 0;
}
