#include <stdio.h>

void t_2_2()
{
    char title[] = "LongMai C language pointer";
    char *p_title;
    printf("%s\n", title);
    p_title = title; // title[0]
    printf("%s\n", p_title);
    printf("%c\n", title[0]);
    printf("%p\n", &title);
    printf("%p\n", p_title);
    printf("%p\n", &title[0]);
}
void t_2_9()
{
    char *str[] = {"China", "Japan", "USA"};
    printf("%s->%p\n", str[0], str[0]);
    printf("%s->%p\n", str[1], str[1]);
    printf("%s->%p", str[2], str[2]);
}
int main()
{
    t_2_9();
    return 0;
}
