/* This program prompts for input, and then captures a character
* from the keyboard. If EOF is signalled (typically through a
* control-D or control-Z character, though not necessarily),
* the program prints 0. Otherwise, it prints 1.
*
* If your input stream is buffered (and it probably is), then
* you will need to press the ENTER key before the program will
* respond.
*/
#include <stdio.h>
int exercise_1_6(void)
{
    printf("Press a key. Enter would be nice :-)\n\n");
    printf("The expression getchar() != EOF evaluates %d\n", getchar() != EOF);

    return 0;
}
