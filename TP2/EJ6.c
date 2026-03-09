// Para resolver este problema, debemos aplicar el concepto de acumulador largo,
// una técnica utilizada nativamente por el hardware de los Procesadores Digitales de Señales (DSP)
// para evitar el catastrófico efecto del overflow en operaciones de acumulación múltiple
// La teoría establece que para sumar de forma segura una cantidad s de sumandos de N bits,
// el acumulador debe tener un tamaño de N+log_2(s) bits
// A partir de los datos del procesador DSP, podemos plantear la siguiente ecuación:
// Tamaño del dato (N): 16 bits.
// Tamaño del acumulador: 40 bits.
// 40 bits=16 bits+log_2(s)
// Si despejamos la variable s (que representa la cantidad de sumandos): 
// log_2(s)=40−16
// log_2(s)=24
// s=2^24
// s=16.777.216
// El DSP puede realizar la suma consecutiva de 16.777.216 sumandos garantizando matemáticamente que no se producirá
// un desbordamiento o overflow.
// A estos 24 bits extra que provee la ALU del procesador (la diferencia entre los 40 bits del acumulador y los 16 bits de las variables)
// se los denomina formalmente bits de guarda
// Su única función es permitir el crecimiento temporal de la parte entera de un número a medida
// que se ejecuta un gran volumen de multiplicaciones y acumulaciones (operaciones MAC), 
// como ocurre típicamente al procesar un filtro digital