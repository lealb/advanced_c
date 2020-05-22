
#include <stdio.h>
#include <limits.h>
#define MAX_LINE 1024
void p_01()
{
    printf("From limits.h:\n");
    printf("CHAR_BIT: %d\n", CHAR_BIT);
    printf("CHAR_MAX: %d\n", CHAR_MAX);
    printf("CHAR_MIN: %d\n", CHAR_MIN);
    printf("INT_MAX: %d\n", INT_MAX);
    printf("INT_MIN: %d\n", INT_MIN);
    printf("LONG_MAX: %d\n", LONG_MAX);
    printf("LONG_MIN: %d\n", LONG_MIN);
    printf("SCHAR_MAX: %d\n", SCHAR_MAX);
    printf("SCHAR_MIN: %d\n", SCHAR_MIN);
    printf("SHRT_MAX: %d\n", SHRT_MAX);
    printf("SHRT_MIN: %d\n", SHRT_MIN);
    printf("UCHAR_MAX: %d\n", UCHAR_MAX);
    printf("UINT_MAX: %u\n", UINT_MAX);
    printf("ULONG_MAX: %u\n", ULONG_MAX);
    printf("USHRT_MAX: %u\n", USHRT_MAX);

    printf("\nFrom calc:\n");

    /*signed types*/
    printf("signed char min=%d\n", -(char)((unsigned char)~0 >> 1));
    printf("signed char max=%d\n", (char)((unsigned char)~0 >> 1));
    printf("signed int min=%d\n", -(int)((unsigned int)~0 >> 1));
    printf("signed int max=%d\n", (int)((unsigned int)~0 >> 1));
    printf("signed short min=%d\n", -(short)((unsigned short)~0 >> 1));
    printf("signed short max=%d\n", (short)((unsigned short)~0 >> 1));
    printf("signed long min=%d\n", -(long)((unsigned long)~0 >> 1));
    printf("signed long max=%d\n", (long)((unsigned long)~0 >> 1));

    /*unsigned types*/
    printf("unsigned char max=%u\n", ((unsigned char)~0 >> 1));
    printf("unsigned int max=%u\n", ((unsigned int)~0 >> 1));
    printf("unsigned long max=%lu\n", ((unsigned int)~0 >> 1));
    printf("unsigned short max=%u\n", ((unsigned int)~0 >> 1));
}

/**
 * for(i=0;i<lim-1&&(c=getchar())!='\n'&&c!=EOF;++i)
 * s[i]=c
 * 不使用&&和||替换
 */
int p_02(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != '\n' && c != EOF; ++i)
    {
        s[i] = c;
    }
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}
/**
 * 函数htoi(s),把由16进制数字的组成的字符串，转换为与之等价的整型值
 * 
 */
int atoi(char s[])
{
    int i, n;
    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0');
    return n;
}
int htoi(const char *s)
{
    if (!s)
        return 0;
    if (*s == '0')
    {
        s++;
        if (*s == 'x' || *s == 'X')
            s++;
    }
    int n = 0;
    while (*s)
    {
        n <<= 4;
        if (*s <= '9')
            n |= (*s & 0xf);
        else
            n |= ((*s & 0xf) + 9);
        s++;
    }
    return n;
}
int main(int argc, char const *argv[])
{
    // p_01();
    // int len;
    // char line[MAX_LINE];
    // while (len = p_02(line, MAX_LINE) > 0)
    // {
    //     printf("%s", line);
    // }
    // printf("%d\n", atoi("1234567890"));
    // printf("%d\n", atoi("1234abc567890"));
    printf("%x\n", htoi("0xa"));
    printf("%x\n", htoi("0XAB"));
    printf("%x\n", htoi("0xabc"));
    printf("%x\n", htoi("0x0a0b"));
    printf("%x\n", htoi("a"));
    printf("%x\n", htoi("ab"));
    printf("%x\n", htoi("abcfg"));
    printf("%x\n", htoi("0x1278AFC89"));
    return 0;
}
