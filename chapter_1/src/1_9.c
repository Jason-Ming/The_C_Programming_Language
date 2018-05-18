#include <stdio.h>
#include <assert.h>

#include "s_defines.h"

//these lines is for test:
//this line's length is 100: 
/*
123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789
*/

#define MAX_LINE_BUFFER 100 //maximum input line length

/* read a line into line, return length */
PRIVATE int getline(FILE *fp, char line[], int maxline)
{
    int c;
    int i;

    //这个条件隐含当i < maxline-1时采取下一个字符到c，否则c就是上一个字符，即当i是99时，c还是上一个字符，不是回车
    for(i = 0; i < maxline-1 && (c = fgetc(fp)) != EOF && c != '\n'; ++i)
    {
        line[i] = c;
    }

    if(c == '\n')
    {
        line[i] = c;
        ++i;
    }

    line[i] = '\0';

    return i;
}

/* copy 'from' to 'to'; assume to is big enough */
PRIVATE void copy(char to[], char from[])
{
    int i;
    i = 0;

    while((to[i] = from[i]) != '\0')
    {
        ++i;
    }
    
}

//print the longest input line
int main(int argc, char **argv)
{
    int len; //current line length
    int max; //maximum length seen so far
    
    char line[MAX_LINE_BUFFER]; //current input line
    char longest[MAX_LINE_BUFFER]; //longest line saved here

    max = 0;

    assert(argc == 2);
    assert(argv[1] != NULL);

    FILE *fp = fopen(argv[1], "r");
    assert(fp != NULL);
    
    while((len = getline(fp, line, MAX_LINE_BUFFER)) > 0)
    {
        if(len > max )
        {
            max = len;
            copy(longest, line);
        }
    }

    if(max > 0) //here was a line
    {
        printf("%d\n%s\n", max, longest);
    }

    fclose(fp);
    
    return 0;
}

