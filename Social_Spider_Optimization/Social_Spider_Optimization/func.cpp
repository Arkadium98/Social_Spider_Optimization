#include "func.h"
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;



/// Funcion 1, Ackley's 
float func::ackleys(vector<float>& x) {
    const double PI = 3.14159265358979323846;
    const double E = 2.71828182845904523536;
    float resultado = 0;
    for (int i = 0; i < x.size() - 1; i++) {
        float a = 0.2 * sqrt((x[i] * x[i] + x[i + 1] * x[i + 1]) / 2);
        float b = 0.5 * (cos(2 * PI * x[i]) + sin(2 * PI * x[i + 1]));
        resultado += 20 + E - 20 / pow(E, a) - pow(E, b);
    }
    return resultado;
}

/// Funcion 2, Griewangk 
float func::griewangk(vector<float>& x) {
    float sum = 0;
    float producto = 1;
    for (int i = 0; i < x.size(); i++) {
        sum += (x[i] * x[i]) / 4000;
        producto *= cos(x[i] / sqrt(i + 1));
    }
    return 1.0 + sum - producto;
}

/// Funcion 3, Levy 
float func::levy(vector<float>& x) {
    const double PI = 3.14159265358979323846;
    float resultado = sin(PI * (1 + (x[0]-1) / 4));
    resultado = resultado * resultado;
    float wn = 1 + (x[x.size() - 1] - 1) / 4;
    float wna = pow(wn - 1, 2) * (1 + pow(2 * PI * wn, 2));
    for (int i = 0; i < x.size() - 1; i++) {
        float w = 1 + (x[i] - 1) / 4;
        resultado += pow(w - 1, 2) * (1 + 10 * pow(sin(PI * w + 1), 2)) + wna;

    }
    return resultado;
}

/// Funcion 4, Rastrigin's 
float func::rastrigin(vector<float>& x) {
    const double PI = 3.14159265358979323846;

    float resultado = 0;
    for (int i = 0; i < x.size(); i++) {
        resultado += (x[i] * x[i]) - 10.0 * cos((2 * PI * x[i]));
    }
    return 10 * x.size() + resultado;
}

/// Funcion 5, Schwefel’s
float func::schwefel(vector<float>& x) {
    float resultado = 0;
    for (int i = 0; i < x.size(); i++) {
        resultado -= x[i] * sin(sqrt(fabs(x[i])));
    }
    return 418.9829 * x.size() - resultado;
}

/// Funcion 6, Rotated Hyper-Ellipsoid 
float func::r_h_e(vector<float>& x) {

    float resultado = 0;
    float sum = 0;
    for (int j = 0; j < x.size(); j++) {
        for (int i = 0; i < x.size(); i++) {
            resultado += pow(x[i], 2);
            
        }
    }
    return resultado;
}

/// Funcion 7, Sphere 
float func::sphere(vector<float>& x) {
    float resultado = 0;
    for (int i = 0; i < x.size(); i++) {
        resultado += x[i] * x[i];     
    }
    return resultado; // el resultado es muy cercano a cero
}

/// Function 8, Sum of Different Powers 
float func::sum_d_p(vector<float>& x) {
    float resultado = 0;
    float sum = 0;
    for (int i = 0; i < x.size(); i++) {
        sum = pow(x[i], i + 1);
        resultado += abs(sum);
    }
    return resultado;
}

/// Function 9, Trid 
float func::trid(vector<float>& x) {

    float resultado = 0;
    float sum1 = 0, sum2 = 0;
    for (int i = 0; i < x.size(); i++) {
        sum1 += pow(x[i] - 1, 2);
    }
    for (int i = 1; i < x.size(); i++) {
        sum2 += x[i] * x[i - 1];
    }
    resultado += sum1 - sum2; //sum2 es mayor que sum1 por eso el resultado da negativo
    return resultado; //se considera como minimo global
}

/// Function 10, Rosenbrock's
float func::rosenbrock(vector<float>& x) {
    double resultado = 0;
    for (int i = 0; i < x.size() - 1; i++) {
        double a =  x[i + 1] - (x[i] * x[i]);
        double b = 1.0 - x[i];
        resultado += (100 * a * a) + (b * b);
    }
    return (float)resultado;
}