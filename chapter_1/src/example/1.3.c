#include <stdio.h> 
#include "1.3.h"

/* �� fahr=0��20���� ��300 ʱ���ֱ�
 ��ӡ�����¶��������¶ȶ��ձ� */ 

ENUM_RETURN main_1_3(void) 
{ 
    float fahr, celsius; 
    
    printf(" ==========Fahrenhiet-Celcius Table==========\n");

    for(fahr = 0; fahr <= 300; fahr += 20)
    { 
        celsius = (5.0 / 9.0)*(fahr-32); 
        printf("%3.0f\t%6.1f\n", fahr, celsius); 
    }

    return RETURN_SUCCESS;
} 

