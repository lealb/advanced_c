#include <stdio.h>

void hello()
{
    printf("Hello World\n");
}

/**
 * print Fahrenherit-Celsius table
 */
void fcTable()
{
    float fahr, celsius;
    float lower, upper, step;

    lower = 0;
    upper = 300,
    step = 20;

    fahr = lower;
    printf("fahr\tcelsius\n"); //1-3
    while (fahr <= upper)
    {
        celsius = 5.0 / 9 * (fahr - 32);
        printf("%3.0f\t%6.1f\n", fahr, celsius);
        fahr += step;
    }
}
void cfTable()
{
    for (int i = -50; i <= 100; i += 20)
    {
        printf("%3.0f\t%6.1f\n", i, i * 9.0 / 5 + 32);
    }
}
void copy1()
{
    int c = getchar();
    while (c != EOF)
    {
        putchar(c);
        c = getchar();
    }
}
void copy2()
{
    int c;
    while ((c = getchar()) != EOF)
    {
        putchar(c);
        printf("getchar()!=EOF: %d\n", getchar() != EOF);
        printf("EOF: %d\n", EOF);
    }
}
void count1()
{
    long nc = 0;
    while (getchar() != EOF)
    {
        ++nc;
    }
    printf("count1: %ld\n", nc);
}
void count2()
{
    double nc;
    for (nc = 0; getchar() != EOF; ++nc)
        ;
    printf("count2: %.f\n", nc);
}
void countLine()
{
    int c, line = 0;
    int tabCount = 0, spaceCount = 0;
    while ((c = getchar()) != EOF)
    {
        if (c == '\n')
        {
            line++;
        }
        if (c == ' ')
        {
            spaceCount++;
        }
        if (c == '\t')
        {
            tabCount++;
        }
    }
    printf("line: %d, space: %d, tab: %d\n", line, spaceCount, tabCount);
}
void t_1_9(){
    int c;
    int spaceCount;
    while ((c=getchar()!=EOF))
    {
         if (c == ' ')
        {
            spaceCount++;
        }
        putchar(c);
    }
    
}
int main(int argc, char const *argv[])
{
    // hello();
    // fcTable();
    // cfTable();
    // copy1();
    // copy2();
    // count1();
    // count2();
    countLine();
    return 0;
}
