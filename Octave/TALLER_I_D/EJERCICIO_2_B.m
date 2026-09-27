% 1. Cargar el CSV (saltando la primera fila de encabezados)
datos = csvread('datos_sensor.csv', 1, 0);
x = datos(:, 1);
y = datos(:, 2);

N = length(x);
h = x(2) - x(1); %Paso de 0.2

% 2. Regla del Trapecio
% Octave cuenta con una función nativa vectorizada para esto
I_trap = trapz(x, y);

% 3. Regla de Simpson
I_simp_parcial = 0;
% Simpson 1/3
for i = 1:2:N-2
    I_simp_parcial = I_simp_parcial + (h/3) * (y(i) + 4*y(i+1) + y(i+2));
end

% El subintervalo final (entre el dato 49 y 50) se suma como un trapecio simple
I_ultimo_tramo = (h/2) * (y(N-1) + y(N));
I_simp_total = I_simp_parcial + I_ultimo_tramo;

% Imprimir resultados en consola
fprintf('--- Resultados de Integración Numérica (Datos discretos) ---\n');
fprintf('Integral mediante Trapecio: %f\n', I_trap);
fprintf('Integral mediante Simpson (Ajustado): %f\n', I_simp_total);

% 4. Visualización: Graficar los datos y el área aproximada
figure;
hold on;
% Dibujar el polígono sombreado bajo la curva (Área)
area(x, y, 'FaceColor', [0.8 0.9 1], 'EdgeColor', 'none');

% Superponer las 50 mediciones como marcadores
plot(x, y, 'bo', 'MarkerFaceColor', 'b', 'MarkerSize', 4);

title('Área bajo la curva usando únicamente datos discretos');
xlabel('x');
ylabel('y');
grid on;
hold off;
