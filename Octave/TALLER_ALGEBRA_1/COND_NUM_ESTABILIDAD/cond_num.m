clc; clear;

% 1. Definición de la matriz original A_orig (10x10)
% La Fila 2 es casi idéntica a la Fila 1 (diferencia de 0.000001 en el último elemento)
A_orig = [
    3, 2, 0, 1, 4, 1, 2, 0, 1, 5;
    3, 2, 0, 1, 4, 1, 2, 0, 1, 5.000001; % Fila casi dependiente (provoca cond(A) alto)
    1, 4, 2, 0, 1, 3, 0, 2, 4, 1;
    0, 1, 5, 2, 1, 0, 3, 1, 0, 2;
    2, 0, 1, 4, 2, 1, 0, 5, 1, 3;
    1, 3, 0, 1, 5, 2, 1, 0, 2, 0;
    0, 2, 4, 0, 1, 3, 2, 1, 0, 4;
    4, 1, 0, 3, 0, 1, 5, 2, 1, 1;
    1, 0, 3, 1, 2, 0, 1, 4, 5, 2;
    2, 5, 1, 0, 3, 2, 0, 1, 2, 3
];


% 2. Vector b de entrada
b = [1; 1; 1; 1; 1; 1; 1; 1; 1; 1];

% 3. Matriz perturbada A_pert (se modifica A(1,3) de 0 a 0.001)
A_pert = A_orig;
A_pert(1, 3) = 0.001;


% 4. Resolución de sistemas
x = A_orig \ b;       % Solución no perturbada
x_pert = A_pert \ b;  % Solución perturbada

% 5. Cálculo del error relativo entre ambas soluciones
e_x = norm(x_pert - x) / norm(x);

disp('--- Vector Solución x (Original)'); disp(x');
disp('--- Vector Solución x (pertubada)'); disp(x_pert');

% 6. Impresión del resultado
fprintf('=========================================================\n');
fprintf('   ANÁLISIS DE PERTURBACIÓN EN LA MATRIZ A (PUNTO 3)    \n');
fprintf('=========================================================\n');
fprintf('Número de condición cond(A_orig)   : %.6e\n', cond(A_orig));
fprintf('Número de condición cond(A_pert  )   : %.6e\n', cond(A_pert));
fprintf('Error relativo en la solución (e_x): %.6e\n', e_x);
fprintf('---------------------------------------------------------\n');
