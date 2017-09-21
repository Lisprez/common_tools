#include <stdio.h>
#include <stdlib.h>

/**
 * 这个变长的结构体机制是 C99 之后才有的柔性数组
 * 就是允许结构中的最后一个元素是一个数组标识
 * 但是初始这个不占用内存空间
 */

typedef struct _my_t {
    int i;
    int arr[0];
} my_t;

int main(void)
{
    my_t my;
    int i;
    printf("%lu\n", sizeof(my));
    my_t* p = (my_t*)malloc(sizeof(my_t) + 100 * sizeof(int));
    for (i = 0; i < 100; i++) {
        p->arr[i] = i;
    }

    for (i = 0; i < 100; i++) {
        printf("%d ", p->arr[i]);
    }

    printf("%lu\n", sizeof(my));

    free(p);
    return 0;
}
