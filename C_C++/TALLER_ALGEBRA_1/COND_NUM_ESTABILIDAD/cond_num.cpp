#include <iostream>
#include <iomanip> // Para darle formato bonito a la salida
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// Función auxiliar para calcular el número de condición usando SVD
double calcularCondicion(const MatrixXd& matriz) {
    JacobiSVD<MatrixXd> svd(matriz);
    double sigma_max = svd.singularValues()(0);
    double sigma_min = svd.singularValues()(svd.singularValues().size() - 1);
    return sigma_max / sigma_min;
}

int main() {
    // 1. Definición de la matriz original A_orig (10x10)
    MatrixXd A_orig(10, 10);
    A_orig << 3, 2, 0, 1, 4, 1, 2, 0, 1, 5,
              3, 2, 0, 1, 4, 1, 2, 0, 1, 5.000001, // Fila casi dependiente
              1, 4, 2, 0, 1, 3, 0, 2, 4, 1,
              0, 1, 5, 2, 1, 0, 3, 1, 0, 2,
              2, 0, 1, 4, 2, 1, 0, 5, 1, 3,
              1, 3, 0, 1, 5, 2, 1, 0, 2, 0,
              0, 2, 4, 0, 1, 3, 2, 1, 0, 4,
              4, 1, 0, 3, 0, 1, 5, 2, 1, 1,
              1, 0, 3, 1, 2, 0, 1, 4, 5, 2,
              2, 5, 1, 0, 3, 2, 0, 1, 2, 3;

    // 2. Vector b de entrada (puros unos)
    VectorXd b = VectorXd::Ones(10);

    // 3. Matriz perturbada A_pert
    // OJO: En Octave es (1,3), en C++ es la fila 0, columna 2
    MatrixXd A_pert = A_orig;
    A_pert(0, 2) = 0.001;

    // 4. Resolución de sistemas
    // Usamos FullPivLU por ser robusto ante matrices mal condicionadas
    VectorXd x = A_orig.fullPivLu().solve(b);
    VectorXd x_pert = A_pert.fullPivLu().solve(b);

    // 5. Cálculo del error relativo entre ambas soluciones
    double e_x = (x_pert - x).norm() / x.norm();

    // Calcular números de condición
    double cond_orig = calcularCondicion(A_orig);
    double cond_pert = calcularCondicion(A_pert);

    // 6. Impresión del resultado
    cout << scientific << setprecision(6); // Formato científico
    
    cout << "--- Vector Solucion x (Original) ---" << endl;
    cout << x.transpose() << endl << endl;

    cout << "--- Vector Solucion x (Perturbada) ---" << endl;
    cout << x_pert.transpose() << endl << endl;

    cout << "=========================================================\n";
    cout << "   ANALISIS DE PERTURBACION EN LA MATRIZ A (PUNTO 3)    \n";
    cout << "=========================================================\n";
    cout << "Numero de condicion cond(A_orig)   : " << cond_orig << endl;
    cout << "Numero de condicion cond(A_pert)   : " << cond_pert << endl;
    cout << "Error relativo en la solucion (e_x): " << e_x << endl;
    cout << "---------------------------------------------------------\n";

    return 0;
}