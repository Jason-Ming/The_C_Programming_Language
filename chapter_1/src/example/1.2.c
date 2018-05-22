#include <stdio.h> 
#include "1.2.h"
/* �� fahr=0��20���� ��300 ʱ���ֱ�
 ��ӡ�����¶��������¶ȶ��ձ� */ 

void main_1_2_version_1(void)
{
    int fahr, celsius; 
    int lower, upper, step; 
    
    lower = 0; /* �¶ȱ������ */ 
    upper = 300; /* �¶ȱ������ */ 
    step = 20; /* ���� */
    
    fahr = lower; 
    
    while (fahr <= upper) 
    { 
        celsius = 5 * (fahr-32) / 9; 
        printf("%d\t%d\n", fahr, celsius); 
        fahr = fahr + step; 
    }
}

void main_1_2_version_2(void)
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
        celsius = (5.0 / 9.0)*(fahr-32); 
        printf("%3.0f\t%6.1f\n", fahr, celsius); 
        fahr = fahr + step; 
    }

}

ENUM_RETURN main_1_2(void) 
{ 
    main_1_2_version_1();
    
    main_1_2_version_2();
    
    return RETURN_SUCCESS;
} 

