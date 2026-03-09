// 1 y 2. Funciones de redondeo (Truncación y Valor más cercano)
// Al multiplicar dos números de N bits en formato punto fijo, se produce un resultado que requiere hasta 2N bits, duplicándose también el número de bits de la parte fraccionaria
// . Para el formato Q21.10 (donde n=10 bits fraccionarios), la multiplicación directa de dos variables generará temporalmente un resultado con 20 bits fraccionarios que normalmente se almacena en un acumulador de 64 bits (int64_t).
// Para almacenar este resultado nuevamente en una variable Q21.10 de 32 bits, debemos eliminar 10 bits fraccionarios realizando un desplazamiento aritmético a la derecha (>> 10)
// .
// A continuación se presenta el código en C para implementar ambas soluciones basadas en los esquemas de la bibliografía:
#include <stdio.h>
#include <stdint.h>

// Cantidad de bits fraccionarios para Q21.10
#define n 10

// 1. Función que implemente redondeo por truncación
int32_t truncation(int64_t X) {
    int32_t a;
    // Desplazamiento aritmético a la derecha: recorta los 'n' bits extra
    a = (int32_t) (X >> n); 
    return a;
}

// 2. Función que implemente redondeo al valor más cercano
int32_t rounding(int64_t X) {
    int64_t a;
    // Se suma la mitad de la precisión (2^(n-1)) y luego se trunca
    a = X + (1 << (n - 1)); 
    return truncation(a);
}
// 3. Comparación de los esquemas con el resultado en formato double
// Para ilustrar la diferencia teórica y práctica, podemos incorporar las funciones anteriores en una función main y evaluar una multiplicación que genere bits residuales, por ejemplo, multiplicar 2.45 por 1.15.
int main(void) {
    // 1. Referencia usando formato double (IEEE 754)
    double f1 = 2.45;
    double f2 = 1.15;
    double double_result = f1 * f2;

    // 2. Conversión a punto fijo Q21.10 (Factor de escala: 2^10 = 1024)
    int32_t q1 = (int32_t)(f1 * 1024);
    int32_t q2 = (int32_t)(f2 * 1024);

    // Multiplicación en complemento a 2 (Q21.10 * Q21.10 = Q42.20 temporal)
    int64_t mult_result = (int64_t)q1 * (int64_t)q2; 

    // 3. Aplicación de los esquemas de redondeo
    int32_t res_trunc = truncation(mult_result);
    int32_t res_round = rounding(mult_result);

    // Conversión de vuelta a flotante para visualizar el resultado final
    double final_trunc = (double)res_trunc / 1024.0;
    double final_round = (double)res_round / 1024.0;

    printf("Resultado en double:        %f\n", double_result);
    printf("Resultado con truncamiento: %f\n", final_trunc);
    printf("Resultado con redondeo:     %f\n", final_round);

    return 0;
}
// Análisis de los resultados:
// Formato double (IEEE-754 de 64 bits): Operará como el "valor real" o ideal. Al usar precisión doble, su significando tiene 53 bits (52+1)
// . Por ello, su exactitud relativa no sufrirá del underflow severo del formato Q21.10 y nos dará un valor altamente preciso, prácticamente idéntico al valor matemático real (2.8175).
// Redondeo por truncación: Conceptualmente, esto es un redondeo hacia −∞
// . Al usar X >> n, los bits menos significativos simplemente se descartan (y si son descartados, el valor truncado será levemente menor al valor original). El resultado representará el valor exacto de Q21.10 ubicado justo por debajo del valor real calculado.
// Redondeo al valor más cercano: Al sumar la mitad de la precisión (2 
// n−1
//  ) antes de aplicar el truncamiento, el sistema evalúa indirectamente si los bits descartados superaban la mitad de la resolución disponible
// . Su resultado final estará notablemente más próximo al que entrega el double.