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
        int dirIn; // How much IP direction try to access to this IP
        int dirOut; // How much directions this IP access to

    public:
        Ip();
        Ip(string valIp, int valDirIn, int valDirOut);
        // Acceso a datos privados
        void setIp(string s_ip);
        void setDirIn(int valDirIn);
        void setDirOut(int valDirOut);
        string getIp();
        int getDirIn();
        int getDirOut();
        // Sobrecarga de operadores
        bool operator > (const Ip&); 
        bool operator < (const Ip&);
        bool operator == (const Ip&);
        bool operator != (const Ip&);
        bool operator >= (const Ip&);
        bool operator <= (const Ip&);
        int operator %(const int key);
};

Ip::Ip(){
    ip = "";
    dirIn = 0;
    dirOut = 0;
}

Ip::Ip(string valIp, int valDirIn, int valDirOut){
    ip = valIp;
    dirIn = valDirIn;
    dirOut = valDirOut;
}

// Establecer el valor de la Ip
void Ip::setIp(string s_ip){
    ip = s_ip;
}

void Ip::setDirIn(int valDirIn){
    dirIn = valDirIn;
}

void Ip::setDirOut(int valDirOut){
    dirOut = valDirOut;
}

int Ip::getDirIn(){
    return dirIn;
}

int Ip::getDirOut(){
    return dirOut;
}

// Devolver IP (dato privado)
string Ip::getIp(){
    return ip;
}

// ------------------------
// Sobrecarga de operadores
// ------------------------

bool Ip::operator > (const Ip &other){

    return this->dirOut > other.dirOut;
}

bool Ip::operator < (const Ip &other){

    return this->dirOut < other.dirOut;
}

bool Ip::operator == (const Ip &other){

    return this->dirOut == other.dirOut;
}

bool Ip::operator != (const Ip &other){

    return this->dirOut != other.dirOut;
}

bool Ip::operator >= (const Ip &other){

    return this->dirOut >= other.dirOut;
}

bool Ip::operator <= (const Ip &other){

    return this->dirOut <= other.dirOut;
}

int Ip::operator %(const int key){
    return dirOut%key;
}

#endif