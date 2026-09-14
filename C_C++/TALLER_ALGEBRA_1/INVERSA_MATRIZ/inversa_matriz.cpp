#include <iostream>
#include <iomanip>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    MatrixXd A(10, 10);
    A << 3, 2, 0, 1, 4, 1, 2, 0, 1, 5,
         3, 2, 0, 1, 4, 1, 2, 0, 1, 5.000001,
         1, 4, 2, 0, 1, 3, 0, 2, 4, 1,
         0, 1, 5, 2, 1, 0, 3, 1, 0, 2,
         2, 0, 1, 4, 2, 1, 0, 5, 1, 3,
         1, 3, 0, 1, 5, 2, 1, 0, 2, 0,
         0, 2, 4, 0, 1, 3, 2, 1, 0, 4,
         4, 1, 0, 3, 0, 1, 5, 2, 1, 1,
         1, 0, 3, 1, 2, 0, 1, 4, 5, 2,
         2, 5, 1, 0, 3, 2, 0, 1, 2, 3;

    MatrixXd I = MatrixXd::Identity(10, 10);

    // --- 1. Método Directo ---
    MatrixXd inv_directa = A.inverse();
    double err_directa = (A * inv_directa - I).norm();

    // --- 2. Descomposición QR ---
    HouseholderQR<MatrixXd> qr(A);
    MatrixXd Q = qr.householderQ();
    // Extraemos R (parte triangular superior)
    MatrixXd R = qr.matrixQR().triangularView<Upper>(); 
    MatrixXd inv_qr = R.inverse() * Q.transpose();
    double err_qr = (A * inv_qr - I).norm();

    // --- 3. Descomposición SVD ---
    // Calculamos U y V
    JacobiSVD<MatrixXd> svd(A, ComputeThinU | ComputeThinV); 
    // Invertimos los valores singulares
    MatrixXd S_inv = svd.singularValues().cwiseInverse().asDiagonal(); 
    MatrixXd inv_svd = svd.matrixV() * S_inv * svd.matrixU().transpose();
    double err_svd = (A * inv_svd - I).norm();

    // --- Impresión de Resultados ---
    cout << scientific << setprecision(6);
    cout << "=== ERROR RESIDUAL ||A * A^-1 - I|| ===\n";
    cout << "Metodo Directo : " << err_directa << endl;
    cout << "Metodo QR      : " << err_qr << endl;
    cout << "Metodo SVD     : " << err_svd << endl;

    return 0;
}