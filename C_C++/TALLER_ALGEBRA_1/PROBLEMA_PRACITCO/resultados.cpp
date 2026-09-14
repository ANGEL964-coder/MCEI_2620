#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

int main() {
    // 1. Leer el archivo CSV
    ifstream file("datos_convertidor_realista.csv");
    string line, val;
    vector<double> V, I, T, P;
    
    // Saltar la cabecera
    if(file.good()) getline(file, line);
    
    while(getline(file, line)) {
        stringstream ss(line);
        getline(ss, val, ','); V.push_back(stod(val));
        getline(ss, val, ','); I.push_back(stod(val));
        getline(ss, val, ','); T.push_back(stod(val));
        getline(ss, val, ','); P.push_back(stod(val));
    }
    
    int n = P.size();
    
    // 2. Construir matriz X y vector y
    MatrixXd X(n, 4);
    VectorXd y(n);
    for(int i = 0; i < n; i++) {
        X(i, 0) = 1.0;     // Intersección (beta_0)
        X(i, 1) = V[i];
        X(i, 2) = I[i];
        X(i, 3) = T[i];
        y(i) = P[i];
    }
    
    // 3. Resolver por mínimos cuadrados usando SVD
    VectorXd beta = X.bdcSvd(ComputeThinU | ComputeThinV).solve(y);
    
    // 4. Residual y Error Cuadrático Medio (MSE)
    VectorXd y_pred = X * beta;
    VectorXd residual = y - y_pred;
    double mse = residual.squaredNorm() / n;
    
    // 5. Número de condición de X
    JacobiSVD<MatrixXd> svd(X);
    double cond_X = svd.singularValues()(0) / svd.singularValues()(svd.singularValues().size()-1);
    
    // Impresión
    cout << "=== MODELO LINEAL DEL CONVERTIDOR ===" << endl;
    cout << "Beta_0 (Interseccion): " << beta(0) << endl;
    cout << "Beta_1 (Voltaje V)   : " << beta(1) << endl;
    cout << "Beta_2 (Corriente I) : " << beta(2) << endl;
    cout << "Beta_3 (Temp T)      : " << beta(3) << endl << endl;
    cout << "Norma del Residual   : " << residual.norm() << endl;
    cout << "Error Cuad. Medio    : " << mse << endl;
    cout << "Condicion de X       : " << cond_X << endl;
    
    return 0;
}