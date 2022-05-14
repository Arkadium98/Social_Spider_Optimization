#pragma once

#ifndef func_h
#define func_h

#include <stdio.h>
#include <vector>

using namespace std;

namespace func {

    float ackleys(vector<float>& x);    //1  Ackley's
    float griewangk(vector<float>& x);  //2  Griewank
    float levy(vector<float>& x);       //3  Levy
    float rastrigin(vector<float>& x);  //4  Rastring
    float schwefel(vector<float>& x);   //5  Schwefel
    float r_h_e(vector<float>& x);      //6  Rotated Hyper Ellipsoid
    float sphere(vector<float>& x);     //7  Sphere
    float sum_d_p(vector<float>& x);    //8  Sum of Different Powers
    float trid(vector<float>& x);       //9  Trid
    float rosenbrock(vector<float>& x); //10 Rosenbrock
    
}

#endif
