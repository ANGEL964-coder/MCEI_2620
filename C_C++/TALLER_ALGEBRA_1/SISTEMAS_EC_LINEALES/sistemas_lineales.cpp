#include <iostream>
#include <chrono>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

// ¡Aquí está la magia! Definimos Vector10d para que el compilador lo entienda
typedef Matrix<double, 10, 1> Vector10d;

int main() {
    // 1. Matriz A 10x10 y vector b
    Matrix<double, 10, 10> A;
    A << 2, 1, 0, 3, 2, 1, 0, 2, 1, 4,
         1, 3, 2, 0, 1, 4, 2, 1, 0, 2,
         0, 2, 4, 1, 3, 0, 1, 2, 4, 1,
         3, 0, 1, 5, 2, 1, 3, 0, 2, 1,
         2, 1, 3, 2, 6, 2, 1, 4, 0, 3,
         1, 4, 0, 1, 2, 5, 2, 1, 3, 0,
         0, 2, 1, 3, 1, 2, 4, 0, 2, 1,
         2, 1, 2, 0, 4, 1, 0, 5, 3, 2,
         1, 0, 4, 2, 0, 3, 2, 3, 6, 1,
         4, 2, 1, 1, 3, 0, 1, 2, 1, 5;

    Vector10d b = Vector10d::Ones();

    // Número de condición usando SVD
    JacobiSVD<Matrix<double, 10, 10>> svd(A);
    double cond = svd.singularValues()(0) / svd.singularValues()(svd.singularValues().size() - 1);
    cout << "=== NUMERO DE CONDICION ===" << endl;
    cout << "cond(A) = " << cond << endl << endl;

    // --- 1. Eliminación de Gauss (FullPivLU) ---
    auto start = chrono::high_resolution_clock::now();
    Vector10d x_gauss = A.fullPivLu().solve(b);
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_gauss = end - start;
    double res_gauss = (A * x_gauss - b).norm();

    // --- 2. Factorización LU (PartialPivLU) ---
    start = chrono::high_resolution_clock::now();
    PartialPivLU<Matrix<double, 10, 10>> lu(A);
    Vector10d x_lu = lu.solve(b);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_lu = end - start;
    double res_lu = (A * x_lu - b).norm();

    // --- 3. Factorización QR (HouseholderQR) ---
    start = chrono::high_resolution_clock::now();
    HouseholderQR<Matrix<double, 10, 10>> qr(A);
    Vector10d x_qr = qr.solve(b);
    end = chrono::high_resolution_clock::now();
    chrono::duration<double, milli> t_qr = end - start;
    double res_qr = (A * x_qr - b).norm();

    // Impresión de resultados
    cout << "--- Solucion x (Gauss) ---" << endl << x_gauss.transpose() << endl;
    cout << "--- Solucion x (LU) ---" << endl << x_lu.transpose() << endl;
    cout << "--- Solucion x (QR) ---" << endl << x_qr.transpose() << endl << endl;

    cout << "=== COMPARACION DE RENDIMIENTO ===" << endl;
    cout << "Metodo\t\tTiempo (ms)\t\tNorma Residuo ||Ax - b||" << endl;
    cout << "Gauss\t\t" << t_gauss.count() << "\t\t" << res_gauss << endl;
    cout << "LU\t\t" << t_lu.count() << "\t\t" << res_lu << endl;
    cout << "QR\t\t" << t_qr.count() << "\t\t" << res_qr << endl;

    return 0;
}