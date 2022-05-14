#include "SSA.h"
#include "func.h"
using namespace std;



int main() {
    SSA ssa1 = SSA(func::ackleys, -32, 32);
    SSA ssa2 = SSA(func::griewangk, -600, 600);
    SSA ssa3 = SSA(func::levy, -10, 10);
    SSA ssa4 = SSA(func::rastrigin, -5, 5);
    SSA ssa5 = SSA(func::schwefel, -500, 500);
    SSA ssa6 = SSA(func::r_h_e, -65, 65);
    SSA ssa7 = SSA(func::sphere, -5, 5);
    SSA ssa8 = SSA(func::sum_d_p, -1, 1);
    SSA ssa9 = SSA(func::trid, -100, 100);
    SSA ssa10 = SSA(func::rosenbrock, -5, 10);

    int opc;
    cout << "----------Menu de Funciones ----------" << endl;
    cout << "\t" << "1) Ackley" << endl;
    cout << "\t" << "2) Giewangk" << endl;
    cout << "\t" << "3) Levy" << endl;
    cout << "\t" << "4) Rastrigin" << endl;
    cout << "\t" << "5) Schwefel" << endl;
    cout << "\t" << "6) Rotated Hyper Ellipsoid" << endl;
    cout << "\t" << "7) Sphere" << endl;
    cout << "\t" << "8) Sum of Different Power" << endl;
    cout << "\t" << "9) Trid" << endl;
    cout << "\t" << "10) Rosenbrock" << endl;
    cout << "Digite el numero asignado a la funcion (1 a 10) : ";
    cin >> opc;
    switch (opc)
    {
    case 1:
        cout << "------------------------------------------Ackley Function--------------------------------" << endl;
        ssa1.maxima_iteracion = 2000;
        ssa1.tasa_atenuacion = 1.0;
        ssa1.p_cambio = 0.7;
        ssa1.p_mascara = 0.1;
        ssa1.correr();
        break;
    case 2:
        cout << "-------------------------------------------Griewangk Function----------------------------" << endl;
        ssa2.maxima_iteracion = 2000;
        ssa2.tasa_atenuacion = 1.0;
        ssa2.p_cambio = 0.7;
        ssa2.p_mascara = 0.1;
        ssa2.correr();
        break;
    case 3:
        cout << "--------------------------------------------Levy Function--------------------------------" << endl;
        ssa3.maxima_iteracion = 2000;
        ssa3.tasa_atenuacion = 1.0;
        ssa3.p_cambio = 0.7;
        ssa3.p_mascara = 0.1;
        ssa3.correr();
        break;
    case 4:
        cout << "-------------------------------------------Rastrigins Function---------------------------" << endl;
        ssa4.maxima_iteracion = 2000;
        ssa4.tasa_atenuacion = 1.0;
        ssa4.p_cambio = 0.7;
        ssa4.p_mascara = 0.1;
        ssa4.correr();
        break;
    case 5:
        cout << "-------------------------------------------Schwefels Function----------------------------" << endl;
        ssa5.maxima_iteracion = 2000;
        ssa5.tasa_atenuacion = 1.0;
        ssa5.p_cambio = 0.7;
        ssa5.p_mascara = 0.1;
        ssa5.correr();
        break;
    case 6:
        cout << "-------------------------------------Rotated Hyper-Ellipsoid Function--------------------" << endl;
        ssa6.maxima_iteracion = 2000;
        ssa6.tasa_atenuacion = 1.0;
        ssa6.p_cambio = 0.7;
        ssa6.p_mascara = 0.1;
        ssa6.correr();
        break;
    case 7:
        cout << "---------------------------------------------Sphere Function-----------------------------" << endl;
        ssa7.maxima_iteracion = 2000;
        ssa7.tasa_atenuacion = 1.0;
        ssa7.p_cambio = 0.7;
        ssa7.p_mascara = 0.1;
        ssa7.correr();
        break;
    case 8:
        cout << "-------------------------------------Sum of Different Powers Function--------------------" << endl;
        ssa8.maxima_iteracion = 2000;
        ssa8.tasa_atenuacion = 1.0;
        ssa8.p_cambio = 0.7;
        ssa8.p_mascara = 0.1;
        ssa8.correr();
        break;
    case 9:
        cout << "---------------------------------------------Trid Function-------------------------------" << endl;
        ssa9.maxima_iteracion = 2000;
        ssa9.tasa_atenuacion = 1.0;
        ssa9.p_cambio = 0.7;
        ssa9.p_mascara = 0.1;
        ssa9.correr();
        break;
    case 10:
        cout << "--------------------------------------------Rosenbrocks Function-------------------------" << endl;
        ssa10.maxima_iteracion = 2000;
        ssa10.tasa_atenuacion = 1.0;
        ssa10.p_cambio = 0.7;
        ssa10.p_mascara = 0.1;
        ssa10.correr();
        break;
    }

    system("pause");

    return 0;
}