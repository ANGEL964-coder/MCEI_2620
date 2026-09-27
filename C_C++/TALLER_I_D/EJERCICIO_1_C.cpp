#include <iostream>
#include <cmath>
#include <iomanip>
#include <gsl/gsl_integration.h>

// 1. Definición de la función matemática con la firma requerida por GSL
double f_integrand(double x, void * params) {
    return exp(-0.4 * x) * (1.0 + 0.5 * sin(3.0 * x));
}

// 2. Implementación explícita de la regla compuesta del trapecio
double trapecio_explicito(double a, double b, int n) {
    double h = (b - a) / n;
    double suma = 0.5 * (f_integrand(a, nullptr) + f_integrand(b, nullptr));
    
    for (int i = 1; i < n; ++i) {
        double xi = a + i * h;
        suma += f_integrand(xi, nullptr);
    }
    return suma * h;
}

int main() {
    double a = 0.0, b = 8.0;
    
    // --- CÁLCULO CON GSL (Cuadratura Adaptativa Gauss-Kronrod) ---
    int limit = 1000; // Límite de subdivisiones
    gsl_integration_workspace * workspace = gsl_integration_workspace_alloc(limit);
    
    double result, error;
    double epsabs = 1e-7; // Tolerancia de error absoluta
    double epsrel = 1e-7; // Tolerancia de error relativa
    
    gsl_function F;
    F.function = &f_integrand;
    F.params = nullptr;
    
    // key define la regla de integración (p. ej., 6 para Gauss-Kronrod de 61 puntos)
    int key = 6; 
    
    // Llamada a la interfaz central para un intervalo finito
    gsl_integration_qag(&F, a, b, epsabs, epsrel, limit, key, workspace, &result, &error);
    
    std::cout << std::setprecision(10);
    std::cout << "--- Integración con GSL (gsl_integration_qag) ---\n";
    std::cout << "Resultado:           " << result << "\n";
    std::cout << "Error estimado:      " << error << "\n";
    std::cout << "Tolerancia absoluta: " << epsabs << "\n";
    std::cout << "Tolerancia relativa: " << epsrel << "\n\n";
    
    gsl_integration_workspace_free(workspace);
    
    // --- CÁLCULO CON TRAPECIO EXPLÍCITO ---
    int n = 100; // Nodos de discretización
    double I_trap = trapecio_explicito(a, b, n);
    
    std::cout << "--- Integración explícita (Regla del Trapecio, n=" << n << ") ---\n";
    std::cout << "Resultado:           " << I_trap << "\n";
    
    return 0;
}