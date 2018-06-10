#include <stdio.h>
#include "s_mem.h"

#include "2.3.h"
int main_2_3(void)
{
    int i = 123;
    i = 0123;
    i = 0x3f;
    DISPLAY_VAR_MEM_MULTI_LINES(i);
    
    unsigned int ui = 123u;
    ui = 123U;
    ui = 0123U;
    ui = 0x3fU;
    DISPLAY_VAR_MEM_MULTI_LINES(ui);

    long int li = 123L;
    li = 123l;
    li = 0123l;
    li = 0x3fl;
    DISPLAY_VAR_MEM_MULTI_LINES(li);

    unsigned long int uli = 123ul;
    uli = 123Ul;
    uli =123uL;
    uli = 0123UL;
    uli = 0x123UL;
    DISPLAY_VAR_MEM_MULTI_LINES(uli);

    long long int lli = 123ll;
    lli = 123LL;
    lli = 0123LL;
    lli = 0x3fLL;
    DISPLAY_VAR_MEM_MULTI_LINES(lli);

    unsigned long long int ulli = 123ull;
    ulli = 123ULL;
    ulli = 0123ULL;
    ulli = 0x3fULL;
    DISPLAY_VAR_MEM_MULTI_LINES(ulli);

    float f = 123.4f;
    f = 123.4F;
    f = 123.4e-3f;
    f = 123.4E-3F;
    f = 123.4e-3F;
    DISPLAY_VAR_MEM_MULTI_LINES(f);

    double d = 123.4;
    d = 123.4e-3;
    d = 123.4E-3;
    DISPLAY_VAR_MEM_MULTI_LINES(d);

    long double ld = 123.4l;
    ld = 123.4L;
    ld = 123.4e-3L;
    ld = 123.4e-3l;
    DISPLAY_VAR_MEM_MULTI_LINES(ld);

    char c = 'x';
    c = '\0';
    c = '\012';
    c = '\x12';
    DISPLAY_VAR_MEM_MULTI_LINES(c);

    char *cp = "I am a string";
    cp = "";
    cp = "hello," " world";

    DISPLAY_VAR_MEM_MULTI_LINES(cp);

    char ca[] = "I am a string";

    DISPLAY_VAR_MEM_MULTI_LINES(ca);

    return 0;
}


