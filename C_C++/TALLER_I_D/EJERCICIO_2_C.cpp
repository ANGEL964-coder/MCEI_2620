#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_spline.h> // Necesario para la interpolación

// Estructura para encapsular los datos para la función de callback de GSL
struct DatosInterpolados {
    gsl_spline *spline;
    gsl_interp_accel *acc;
};

// Función de callback que evalúa el spline en un punto x
double f_interpolada(double x, void *params) {
    DatosInterpolados *datos = static_cast<DatosInterpolados*>(params);
    return gsl_spline_eval(datos->spline, x, datos->acc);
}

int main() {
    std::vector<double> x, y;
    std::ifstream archivo("datos_sensor.csv");
    std::string linea;

    // 1. Leer el archivo CSV
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir datos_sensor.csv" << std::endl;
        return 1;
    }


    std::getline(archivo, linea); 

    // Extraer datos 
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string valor_x, valor_y;
        
        if (std::getline(ss, valor_x, ',') && std::getline(ss, valor_y, ',')) {
            x.push_back(std::stod(valor_x));
            y.push_back(std::stod(valor_y));
        }
    }
    archivo.close();

    int N = x.size();
    if (N < 2) {
        std::cerr << "Datos insuficientes." << std::endl;
        return 1;
    }

    // 2. Primera estrategia: Implementación explícita del trapecio
    double h = x[1] - x[0]; 
    double I_trap_discreto = 0.5 * (y[0] + y[N - 1]);
    
    for (int i = 1; i < N - 1; ++i) {
        I_trap_discreto += y[i];
    }
    I_trap_discreto *= h;

    std::cout << "--- Integración con datos discretos (C/C++) ---\n";
    std::cout << "Integral Trapecio Explicito: " << I_trap_discreto << "\n\n";

    // 3. Segunda estrategia: Representación interpolada con GSL
    // Inicializar el acelerador y el objeto spline
    gsl_interp_accel *acc = gsl_interp_accel_alloc();
    gsl_spline *spline = gsl_spline_alloc(gsl_interp_cspline, N);
    
    // Inicializar el spline con nuestros datos
    gsl_spline_init(spline, x.data(), y.data(), N);

    // Preparar los parámetros para la integración adaptativa de GSL
    DatosInterpolados parametros_interpolacion = {spline, acc};
    
    gsl_function F;
    F.function = &f_interpolada;
    F.params = &parametros_interpolacion;

    double result_gsl, error_gsl;
    int limit = 1000;
    gsl_integration_workspace *workspace = gsl_integration_workspace_alloc(limit);
    
    // Integramos desde el primer x hasta el último x
    gsl_integration_qag(&F, x.front(), x.back(), 1e-7, 1e-7, limit, 6, workspace, &result_gsl, &error_gsl);

    std::cout << "--- Integración mediante Interpolación Cúbica (GSL) ---\n";
    std::cout << "Integral GSL (Spline):       " << result_gsl << "\n";
    std::cout << "Error estimado:              " << error_gsl << "\n";

    // Liberar memoria
    gsl_integration_workspace_free(workspace);
    gsl_spline_free(spline);
    gsl_interp_accel_free(acc);

    return 0;
}