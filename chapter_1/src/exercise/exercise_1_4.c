#include <stdio.h> 
/* 当 fahr=0，20，… ，300 时，分别
 打印华氏温度与摄氏温度对照表 */ 

int exercise_1_4(void) 
{ 
    float fahr, celsius; 
    float lower, upper, step; 
    
    lower = -100; /* 温度表的下限 */ 
    upper = 200; /* 温度表的上限 */ 
    step = 10; /* 步长 */
    
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



