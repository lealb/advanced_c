#include <stdio.h>
#define MAXLINE 1000
/**
 * get line into s,return length
 */
int getline(char s[], int lim)
{
    int c, i;
    i = 0;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
    {
        s[i++] = c;
    }
    if (c == '\n')
    {
        s[i++] = c;
    }
    s[i] = '\0';
    return i;
}

int strindex(char s[], char t[])
{
    int j, k;
    for (int i = 0; s[i] != '\0'; i++)
    {
        for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
            ;
        if (k > 0 && t[k] == '\0')
        {
            return i;
        }
    }
    return -1;
}

int main(int argc, char const *argv[])
{
    // char pattern[] = "ould";
    // char line[MAXLINE];
    // int found = 0;
    // while (getline(line, MAXLINE) > 0)
    // {
    //     if (strindex(line, pattern) >= 0)
    //     {
    //         printf("%s", line);
    //         found++;
    //     }
    // }
    printf("%d", strindex("I sdf cloud af sdfe", "cloud"));
    return 0;
}
