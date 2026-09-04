#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <gsl/gsl_roots.h>
#include <gsl/gsl_errno.h>

double f(double x, void *params) {
  //return  (x*x*x) - (5*x) + 1;
  return std::exp(-x) - x;
}


double df(double x, void *params) {
  //return 3*x*x - 5;
  return -std::exp(-x) - 1;
}



void fdf(double x, void *params, double *y, double *dy) {
  *y = f(x, params);
  *dy = df(x, params);
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Existe más de dos argumentos en la linea de ejecución\n";
    return 1;
  }

  std::string metodo = argv[1];

  gsl_function F;
  F.function = &f;
  F.params = nullptr;
  gsl_function_fdf FDF;
  FDF.f = &f;
  FDF.df = &df;
  FDF.fdf = &fdf;
  FDF.params = nullptr;

  double x_lo = 0.0;
  double x_hi = 1000.0;
  const int max_iter = 100;
  const double tolerancia = 1e-8;
  double r = 0.0;
  int status = GSL_CONTINUE;
  int iter = 0;


  //Primero dos métodos de la lista
  if (metodo == "falsepos" || metodo == "brent" || metodo == "biseccion") {
    const gsl_root_fsolver_type *T;
    if (metodo == "falsepos") {
      T = gsl_root_fsolver_falsepos;
    } 
    else if (metodo == "biseccion"){
      T = gsl_root_fsolver_bisection;
    }
    else {
      T = gsl_root_fsolver_brent;
    }

    gsl_root_fsolver *s = gsl_root_fsolver_alloc(T);
    status = gsl_root_fsolver_set(s, &F, x_lo, x_hi);

    std::cout << "iter\tinf\tsup\traiz\n";
    do {
      ++iter;
      status = gsl_root_fsolver_iterate(s);
      r = gsl_root_fsolver_root(s);
      x_lo = gsl_root_fsolver_x_lower(s);
      x_hi = gsl_root_fsolver_x_upper(s);
      std::cout << iter << "\t" << x_lo << "\t" << x_hi << "\t" << r << "\n";
      status = gsl_root_test_interval(x_lo, x_hi, 0.0, tolerancia);
    } while (status == GSL_CONTINUE && iter < max_iter);

    gsl_root_fsolver_free(s);
  }
  
  else if (metodo == "newton" || metodo == "secant" || metodo == "steffensen") {
    const gsl_root_fdfsolver_type *T;
    if (metodo == "newton") {
      T = gsl_root_fdfsolver_newton;
    } 
    else if (metodo == "secant") {
      T = gsl_root_fdfsolver_secant;
    } 
    else {
      T = gsl_root_fdfsolver_steffenson;
    }

    gsl_root_fdfsolver *s = gsl_root_fdfsolver_alloc(T);
    double x = (x_lo + x_hi) / 2.0; //se empieza desde cualquier punto pero se define con el intervalo
    status = gsl_root_fdfsolver_set(s, &FDF, x);

    r = x;
    std::cout << "iter\tx\traiz\n";
    do {
      const double anterior = r;
      ++iter;
      status = gsl_root_fdfsolver_iterate(s);
      r = gsl_root_fdfsolver_root(s);
      std::cout << iter << "\t" << anterior << "\t" << r << "\n";
      status = gsl_root_test_delta(r, anterior, 0.0, tolerancia);
    } while (status == GSL_CONTINUE && iter < max_iter);

    gsl_root_fdfsolver_free(s);
  } else {
    std::cerr << "Metodo no valido.\n";
    return 1;
  }

  std::cout << "\nRaiz encontrada = " << r << std::endl;
  return status == GSL_SUCCESS ? 0 : 1;
}

