#include <stdio.h> 
/* 当 fahr=0，20，… ，300 时，分别
 打印华氏温度与摄氏温度对照表 */ 

#define LOWER 0 /* Lower limit of table */
#define UPPER 300 /* upper limit of table */
#define STEP 20 /* step size */

main() 
{ 
    float fahr, celsius; 
    
    printf(" ==========Fahrenhiet-Celcius Table==========\n");

    for(fahr = LOWER; fahr <= UPPER; fahr += STEP)
    { 
        celsius = (5.0 / 9.0)*(fahr-32); 
        printf("%3.0f\t%6.1f\n", fahr, celsius); 
    }

} 


