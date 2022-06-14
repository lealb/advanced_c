#include <stdio.h>
#include <string.h>

char *getString()
{
    char buf[30];
    strcpy(buf, "abcde");
    return buf;
}
int main(int argc, char const *argv[])
{
    char *p1 = getString();
    printf("%d\n", p1);
    printf("%s\n", p1);
    return 0;
}
