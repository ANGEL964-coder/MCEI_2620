% Cargar datos
datos = csvread('datos_sensor.csv', 1, 0);
x = datos(:, 1); y = datos(:, 2);
h = x(2) - x(1);

% Aproximación 1: Diferencia hacia adelante (Forward)
% diff(y) calcula y(i+1) - y(i)
df_forward = diff(y) / h;
x_forward = x(1:end-1); % Se pierde el último punto

% Aproximación 2: Diferencia central (Central)
df_central = (y(3:end) - y(1:end-2)) / (2*h);
x_central = x(2:end-1); % Se pierden el primer y último punto

plot(x_central, df_central, 'r', x_forward, df_forward, 'b--');
legend('Central', 'Adelante');
