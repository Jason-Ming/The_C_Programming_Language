#include <stdio.h> 
#include "exercise.1.5.h"

/* �� fahr=0��20���� ��300 ʱ���ֱ�
 ��ӡ�����¶��������¶ȶ��ձ� */ 

int exercise_1_5(void) 
{ 
    float fahr, celsius; 
    
    printf(" ==========Fahrenhiet-Celcius Table==========\n");

    for(fahr = 300; fahr >=0; fahr -= 20)
    { 
        celsius = (5.0 / 9.0)*(fahr-32); 
        printf("%3.0f\t%6.1f\n", fahr, celsius); 
    }

    return 0;
} 


