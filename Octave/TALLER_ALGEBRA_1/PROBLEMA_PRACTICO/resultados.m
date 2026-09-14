% 1. Cargar datos (saltando la primera fila de encabezados)
data = csvread('datos_convertidor_realista.csv', 1, 0);

V = data(:, 1); % Voltaje
I = data(:, 2); % Corriente
T = data(:, 3); % Temperatura
P = data(:, 4); % Potencia (y)

n = length(P);

% 2. Construir la matriz X y el vector y
% Se añade una columna de unos para el término independiente beta_0
X = [ones(n, 1), V, I, T];
y = P;

% 3. Resolver por mínimos cuadrados
beta = X \ y;

% 4. Calcular residual y Error Cuadrático Medio (MSE)
y_pred = X * beta;
residual = y - y_pred;
mse = mean(residual.^2);

% 5. Calcular número de condición
cond_X = cond(X);

fprintf('=== MODELO LINEAL DEL CONVERTIDOR ===\n');
fprintf('Beta_0 (Interseccion): %.4f\n', beta(1));
fprintf('Beta_1 (Voltaje V)   : %.4f\n', beta(2));
fprintf('Beta_2 (Corriente I) : %.4f\n', beta(3));
fprintf('Beta_3 (Temp T)      : %.4f\n\n', beta(4));

fprintf('Norma del Residual   : %.4f\n', norm(residual));
fprintf('Error Cuad. Medio    : %.4f\n', mse);
fprintf('Condición de X       : %.4f\n', cond_X);
