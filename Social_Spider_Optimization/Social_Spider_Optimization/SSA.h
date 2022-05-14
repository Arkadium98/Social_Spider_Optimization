#pragma once

#ifndef SSA_SSA_H
#define SSA_SSA_H

#include <chrono>
#include <ctime>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace chrono;
class SSA;

class Posicion {
public:
    double aptitud;
    vector<float> solucion;

    Posicion() { };
    Posicion(const vector<float>& solucion, double aptitud) :
        solucion(solucion), aptitud(aptitud) { }

    friend bool operator==(const Posicion& p1, const Posicion& p2) {
        for (int i = 0; i < p1.solucion.size(); ++i) {
            if (p1.solucion[i] != p2.solucion[i]) {
                return false;
            }
        }
        return true;
    }

    friend double operator-(const Posicion& p1, const Posicion& p2) {
        double distancia = 0.0;
        for (int i = 0; i < p1.solucion.size(); ++i) {
            distancia += fabs(p1.solucion[i] - p2.solucion[i]);
        }
        return distancia;
    }

    static Posicion init_posicion(SSA* ssa);
};

class Vibracion {
public:
    double intensidad;
    Posicion posicion;
    static double C;

    Vibracion() { }
    Vibracion(const Posicion& posicion);
    Vibracion(double intensidad, const Posicion& posicion);

    double intensidad_atenuacion(double factor_atenuacion, double distancia) const;
    static double aptitud_a_intensidad(double atenuacion);
};

class Spider {
public:
    Posicion posiciones;
    Vibracion objetivo_vibr;
    vector<bool> dimension_mascara;
    vector<double> movimiento_previo;
    int inactivo_deg;

    Spider(const Posicion& position);

    void elegir_vibracion(const vector<Vibracion>& vibrations,
        const vector<double>& distances, double attenuation_factor);
    void cambio_mascara(double p_change, double p_mask);
    void camino_random(const vector<Vibracion>& vibrations);
};

class SSA {
public:
    const double PI = 3.14159265358979323846;
    const double E = 2.71828182845904523536;
    float (*funcion)(vector<float>&); /// Función objetivo

    unsigned int dimension = 10; // Dimension 10 y 20
    int tamano_poblacion = 30; /// Tamaño de la población
    vector<Spider> poblacion;  
    vector<Vibracion> vibraciones;
    vector<vector<double>> distancias;
    Posicion mejor_global;
    //-----Limites--------
    float limite_inferior; /// Límite inferior de la solución objetivo
    float limite_superior; /// Límite superior de la solución objetivo

    int iteracion;
    double poblacion_mejor_aptitud;
    double base_atenuacion;
    double distancia_media;
    int    maxima_iteracion;
    double tasa_atenuacion;
    double p_cambio;
    double p_mascara;

    SSA(float (*f)(vector<float>&), float l, float u);          
    void correr();
    void calculo_aptitud();
    void generacion_vibracion(double tasa_atenuacion);

private:
    
    high_resolution_clock::time_point tiempo_inicio;
    void Imprimir_cabeza();
    void Imprimir_contenido();
    void Imprimir_pies();
};

inline double media(vector<double> data) {
    double sum = 0.0;
    for (int i = 0; i < data.size(); ++i) {
        sum += data[i];
    }
    return sum / data.size();
}

inline double dev_std(std::vector<double> data) {
    double valor_media = media(data);
    double sum = 0.0;
    for (int i = 0; i < data.size(); ++i) {
        sum += (valor_media - data[i]) * (valor_media - data[i]);
    }
    return sqrt(sum / data.size());
}

inline double randu() {
    return (double)rand() / (RAND_MAX + 1.0f);
}

string obtener_tiempo_string();
string obtener_tiempo_string(milliseconds ms);

#endif
