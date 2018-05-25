#include <stdio.h> 
#include "1.4.h"
#include "s_defines.h"

/* �� fahr=0��20���� ��300 ʱ���ֱ�
 ��ӡ�����¶��������¶ȶ��ձ� */ 

#define LOWER 0 /* Lower limit of table */
#define UPPER 300 /* upper limit of table */
#define STEP 20 /* step size */

int main_1_4(void) 
{ 
    float fahr, celsius; 
    
    printf(" ==========Fahrenhiet-Celcius Table==========\n");

    for(fahr = LOWER; fahr <= UPPER; fahr += STEP)
    { 
        celsius = (5.0 / 9.0)*(fahr-32); 
        printf("%3.0f\t%6.1f\n", fahr, celsius); 
    }
    return RETURN_SUCCESS;
} 


