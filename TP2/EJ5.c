// 1 al 4. Código en C: Implementación de la operación MAC
// La operación MAC es la operación fundamental en los Procesadores Digitales de Señales (DSP) para implementar algoritmos como la convolución o el filtrado
// . En el código a continuación, se convierten los vectores de punto flotante a punto fijo (Q21.10) multiplicándolos por el factor de escala 2 
// 10
//  =1024
// . Luego, calculamos las operaciones utilizando los dos enfoques solicitados y el valor ideal usando double.
#include <stdio.h>
#include <stdint.h>

#define n 10 // Número de bits fraccionarios para el formato Q21.10

// Función para redondeo por truncación
int32_t truncation(int64_t X) {
    return (int32_t)(X >> n);
}

int main(void) {
    // 1. Vectores originales en punto flotante
    float X_f[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    float Y_f[5] = {6.6, 7.7, 8.8, 9.9, 10.10};
    
    // Vectores en formato double para máxima precisión
    double X_d[5] = {1.1, 2.2, 3.3, 4.4, 5.5};
    double Y_d[5] = {6.6, 7.7, 8.8, 9.9, 10.10};

    // 2. Vectores en punto fijo Q21.10
    int32_t A[5], B[5];
    for(int i = 0; i < 5; i++) {
        A[i] = (int32_t)(X_f[i] * (1 << n));
        B[i] = (int32_t)(Y_f[i] * (1 << n));
    }

    // Acumuladores
    int32_t acum_32a = 0;
    int64_t acum_64  = 0;
    int32_t acum_32b = 0;
    double  acum_db  = 0.0;

    // 3 y 4. Operación MAC
    for(int i = 0; i < 5; i++) {
        // Enfoque 1: Truncar CADA multiplicación antes de sumar
        acum_32a += (int32_t) (truncation( (int64_t)A[i] * (int64_t)B[i] ));
        
        // Enfoque 2: Acumular con todos los bits (64 bits) temporalmente
        acum_64 += (int64_t)A[i] * (int64_t)B[i];
        
        // Operación ideal en Double
        acum_db += X_d[i] * Y_d[i];
    }
    
    // Finalización del Enfoque 2: Truncar sólo al final, luego de sumar todo
    acum_32b = truncation(acum_64); 

    // Imprimir los resultados recuperados a formato flotante para comparar
    printf("Resultados obtenidos:\n");
    printf("1. acum_32a (Truncado temprano): %f\n", (double)acum_32a / (1 << n));
    printf("2. acum_32b (Truncado final)  : %f\n", (double)acum_32b / (1 << n));
    printf("3. acum_db  (Formato double)  : %f\n", acum_db);

    return 0;
}
// 5. Comparación de los valores de acum_32a, acum_32b y acum_db
// Al compilar y ejecutar el programa anterior, se obtiene una salida similar a la siguiente:
// 1. acum_32a (Truncado temprano): ≈152.324219
// 2. acum_32b (Truncado final): ≈152.326172
// 3. acum_db (Formato double): ≈152.350000
// Análisis de los resultados:
// El resultado en double (acum_db): Actúa como el valor de referencia o "valor real" de la operación, ya que el estándar IEEE-754 de 64 bits posee una inmensa precisión (53 bits para la mantisa), reduciendo drásticamente los errores de cuantización y problemas de pérdida de resolución observados en otros formatos
// . Matemáticamente la sumatoria real de los productos es exactamente 152.35.
// Diferencia entre acum_32a y acum_32b: El resultado acum_32b es más preciso que acum_32a y se acerca más al valor ideal en double.
// En el Enfoque 1 (acum_32a), al multiplicar se generan 20 bits fraccionarios, pero truncamos a 10 bits en cada iteración del bucle antes de acumular. Esto significa que descartamos información valiosa 5 veces, acumulando el error de cuantización por redondeo en cada paso.
// En el Enfoque 2 (acum_32b), se utiliza un acumulador largo de 64 bits acum_64 a lo largo de todo el bucle for, preservando intactos los 20 bits fraccionarios de cada producto
// . El error de truncamiento se introduce una única vez al finalizar el ciclo. Este enfoque es un reflejo de cómo operan internamente los verdaderos Procesadores Digitales de Señales (DSP), los cuales cuentan con acumuladores con bits de guarda en su hardware para evitar el overflow y el underflow durante este tipo de operaciones consecutivas
// .