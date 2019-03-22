#include <stdio.h>
#include "s_draw.h"
#include "6.1.h"

ENUM_RETURN main_6_1(void)
{
    STRU_POINT pt1 = s_make_point(320, 200);
    printf("point: [%d, %d]\n", pt1.x, pt1.y);

    STRU_POINT pt2 = s_make_point(20, 00);

    _SD dist = s_dist_of_points(pt1, pt2);
    printf("distance of points: %lf\n", dist);
    
    return RETURN_SUCCESS;
}

