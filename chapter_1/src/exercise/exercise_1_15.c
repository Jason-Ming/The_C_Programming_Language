#include <stdio.h> 
/* 当 fahr=0，20，… ，300 时，分别
 打印华氏温度与摄氏温度对照表 */ 


void float_format(void)
{
    float f = 0.15625;
    printf("0x%x\n", *(int*)&f);
}

void exercise_1_15_version_1(void)
{
    int fahr, celsius; 
    int lower, upper, step; 
    
    lower = 0; /* 温度表的下限 */ 
    upper = 300; /* 温度表的上限 */ 
    step = 20; /* 步长 */
    
    fahr = lower; 
    
    while (fahr <= upper) 
    { 
        celsius = 5 * (fahr-32) / 9; 
        printf("%d\t%d\n", fahr, celsius); 
        fahr = fahr + step; 
    }
}

float FtoC(float x)
{
    return (5.0 / 9.0)*(x-32); 
}

void exercise_1_15_version_2(void)
{    
    float fahr, celsius; 
    float lower, upper, step; 
    
    lower = 0; /* 温度表的下限 */ 
    upper = 300; /* 温度表的上限 */ 
    step = 20; /* 步长 */
    
    fahr = lower; 

    printf(" ==========Fahrenhiet-Celcius Table==========\n");
    
    while (fahr <= upper) 
    { 
        celsius = FtoC(fahr);
        printf("%3.0f\t%6.1f\n", fahr, celsius); 
        fahr = fahr + step; 
    }

}

int exercise_1_15(void) 
{ 
    exercise_1_15_version_2();
    return 0;
} 


