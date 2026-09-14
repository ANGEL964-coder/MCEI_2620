#include <iostream>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

int main() {
    // Definir la matriz A de 4x3
    MatrixXd A(4, 3);
    A << 1,  0,  2,
         2, -1,  5,
         0,  1, -1,
         1,  3, -1;

    // Calcular pseudo-inversa de Moore-Penrose
    CompleteOrthogonalDecomposition<MatrixXd> cod(A);
    MatrixXd A_pinv = cod.pseudoInverse();

    cout << "Inversa de Moore-Penrose (A+):" << endl;
    cout << A_pinv << endl << endl;

    // Comprobación de las 4 propiedades
    double tol = 1e-10; // Tolerancia
    
    // 1. A A+ A = A
    bool prop1 = (A * A_pinv * A).isApprox(A, tol);
    
    // 2. A+ A A+ = A+
    bool prop2 = (A_pinv * A * A_pinv).isApprox(A_pinv, tol);
    
    // 3. (A A+)^T = A A+
    MatrixXd AA_pinv = A * A_pinv;
    bool prop3 = AA_pinv.transpose().isApprox(AA_pinv, tol);
    
    // 4. (A+ A)^T = A+ A
    MatrixXd A_pinvA = A_pinv * A;
    bool prop4 = A_pinvA.transpose().isApprox(A_pinvA, tol);

    cout << "--- Verificacion de Propiedades ---" << endl;
    cout << "1. A A+ A = A: " << (prop1 ? "Cumple" : "No cumple") << endl;
    cout << "2. A+ A A+ = A+: " << (prop2 ? "Cumple" : "No cumple") << endl;
    cout << "3. (A A+)^T = A A+: " << (prop3 ? "Cumple" : "No cumple") << endl;
    cout << "4. (A+ A)^T = A+ A: " << (prop4 ? "Cumple" : "No cumple") << endl;

    return 0;
}