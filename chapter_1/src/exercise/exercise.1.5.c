#include <stdio.h> 
#include "exercise.1.5.h"

/* 当 fahr=0，20，… ，300 时，分别
 打印华氏温度与摄氏温度对照表 */ 

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


