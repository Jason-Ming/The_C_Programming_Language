#include <stdio.h> 
/* �� fahr=0��20���� ��300 ʱ���ֱ�
 ��ӡ�����¶��������¶ȶ��ձ� */ 

int exercise_1_4(void) 
{ 
    float fahr, celsius; 
    float lower, upper, step; 
    
    lower = -100; /* �¶ȱ������ */ 
    upper = 200; /* �¶ȱ������ */ 
    step = 10; /* ���� */
    
    celsius = lower; 

    printf(" ==========Celcius-Fahrenhiet Table==========\n");
    
    while (celsius <= upper) 
    { 
        fahr = celsius*(9.0/5.0)+32.0;
        printf("%6.0f\t%3.1f\n", celsius, fahr); 
        celsius = celsius + step; 
    }

    return 0;
} 



