
#include <stdio.h>
#include <time.h>

#include "s_alg.h"

#include "s_type.h"
#include "s_text.h"

#include "exercise.3.2.h"


int exercise_3_2(void)
{
    _S8 t[] = "\aHello,\n\tWorld! Mistakee\b was \"Extra'e'\"!\n";
    _S8 s1[64];
    _S8 s2[64];

    s_escape(t, s1, 64);
    s_unescape(s1, s2, 64);
    printf("Original string: \n%s\n", t);
    printf("Escaped string: \n%s\n", s1);
    printf("Unescaped string: \n%s\n", s2);
    return 0;
}



