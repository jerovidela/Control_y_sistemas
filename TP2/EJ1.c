#include <math.h>
#include <stdio.h>
void main(void)
{
signed char a, b, c, d, s1, s2;
a = 127;
b = 127;
c = a + b;
d = a * b;
s1 = (-8) >> 2;
s2 = (-1) >> 5;
printf("c = %d \n", c );
printf("d = %d \n", d );
printf("s1 = %d \n", s1 );
printf("s2 = %d \n", s2 );
}

// 1. 
// Matemáticamente, los valores resultantes no son correctos. Esto ocurre debido a un fenómeno llamado overflow (desbordamiento)
// En el lenguaje C, una variable declarada como signed char (entero de 8 bits) tiene un rango de representación limitado desde -128 hasta 127
// Para la variable c (127 + 127 = 254), sumar dos números de N bits puede producir un resultado de hasta N + 1 bits
// Como 254 supera el límite de 127, ocurre un overflow que produce una "caída en escalera" (rollover),
// y el resultado será un número negativo muy distinto al esperado
// Para la variable d (127 * 127 = 16129), multiplicar dos números de N bits puede producir un resultado que ocupa hasta 2N bits
// Nuevamente, el valor excede por mucho el límite de 8 bits, resultando en un valor erróneo.
// 2.
// Usar un acumulador largo:
// La solución más simple es utilizar una variable para el resultado que sea más larga (tenga más bits) que los sumandos o factores
// Para que la suma de a + b sea correcta, se necesitaría un acumulador de al menos 9 bits (N + 1)
// Para la multiplicación a * b, el resultado necesitaría una variable de 16 bits (2N)
// En código, esto se lograría declarando c y d como un entero más grande, por ejemplo int16_t o short
// Utilizar saturación:
// Esta técnica consiste en implementar una función que evalúe si el valor supera el máximo (127).
// De ser así, se asigna el valor máximo posible en lugar de dejar que el sistema colapse de un valor positivo a uno negativo (discontinuidad).
// Aunque la saturación introduce una no-linealidad, evita resultados catastróficos e incoherentes
// 3.
// Sí, los valores resultantes son conceptualmente correctos.
// La operación >> realiza un desplazamiento a la derecha, que computacionalmente equivale a realizar divisiones sucesivas por 2
// Como s1 y s2 provienen de números negativos almacenados en complemento a 2,
// el compilador realiza lo que se conoce como un desplazamiento aritmético (a diferencia del lógico)
// En el caso de s1 = (-8) >> 2, se divide -8 entre 4, arrojando correctamente -2 manteniendo el signo.
// En el caso de s2 = (-1) >> 5, al desplazar los bits preservando el signo (es decir, rellenando con unos a la izquierda),
// el número mantendrá su valor de -1.