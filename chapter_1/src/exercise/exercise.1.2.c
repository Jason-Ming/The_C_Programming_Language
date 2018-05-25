#include <stdio.h>
#include "exercise.1.2.h"

int exercise_1_2(void)
{
    printf("Audible or visual alert. \a\n");
    printf("Form feed \f\n");
    printf("This escape, \r, moves the active position to the initial position of current line. \n");
    printf("Vertical tab \v is tricky, as its behaviour is unspecified under certain conditions.\n");
    return 0;
}

