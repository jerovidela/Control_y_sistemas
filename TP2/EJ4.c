// Para implementar correctamente la aritmética de saturación, es un requisito indispensable operar primero con un acumulador más largo
// (en este caso, de 64 bits) antes de aplicar los límites
// Esto permite que la suma retenga su valor real temporalmente para luego poder compararlo contra INT_MAX e INT_MIN y 
// decidir si es necesario saturar el resultado, previniendo así la catastrófica "caída en escalera" o rollover
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

int32_t saturation(int32_t a, int32_t b) {
    int64_t acumulador = (int64_t)a + (int64_t)b;
    if (acumulador > INT_MAX) {
        return INT_MAX;
    } else if (acumulador < INT_MIN) {
        return INT_MIN;
    } else {
        return (int32_t)acumulador;
    }
}

int main(void) {
    int32_t a, b, res_saturado, res_normal;

    printf("Límites definidos en limits.h:\n");
    printf("INT_MAX = %d\n", INT_MAX);
    printf("INT_MIN = %d\n\n", INT_MIN);

    // --- Caso 1: Suma normal (Sin overflow) ---
    a = 1500000;
    b = 2500000;
    res_saturado = saturation(a, b);
    printf("Caso 1: Suma normal (%d + %d)\n", a, b);
    printf("Resultado: %d\n\n", res_saturado);

    // --- Caso 2: Overflow positivo ---
    a = INT_MAX - 100;
    b = 500;
    res_saturado = saturation(a, b);
    res_normal = a + b;
    printf("Caso 2: Overflow Positivo (%d + %d)\n", a, b);
    printf("Suma sin saturacion (Rollover): %d\n", res_normal);
    printf("Suma con saturacion:            %d\n\n", res_saturado);

    // --- Caso 3: Overflow negativo ---
    a = INT_MIN + 100;
    b = -500;
    res_saturado = saturation(a, b);
    res_normal = a + b;
    printf("Caso 3: Overflow Negativo (%d + %d)\n", a, b);
    printf("Suma sin saturacion (Rollover): %d\n", res_normal);
    printf("Suma con saturacion:            %d\n", res_saturado);

    return 0;
}
// Al ejecutar el programa, se pondrá a prueba el comportamiento de la función frente a distintos escenarios:
// Caso 1 (Normal): Suma dos números cuyos valores están dentro de los márgenes soportados.
// El acumulador simplemente se convierte de nuevo a 32 bits, comportándose de manera completamente lineal
// Caso 2 (Overflow Positivo): La suma supera el máximo valor posible (INT_MAX, que típicamente es 2147483647 para enteros de 32 bits)
// Sin saturación, el programa experimentaría un rollover, arrojando un gran número negativo
// Con la función saturation(), el resultado se "estanca" correctamente en 2147483647
// Caso 3 (Overflow Negativo): La suma excede el límite inferior (INT_MIN, típicamente -2147483648)
// Sin saturación, arrojaría un gran número positivo debido a la discontinuidad
// Con saturación, la función atrapa esto y devuelve -2147483648 de forma controlada