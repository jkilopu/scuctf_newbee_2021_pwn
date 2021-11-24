#include <stdio.h>

// asm:
// ecx: n
// eax: initial
// esi: mul
// edx: i
// ebx: add
int main(void)
{
    int initial, mul, add, n;
    scanf("%d", &initial, &mul, &add, &n);

    for (int i = 0; i < n; i++)
    {
        initial = mul * initial + add;
    }
    return initial;
}
