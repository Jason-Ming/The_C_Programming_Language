#include <stdio.h> 
/* �� fahr=0��20���� ��300 ʱ���ֱ�
 ��ӡ�����¶��������¶ȶ��ձ� */ 

int exercise_1_3(void) 
{ 
    float fahr, celsius; 
    float lower, upper, step; 
    
    lower = 0; /* �¶ȱ������ */ 
    upper = 300; /* �¶ȱ������ */ 
    step = 20; /* ���� */
    
    fahr = lower; 

    printf(" ==========Fahrenhiet-Celcius Table==========\n");
    
    while (fahr <= upper) 
    { 
        celsius = (5.0 / 9.0)*(fahr-32.0); 
        printf("%3.0f\t%6.1f\n", fahr, celsius); 
        fahr = fahr + step; 
    }

    return 0;
} 


