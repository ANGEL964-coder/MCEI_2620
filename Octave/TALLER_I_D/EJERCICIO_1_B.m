% Definición de la función en forma de vector
f = @(x) exp(-0.4.*x) .* (1 + 0.5.*sin(3.*x));


a = 0;
b = 8;
referencia = 2.55982450830206; % Valor analítico calculado para comparar con el resultado

% Vector con los valores de n solicitados
n_vals = [10, 20, 50, 100, 500, 1000];

fprintf('--- Regla Compuesta del Trapecio ---\n');
fprintf('n\t Integral\t Error Absoluto\t Tiempo (s)\n');
fprintf('------------------------------------------------------------\n');

% Bucle para evaluar cada n
for i = 1:length(n_vals)
    n = n_vals(i);

    tic; % Iniciar cronómetro

    h = (b - a) / n;
    x = linspace(a, b, n + 1);
    y = f(x);

    % Implementación vectorizada del trapecio
    % Suma los extremos divididos por 2, más la suma de los puntos interiores
    I_trap = h * ( (y(1) + y(end))/2 + sum(y(2:end-1)) );

    t = toc; % Detener cronómetro

    error_trap = abs(referencia - I_trap);

    % Imprimir fila de la tabla
    fprintf('%d\t %.8f\t %.8e\t %.6f\n', n, I_trap, error_trap, t);
end

fprintf('\n--- Segunda Aproximación: Función Nativa de Octave ---\n');
tic;
% 'integral' usa cuadratura adaptativa global por defecto en Octave
I_oct = integral(f, a, b);
t_oct = toc;

error_oct = abs(referencia - I_oct);
fprintf('Integral: %.8f | Error: %.8e | Tiempo: %.6f s\n', I_oct, error_oct, t_oct);
