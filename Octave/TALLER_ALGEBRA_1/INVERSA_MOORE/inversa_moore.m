% Matriz original A
A = [1, 0, 2;
     2, -1, 5;
     0, 1, -1;
     1, 3, -1];

A_pinv = pinv(A); %Inversa de Moorse

disp("Inversa de Moore-Penrose (A+):");
disp(A_pinv);

tol = 1e-10; % Tolerancia para errores de precisión

prop1 = norm(A * A_pinv * A - A) < tol;
prop2 = norm(A_pinv * A * A_pinv - A_pinv) < tol;
prop3 = norm((A * A_pinv)' - (A * A_pinv)) < tol;
prop4 = norm((A_pinv * A)' - (A_pinv * A)) < tol;

disp("¿Cumple las propiedades? (1 = Sí, 0 = No):");
fprintf("1. A A+ A = A: %d\n", prop1);
fprintf("2. A+ A A+ = A+: %d\n", prop2);
fprintf("3. (A A+)^T = A A+: %d\n", prop3);
fprintf("4. (A+ A)^T = A+ A: %d\n", prop4);
