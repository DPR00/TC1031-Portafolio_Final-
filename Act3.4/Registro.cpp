#include "Registro.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using std::string;
using std::cout;
using std::cin;
using std::stoi;
using std::endl;

Registro::Registro(){
    day = 1;
    ip = "a";
    reason = "b";
}

// Guardar datos
void Registro::setData(string t_month, int t_day, string t_hours, string t_ip, string t_reason){
    
    ip = t_ip;
    reason = t_reason;
    hours = t_hours;
    month = t_month;
    day = t_day;
}

// Función que retorna el valor de la IP en string
string Registro::getIp(){
    return ip;
}

// Función que retorna el valor del registro
string Registro::getInfo(){
    string info;
    info = month + " " + std::to_string(day) + " " + hours + " " + ip + " " + reason;
    return info;
}

// Función que retorna la ip en formato entero
unsigned int Registro::getIntIp(string t_ip){

    unsigned int intIP=0;
    string temp = "";
    int pos= 3;
    for(int i=0; i < t_ip.size(); i++){
        temp += (t_ip)[i];
        if ((t_ip)[i] == '.' || (t_ip)[i] == ':'){
            intIP += stoi(temp)*pow(256,pos);
            pos--;
            temp = "";
        }
        if ((t_ip)[i] == ':') break; 
    }
    return intIP;
}

// Función que sobrecarga el operador >
bool Registro::operator > (const Registro &other){

    unsigned int intIP= getIntIp(this->ip);
    unsigned int intIP2= getIntIp(other.ip);

    return intIP > intIP2;
}

// Función que sobrecarga el operador <
bool Registro::operator < (const Registro &other){

    unsigned int intIP= getIntIp(this->ip);
    unsigned int intIP2= getIntIp(other.ip);

    return intIP < intIP2;
}

// Función que sobrecarga el operador ==
bool Registro::operator == (const Registro &other){

    unsigned int intIP= getIntIp(this->ip);
    unsigned int intIP2= getIntIp(other.ip);

    return intIP == intIP2;
}

// Función que sobrecarga el operador !=
bool Registro::operator != (const Registro &other){

    unsigned int intIP= getIntIp(this->ip);
    unsigned int intIP2= getIntIp(other.ip);

    return intIP != intIP2;
}

// Función que sobrecarga el operador >=
bool Registro::operator >= (const Registro &other){

    unsigned int intIP= getIntIp(this->ip);
    unsigned int intIP2= getIntIp(other.ip);

    return intIP >= intIP2;
}

// Función que sobrecarga el operador <=
bool Registro::operator <= (const Registro &other){

    unsigned int intIP= getIntIp(this->ip);
    unsigned int intIP2= getIntIp(other.ip);

    return intIP <= intIP2;
}