#include <stdio.h>
#include "s_draw.h"
#include "6.2.h"

#define XMAX 800
#define YMAX 600

ENUM_RETURN main_6_2(void)
{
    STRU_RECTANGLE screen;
    STRU_POINT middle;

    screen.p1 = s_make_point(0, 0);
    screen.p2 = s_make_point(XMAX, YMAX);

    middle = s_make_point((screen.p1.x + screen.p2.x)/2, (screen.p1.y + screen.p2.y)/2);

    STRU_POINT origin, *pp;
    origin = middle;
    
    pp = &origin;
    //�����.��->���Ǵ������ҽ�ϵ�
    printf("origin is [%d, %d]\n", (*pp).x, (*pp).y);
    printf("origin is [%d, %d]\n", pp->x, pp->y);
    
    return RETURN_SUCCESS;
}


