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
        int grado;

    public:
        Ip();
        Ip(string valIp, int valG);
        // Acceso a datos privados
        void setIp(string s_ip);
        void setGradeIp(int grad);
        int getGradeIp();
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
    grado = 0;
}

Ip::Ip(string valIp, int valG){
    ip = valIp;
    grado = valG;
}

// Establecer el valor de la Ip
void Ip::setIp(string s_ip){
    ip = s_ip;
}

// Establecer el valor del grado de la Ip
void Ip::setGradeIp(int grad){
    grado = grad;
}

// Devolver accesos totales (dato privado)
int Ip::getGradeIp(){
    return grado;
}


// Devolver IP (dato privado)
string Ip::getIp(){
    return ip;
}

// ------------------------
// Sobrecarga de operadores
// ------------------------

bool Ip::operator > (const Ip &other){

    return this->grado > other.grado;
}

bool Ip::operator < (const Ip &other){

    return this->grado < other.grado;
}

bool Ip::operator == (const Ip &other){

    return this->grado == other.grado;
}

bool Ip::operator != (const Ip &other){

    return this->grado != other.grado;
}

bool Ip::operator >= (const Ip &other){

    return this->grado >= other.grado;
}

bool Ip::operator <= (const Ip &other){

    return this->grado <= other.grado;
}

#endif