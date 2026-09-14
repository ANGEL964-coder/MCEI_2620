% Matriz mal condicionada
A = [
    3, 2, 0, 1, 4, 1, 2, 0, 1, 5;
    3, 2, 0, 1, 4, 1, 2, 0, 1, 5.000001;
    1, 4, 2, 0, 1, 3, 0, 2, 4, 1;
    0, 1, 5, 2, 1, 0, 3, 1, 0, 2;
    2, 0, 1, 4, 2, 1, 0, 5, 1, 3;
    1, 3, 0, 1, 5, 2, 1, 0, 2, 0;
    0, 2, 4, 0, 1, 3, 2, 1, 0, 4;
    4, 1, 0, 3, 0, 1, 5, 2, 1, 1;
    1, 0, 3, 1, 2, 0, 1, 4, 5, 2;
    2, 5, 1, 0, 3, 2, 0, 1, 2, 3
];

I = eye(10); % Matriz Identidad

% --- 1. Método Directo ---
inv_directa = inv(A);
err_directa = norm(A * inv_directa - I);

% --- 2. Descomposición QR ---
[Q, R] = qr(A);
inv_qr = inv(R) * Q';
err_qr = norm(A * inv_qr - I);

% --- 3. Descomposición SVD ---
[U, S, V] = svd(A);
% Invertir los valores singulares (diagonal de S)
S_inv = diag(1 ./ diag(S));
inv_svd = V * S_inv * U';
err_svd = norm(A * inv_svd - I);

% --- Impresión de Resultados ---
fprintf('=== ERROR RESIDUAL ||A * A^-1 - I|| ===\n');
fprintf('Método Directo : %e\n', err_directa);
fprintf('Método QR      : %e\n', err_qr);
fprintf('Método SVD     : %e\n', err_svd);
