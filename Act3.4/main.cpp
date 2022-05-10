/**
 * Fecha: 10 May 2022
 * 
 * Integrantes: 
 *   - Diego Palma (A01759772)
 *
 * Para compilar: 
 * g++ -std=c++17 *.cpp -o main
 *
 * Para ejecutar:
 * ./main 
 */

#include "Registro.h"
#include "MaxHeap.h"
#include "Ip.h"
#include <string>
#include <algorithm>
#include <fstream>
#include <cstdlib>

using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::cin;
using std::cerr;
using std::endl;

#define MAX 17000

ofstream outputFile;
ofstream outputFile2;

// =============
// Main function
// =============
int main(){
    // Datos 
    MaxHeap<Registro> mhRegistros(MAX);

    // Variables para almacenar cada registro
    Registro temp_btc, bitacora1, bitacora2;
    string t_month, t_ip, t_hours;
    int t_day;
    
    // Leer el archivo "bitacora.txt"
    ifstream inFile;
    inFile.open("bitacoraHeap.txt");
    if(!inFile){
        cerr << "Error while opening the file" << endl;
        return 1;
    }

    // Almacenar datos en MaxHeap
    while(!inFile.eof()){
        inFile >> t_month >> t_day >> t_hours >> t_ip;
        string t_reason;
        while ( (inFile.peek() != '\n' && inFile.peek() != EOF)){
            string temp;
            inFile >> temp;
            t_reason += temp+ " ";
        }
        temp_btc.setData(t_month, t_day, t_hours, t_ip, t_reason);
        mhRegistros.push(temp_btc);
    }

    // getSize
    int size =  mhRegistros.getSize();

    // Ordena los registros
    cout << "Ordenando registros ..." << endl;
    mhRegistros.sort();

    // Almacenar data ordenada por IP
    vector<Registro> dataOrdenada = mhRegistros.getData();

    // Guardar valores ordenados en 'bitacora_ordenada.txt'
    cout << "Guardando registros ordenados ..." << endl;
    outputFile.open("bitacora_ordenada.txt");
    for(int i=0; i<mhRegistros.getSize(); i++){
        outputFile << dataOrdenada[i].getInfo() << endl;
    }

    // -----------
    // Contabilizar de forma eficiente la cantidad de accesos de cada IP. 
    // -----

    // Crear un MaxHeap de las IPs
    MaxHeap<Ip> cantAccesos(size);

    // Contabilizar la cantidad de accesos
    int cuenta = 1, j= 0;
    for (int i = 0; i + j < size; i++)
    {
        Registro temp = dataOrdenada[i+j]; // Almacena el primer valor
        // Compara el valor almacenado con los siguientes hasta que no sean iguales (Esto debido a que estan ordenados)
        while( temp.getIntIp(temp.getIp()) == dataOrdenada[i+j+1].getIntIp(dataOrdenada[i+j+1].getIp())){
            cuenta++; // aumenra la cuenta
            j++; // aumenta iterador
        }
        Ip tempIp(temp.getIp(), cuenta); // Crea un objeto IP con la ip actual y la cantidad de accesos
        cantAccesos.push(tempIp); // Agrega el objeto al MaxHeap
        cuenta= 1; // Reinicia la cuenta
    }

    // Guardar la cantidad de accesos en 'bitacora_ordenada.txt'
    cout << "Guardando cantidad de accesos totales ..." << endl;
    outputFile2.open("ips_con_mayor_acceso.txt");

    for(int i=0; i<5; i++){
        outputFile2 << cantAccesos.top().getIp() << ": " << cantAccesos.top().getAccesosTotales() << endl;
        cantAccesos.pop();
    }   

    return 1;
}