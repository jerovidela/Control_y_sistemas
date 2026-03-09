// la conversión entre punto flotante y punto fijo se basa en el concepto de factor de escala, 
// implementado computacionalmente mediante desplazamientos de bits o multiplicaciones por potencias de 2
// .
// Para que el código sea versátil con distintos formatos Qm.n, las funciones pueden recibir como parámetro el número de bits fraccionarios n. Como los formatos Q23.8 y Q21.10 suman un total de 32 bits (incluyendo 1 bit de signo)
// , utilizaremos enteros de 32 bits (int32_t).

#include <stdio.h>
#include <stdint.h>

// 1. Función para pasar de punto fijo a punto flotante
float fx2fp(int32_t X, int n) {
    // Se divide el entero por 2^n usando desplazamiento de bits
    return (float)X / (1 << n);
}

// 2. Función para pasar de punto flotante a punto fijo
int32_t fp2fx(float x, int n) {
    // Se multiplica el flotante por 2^n y se hace casting a entero
    return (int32_t)(x * (1 << n));
}

int main(void) {
    float original = 2.4515;
    
    // Prueba para formato Q23.8 (n = 8)
    int n1 = 8;
    int32_t X1 = fp2fx(original, n1);
    float b1 = fx2fp(X1, n1);
    
    // Prueba para formato Q21.10 (n = 10)
    int n2 = 10;
    int32_t X2 = fp2fx(original, n2);
    float b2 = fx2fp(X2, n2);
    
    printf("Valor original: %f\n\n", original);
    
    printf("Formato Q23.8 (n=8):\n");
    printf("  Punto fijo (entero): %d\n", X1);
    printf("  Valor recuperado (b): %f\n", b1);
    
    printf("\nFormato Q21.10 (n=10):\n");
    printf("  Punto fijo (entero): %d\n", X2);
    printf("  Valor recuperado (b): %f\n", b2);

    return 0;
}

// Análisis de la comparación La precisión de un formato de punto fijo está directamente determinada por el número de bits asignados a la parte fraccionaria, siendo igual a 2 
// −n
 
// .
// Al correr el programa anterior, se observarían los siguientes resultados:
// En Q23.8 (n = 8): El factor de escala es 2 
// 8
//  =256. Al multiplicar 2.4515×256 obtenemos 627.584. El casting a entero trunca los decimales, almacenando el valor 627 en memoria
// . Al recuperarlo, calculamos 627/256, lo que resulta en b = 2.44921875. La precisión máxima del sistema es de 2 
// −8
//  ≈0.0039, lo que explica el error respecto a 2.4515.
// En Q21.10 (n = 10): El factor de escala es 2 
// 10
//  =1024. La multiplicación arroja 2510.336, que al truncarse se guarda como 2510
// . Al recuperar el valor (2510/1024), obtenemos b = 2.451171875.
// Conclusión de la comparación: La variable b será más cercana a 2.4515 usando la notación Q21.10. Al ceder 2 bits de la parte entera a favor de la parte fraccionaria (pasando de 8 a 10 bits fraccionarios), aumentas la precisión (que mejora a 2 
// −10
//  ≈0.00097) y reduces el error de cuantización introducido por el truncamiento en la conversión
// .
// ¿Te gustaría que te muestre cómo incorporar una técnica de "redondeo al valor más cercano" en la función de conversión para minimizar este error de cuantización que actualmente se produce por truncamiento?