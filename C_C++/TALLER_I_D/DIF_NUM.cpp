#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>

int main() {
    std::vector<double> x, y;
    std::ifstream archivo("datos_sensor.csv");
    std::string linea;

    // 1. Leer el archivo CSV
    if (!archivo.is_open()) {
        std::cerr << "Error al abrir datos_sensor.csv" << std::endl;
        return 1;
    }

    // Saltar el encabezado
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
    if (N < 3) {
        std::cerr << "Datos insuficientes para derivar." << std::endl;
        return 1;
    }

    double h = x[1] - x[0]; // Paso h = 0.2
    
    // Vectores para almacenar las derivadas (más cortos por la pérdida en los bordes)
    std::vector<double> df_forward(N - 1);
    std::vector<double> df_central(N - 2);

    // 2. Diferencia hacia adelante
    for (int i = 0; i < N - 1; ++i) {
        df_forward[i] = (y[i+1] - y[i]) / h;
    }

    // 3. Diferencia central
    for (int i = 1; i < N - 1; ++i) {
        df_central[i - 1] = (y[i+1] - y[i-1]) / (2 * h);
    }

    // 4. Imprimir una muestra de los resultados (los primeros 5 valores)
    std::cout << "--- Resultados de Diferenciacion Numerica ---" << std::endl;
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "Indice\t x\t\t Hacia Adelante\t\t Central" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;
    
    // Imprimimos desde i=1 para alinear los datos, ya que la central pierde el índice 0
    for (int i = 1; i < 6; ++i) {
        std::cout << i << "\t " 
                  << x[i] << "\t\t " 
                  << df_forward[i] << "\t\t\t " 
                  << df_central[i - 1] << std::endl;
    }

    return 0;
}