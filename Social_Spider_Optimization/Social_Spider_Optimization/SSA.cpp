#include "SSA.h"
#pragma warning(disable: 4996)

Posicion Posicion::init_posicion(SSA *ssa) {
    vector<float> solution(ssa->dimension);
    for (int i = 0; i < ssa->dimension; ++i) {
        solution[i] = randu() * 200.0f - 100.0f;
    }
    return Posicion(solution, 1E100);
}

Vibracion::Vibracion(const Posicion& posicion) :
    intensidad(aptitud_a_intensidad(posicion.aptitud)), posicion(posicion) {

}

Vibracion::Vibracion(double intensidad, const Posicion& posicion) :
    intensidad(intensidad), posicion(posicion) {

}

double Vibracion::intensidad_atenuacion(double factor_atenuacion, double distancia) const {
    return intensidad * exp(-distancia / factor_atenuacion);
}

double Vibracion::aptitud_a_intensidad(double aptitud) {
    return  log(1.0 / (aptitud - C) + 1.0);
}

double Vibracion::C = -1E-100;

Spider::Spider(const Posicion& posicion) :
    posiciones(posicion), inactivo_deg(0) {
    objetivo_vibr = Vibracion(0, posicion);
    dimension_mascara.resize(posicion.solucion.size());
    movimiento_previo.resize(posicion.solucion.size());
}

void Spider::elegir_vibracion(const vector<Vibracion>& vibraciones,
    const vector<double>& distancia, double factor_atenuacion) {
    int max_index = -1;
    double maxima_intencidad = objetivo_vibr.intensidad;
    for (int i = 0; i < vibraciones.size(); ++i) {
        if (vibraciones[i].posicion == objetivo_vibr.posicion) {
            continue;
        }
        double intensidad = vibraciones[i].intensidad_atenuacion(factor_atenuacion, distancia[i]);
        if (intensidad > maxima_intencidad) {
            max_index = i;
            maxima_intencidad = intensidad;
        }
    }
    if (max_index != -1) {
        objetivo_vibr = Vibracion(maxima_intencidad, vibraciones[max_index].posicion);
        inactivo_deg = 0;
    }
    else {
        ++inactivo_deg;
    }
}

void Spider::cambio_mascara(double p_cambio, double p_mascara) {
    if (randu() > pow(p_cambio, inactivo_deg)) {
        inactivo_deg = 0;
        p_mascara *= randu();
        for (int i = 0; i < dimension_mascara.size(); ++i) {
            dimension_mascara[i] = (randu()) < p_mascara;
        }
    }
}

void Spider::camino_random(const vector<Vibracion>& vibraciones) {
    for (int i = 0; i < posiciones.solucion.size(); ++i) {
        movimiento_previo[i] *= randu();
        double posicion_objetivo = dimension_mascara[i] ?
            vibraciones[rand() % vibraciones.size()].posicion.solucion[i] :
            objetivo_vibr.posicion.solucion[i];
        movimiento_previo[i] += randu() * (posicion_objetivo - posiciones.solucion[i]);
        posiciones.solucion[i] += movimiento_previo[i];
    }
}

SSA::SSA(float (*f)(vector<float>&), float inf, float sup){
    funcion = f;
    limite_inferior = inf;
    limite_superior = sup;
    srand((unsigned int)(time(NULL) + (int)this));
    poblacion.reserve(tamano_poblacion);
    distancias.resize(tamano_poblacion);
    for (int i = 0; i < tamano_poblacion; ++i) {
        Posicion posicion = Posicion::init_posicion(this);
        poblacion.push_back(Spider(posicion));
        distancias[i].resize(tamano_poblacion);
    }
    vibraciones.reserve(tamano_poblacion);
    mejor_global = poblacion[0].posiciones;
}

void SSA::correr() {
    int cont = 1;
    Imprimir_cabeza();
    tiempo_inicio = high_resolution_clock::now();
    for (iteracion = 1; iteracion <= this->maxima_iteracion; ++iteracion) {
        calculo_aptitud();
        generacion_vibracion(this->tasa_atenuacion);
        for (int i = 0; i < poblacion.size(); ++i) {
            poblacion[i].cambio_mascara(p_cambio, p_mascara);
            poblacion[i].camino_random(vibraciones);
        }
        if ((iteracion == 1) || (iteracion % 66 == 0)||(iteracion == 2000))
        {
            Imprimir_contenido();
        }
        
    }
    iteracion--;
    Imprimir_pies();
}

void SSA::calculo_aptitud() {
    poblacion_mejor_aptitud = 1E100;
    for (int i = 0; i < poblacion.size(); ++i) {

        
        double fitness = funcion(poblacion[i].posiciones.solucion);
        poblacion[i].posiciones.aptitud = fitness;
        if (fitness < mejor_global.aptitud) {
            mejor_global = poblacion[i].posiciones;
        }
        if (fitness < poblacion_mejor_aptitud) {
            poblacion_mejor_aptitud = fitness;
        }
    }
    distancia_media = 0;
    for (int i = 0; i < poblacion.size(); ++i) {
        for (int j = i + 1; j < poblacion.size(); ++j) {
            distancias[i][j] = poblacion[i].posiciones - poblacion[j].posiciones;
            distancias[j][i] = distancias[i][j];
            distancia_media += distancias[i][j];
        }
    }
    distancia_media /= (poblacion.size() * (poblacion.size() - 1) / 2);
}

void SSA::generacion_vibracion(double tasa_ateuacion) {
    vibraciones.clear();
    for (int i = 0; i < poblacion.size(); ++i) {
        vibraciones.push_back(move(Vibracion(poblacion[i].posiciones)));
    }
    double sum = 0.0;
    vector<double> data;
    data.resize(poblacion.size());
    for (int i = 0; i < dimension; ++i) {
        for (int j = 0; j < poblacion.size(); ++j) {
            data[j] = poblacion[j].posiciones.solucion[i];
        }
        sum += dev_std(data);
    }
    base_atenuacion = sum / dimension;
    for (int i = 0; i < poblacion.size(); ++i) {
        poblacion[i].elegir_vibracion(vibraciones, distancias[i], base_atenuacion * tasa_atenuacion);
    }
}

void SSA::Imprimir_cabeza() {
    cout << "               Inicio de corrida el "
        << obtener_tiempo_string() << endl
        << "=========================================================================================" << endl
        << " iter \t Optimo \t Poblacion_Min \t Base_Atenuacion \tMedia \t Lapso_tiempo" << endl
        << "=========================================================================================" << endl;
}

void SSA::Imprimir_contenido() {
    auto tiempo_actual = high_resolution_clock::now();
    printf("%5d |\t %.3f |\t %.3f |\t %.3f |\t %.3f |\t ", iteracion, mejor_global.aptitud, poblacion_mejor_aptitud,
        base_atenuacion, distancia_media);
    cout << obtener_tiempo_string(duration_cast<milliseconds>(tiempo_actual - tiempo_inicio)) << endl;
}

void SSA::Imprimir_pies() {
    cout << "=========================================================================================" << endl;
    Imprimir_contenido();
    cout << "=========================================================================================" << endl;
}

string obtener_tiempo_string() {
    
    auto tiempo_t = system_clock::to_time_t(system_clock::now());
    auto ttm = localtime(&tiempo_t);

    char tiempo_str[80];
    strftime(tiempo_str, 80, "%Y-%m-%d %H:%M:%S", ttm);
    return string(tiempo_str);
}

string obtener_tiempo_string(milliseconds ms) {
    long long int mss = ms.count();
    char tiempo_str[80];
    sprintf(tiempo_str, "%02d:%02d:%02d.%03d", int(mss / 3600000), int(mss / 60000 % 60),
        int(mss / 1000 % 60), int(mss % 1000));
    return string(tiempo_str);
}