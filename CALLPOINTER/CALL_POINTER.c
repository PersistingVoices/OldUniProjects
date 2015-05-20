#include <stdio.h>

int main()
{
    int x, y, *a, *b, temp;
    
    printf("-----------Swapping with pointers in C-------\n");
    printf("Please enter the value of x \n");
    scanf("%d", &x);
    printf("\n");
    printf("Please enter the value of y\n");
    scanf("%d", &y);
    printf("\n");

    a = &x;
    b = &y;

    temp = *b;
    *b   = *a;
    *a   = temp;

    printf("After Swap:\nx = %d\ny = %d\n", x, y);

    return 0;
}
