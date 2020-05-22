#include <stdio.h>

void p_1()
{
    int dogs;
    printf("How many dogs do you have?\n");
    scanf("%d", &dogs);
    printf("So you have %d dog(s)!", dogs);
}
int main()
{
    p_1();
    return 0;
}
