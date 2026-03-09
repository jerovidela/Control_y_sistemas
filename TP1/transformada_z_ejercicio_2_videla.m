%[text] # Trabajo Practico 1: Transformada Z - Ejercicio 3
%[text:tableOfContents]{"heading":"Table of Contents"}
%[text] ## Ejercicio 2:
%[text] 1. Considere las transformadas $&dollar&;X\_1(z) = 1 + z^{-1} + 3z^{-2}&dollar&; y &dollar&;X\_2(z) = 1 + 3z^{-2}&dollar&;$.
%[text] 2. Encuentre $&dollar&;x\[n\] = x\_1\[n\] \* x\_2\[n\]&dollar&;$
%[text] 3. Resuelva el problema aplicando la propiedad de la convolución de la transformada Z.
%[text] 4. Use la función conv para multiplicar dos polinomios.
%[text] 5. Implemente la convolución en el dominio del tiempo con la función filter.
%[text] 6. Compare resultados. \
clc
clear
close all
%%
%[text] ### Desarrollo
b1 = [1 1 3];
b2 = [1 0 3];
by = conv(b1, b2) %[output:03f84664]
x = [1 0 3 0 0 ];
y_filter = filter(b1,1,x) %[output:3e0d9eda]
%%
%[text] ### Conclusiones
%[text] 1. En este ejercicio concluimos que la propiedad que de la convolucion en el dominio del tiempo es igual al producto de los polinomios en el dominio de Z. \

%[appendix]{"version":"1.0"}
%---
%[metadata:view]
%   data: {"layout":"inline","rightPanelPercent":54.3}
%---
%[output:03f84664]
%   data: {"dataType":"matrix","outputData":{"columns":5,"name":"by","rows":1,"type":"double","value":[["1","1","6","3","9"]]}}
%---
%[output:3e0d9eda]
%   data: {"dataType":"matrix","outputData":{"columns":5,"name":"y_filter","rows":1,"type":"double","value":[["1","1","6","3","9"]]}}
%---
