% -------------------------------------------------------------
% Punto 2: Resolver Sistema de Ecuaciones Lineales 10x10
% -------------------------------------------------------------

% 1. Definición de la matriz A (10x10) de la guía
A = [
    2, 1, 0, 3, 2, 1, 0, 2, 1, 4;
    1, 3, 2, 0, 1, 4, 2, 1, 0, 2;
    0, 2, 4, 1, 3, 0, 1, 2, 4, 1;
    3, 0, 1, 5, 2, 1, 3, 0, 2, 1;
    2, 1, 3, 2, 6, 2, 1, 4, 0, 3;
    1, 4, 0, 1, 2, 5, 2, 1, 3, 0;
    0, 2, 1, 3, 1, 2, 4, 0, 2, 1;
    2, 1, 2, 0, 4, 1, 0, 5, 3, 2;
    1, 0, 4, 2, 0, 3, 2, 3, 6, 1;
    4, 2, 1, 1, 3, 0, 1, 2, 1, 5
];

% Vector b (términos independientes: vector unitario 10x1)
b = ones(10, 1);

fprintf('=== NÚMERO DE CONDICIÓN ===\n');
fprintf('cond(A) = %.4f\n\n', cond(A));

% --- 1. ELIMINACIÓN DE GAUSS (Operador Barra Invertida) ---
tic;
x_gauss = A \ b;
t_gauss = toc;
res_gauss = norm(A * x_gauss - b);

% --- 2. FACTORIZACIÓN LU (PA = LU con pivoteo parcial) ---
tic;
[L, U, P] = lu(A); % L -- triangular inferior , U -- Triangular superior, P -- matriz de permutacion
y_lu = L \ (P * b);
x_lu = U \ y_lu;
t_lu = toc;
res_lu = norm(A * x_lu - b);

% --- 3. FACTORIZACIÓN QR (A = QR) ---
tic;
[Q, R] = qr(A); % Q -- matriz ortogonal, R -- Triangular superior
x_qr = R \ (Q' * b);
t_qr = toc;
res_qr = norm(A * x_qr - b);

% Resultados de los vectores solución
disp('--- Vector Solución x (Gauss) ---'); disp(x_gauss');
disp('--- Vector Solución x (LU) ---');    disp(x_lu');
disp('--- Vector Solución x (QR) ---');    disp(x_qr');

% Tabla comparativa
fprintf('=== COMPARACIÓN DE RENDIMIENTO ===\n');
fprintf('Método\t\tTiempo (s)\t\tNorma Residuo ||Ax - b||\n');
fprintf('Gauss\t\t%.6e\t%.6e\n', t_gauss, res_gauss);
fprintf('LU\t\t%.6e\t%.6e\n', t_lu, res_lu);
fprintf('QR\t\t%.6e\t%.6e\n', t_qr, res_qr);
