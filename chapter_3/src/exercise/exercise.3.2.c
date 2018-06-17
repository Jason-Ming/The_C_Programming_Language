
#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"

#include "exercise.3.2.h"

#define MAX_ELEMENT 200000
#define MAX_CHAR 256

_U8 s_escape[MAX_CHAR] = {0};
_U8 s_unescape[MAX_CHAR] = {0};

void escape(_U8* s, _U8* t)
{
    s_escape['\\'] = '\\';
    s_escape['\n'] = 'n';
    s_escape['\t'] = 't';
    s_escape['\a'] = 'a';
    s_escape['\b'] = 'b';
    s_escape['\f'] = 'f';
    s_escape['\r'] = 'r';
    s_escape['\v'] = 'v';
    s_escape['\"'] = '"';
    s_escape['\''] = '\'';
    s_escape['\?'] = '?';

    while(*t != '\0')
    {
        switch(*t)
        {
            case '\\':
            case '\a':
            case '\b':
            case '\n':
            case '\t':
            case '\f':
            case '\r':
            case '\v':
            case '\"':
            case '\'':
            case '\?':
            {
                *s++ = '\\';
                *s++ = s_escape[*t++];
                break;
            }
            default:
            {
                *s++ = *t++;
                break;
            }
        }
    }

    /* append \0 */
    *s = *t;
}

void unescape(_U8* s, _U8* t)
{
    /* init all escape charactors */
    s_unescape['\\'] = '\\';
    s_unescape['b'] = '\b';
    s_unescape['n'] = '\n';
    s_unescape['t'] = '\t';
    s_unescape['a'] = '\a';
    s_unescape['b'] = '\b';
    s_unescape['f'] = '\f';
    s_unescape['r'] = '\r';
    s_unescape['v'] = '\v';
    s_unescape['"'] = '\"';
    s_unescape['\''] = '\'';
    s_unescape['?'] = '\?';

    while(*t != '\0')
    {
        if(*t == '\\')
        {
            switch(*t++)
            {
                case '\\':
                case '\a':
                case '\b':
                case '\n':
                case '\t':
                case '\f':
                case '\r':
                case '\v':
                case '\"':
                case '\'':
                case '\?':
                {
                    *s++ = s_unescape[*t++];
                    break;
                }
                default:
                {
                    *s++ = '\\';
                    *s++ = *t++;
                    break;
                }
            }
        }
        else
        {
            *s++ = *t++;
        }
    }

    /* append \0 */
    *s = *t;
}


int exercise_3_2(void)
{
    _U8 t[] = "\aHello,\n\tWorld! Mistakee\b was \"Extra'e'\"!\n";
    _U8 s1[64];
    _U8 s2[64];

    escape(s1, t);
    unescape(s2, s1);
    printf("Original string: \n%s\n", t);
    printf("Escaped string: \n%s\n", s1);
    printf("Unescaped string: \n%s\n", s2);
    return 0;
}



