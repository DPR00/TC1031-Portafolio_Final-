#ifndef _IP_H_
#define _IP_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

using std::string;

class Ip{

    private:
        string ip;
        int accesosTotales;

    public:
        Ip();
        Ip(string valIp, int valAt);
        // Acceso a datos privados
        int getAccesosTotales();
        string getIp();
        // Sobrecarga de operadores
        bool operator > (const Ip&); 
        bool operator < (const Ip&);
        bool operator == (const Ip&);
        bool operator != (const Ip&);
        bool operator >= (const Ip&);
        bool operator <= (const Ip&);
};

Ip::Ip(){
    ip = "";
    accesosTotales = 0;
}

Ip::Ip(string valIp, int valAt){
    ip = valIp;
    accesosTotales = valAt;
}

// Devolver accesos totales (dato privado)
int Ip::getAccesosTotales(){
    return accesosTotales;
}


// Devolver IP (dato privado)
string Ip::getIp(){
    return ip;
}

// ------------------------
// Sobrecarga de operadores
// ------------------------

bool Ip::operator > (const Ip &other){

    return this->accesosTotales > other.accesosTotales;
}

bool Ip::operator < (const Ip &other){

    return this->accesosTotales < other.accesosTotales;
}

bool Ip::operator == (const Ip &other){

    return this->accesosTotales == other.accesosTotales;
}

bool Ip::operator != (const Ip &other){

    return this->accesosTotales != other.accesosTotales;
}

bool Ip::operator >= (const Ip &other){

    return this->accesosTotales >= other.accesosTotales;
}

bool Ip::operator <= (const Ip &other){

    return this->accesosTotales <= other.accesosTotales;
}

#endif