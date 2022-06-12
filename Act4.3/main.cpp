/**
 * Fecha: 05 Jun 2022
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

#include "Graph.h"
#include "Ip.h"
#include "MaxHeap.h"
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

ofstream outputFile;
ofstream outputFile2;
ofstream outputFile3;


int main(){

    // Leer el archivo
    ifstream inFile;
    inFile.open("bitacoraGrafos.txt");
    if(!inFile){
        cerr << "Error while opening the file" << endl;
        return 1;
    }

    // Variables
    int nodes, edges;
    inFile >> nodes >> edges;
    Graph Grafo(nodes, edges);

    //----------------------------
    // Almacenar datos en el Grafo
    //----------------------------
    while(!inFile.eof()){
        // Recibimos los nodos
        for(int i=0; i<nodes; i++){
            string tempIp;
            inFile >> tempIp;
            Grafo.addNode(tempIp);
        }
        // Recibimos los edges
        for(int i=0; i<edges; i++){
            string junk, origenIp, destinoIp; 
            int costo;
            // Ignoramos las entradas que no requerimos en este problema
            for(int i=0; i<3; i++){
                inFile >> junk;
            }
            // Recibimos ambas IP y el costo
            inFile >> origenIp >> destinoIp >> costo;
            // Solo obtener la IP (ignorar el puerto)
            size_t pos1 = origenIp.find(":");
            origenIp = origenIp.substr(0, pos1);
            size_t pos2 = destinoIp.find(":");
            destinoIp = destinoIp.substr(0, pos2);;
            // Creamos par de IP de destino y costo
            pair<string, int> tempPair(destinoIp, costo);
            // agregamos el edge
            Grafo.addEdge(origenIp, tempPair);
            // Ignoramos las entradas que no seran utilizadas
            while ( (inFile.peek() != '\n' && inFile.peek() != EOF)){
                inFile >> junk;
            }
        }
    }

    //-------------------------------------
    // Determinar las 5 IPs con mayor grado
    //-------------------------------------
    MaxHeap<Ip> gradeIp(nodes);
    cout << "Guardando el grado de cada nodo ..." << endl;
    outputFile.open("grados_ips.txt");
    map<string, vector<pair<string,int>>> listAdj = Grafo.getData();
    auto iter = listAdj.begin();
    while (iter != listAdj.end()) {
        Ip tempIp(iter->first, Grafo.getGrade(iter->first)); // Crea un objeto IP con la ip actual y ell grado
        outputFile << "(" << iter->first << ", " << Grafo.getGrade(iter->first) << ")" << endl;
        gradeIp.push(tempIp); // Agrega la IP al MaxHeap
        ++iter;
    }
    outputFile.close();

    //-------------------------------------------------------------
    // Guardar la cantidad de accesos en 'ips_con_mayor_acceso.txt'
    //-------------------------------------------------------------
    cout << "Guardando IPs con mayor grado ..." << endl;
    outputFile2.open("mayores_grados_ips.txt");
    Ip bootMaster = gradeIp.top();
    outputFile2 << "("<< bootMaster.getIp() << ", " << bootMaster.getGradeIp() << ")" << endl;
    cout << "El boot master probablemente se encuentra en la dirección IP: "<< bootMaster.getIp() << endl;
    gradeIp.pop();
    for(int i=0; i<4; i++){
        outputFile2 << "("<<gradeIp.top().getIp() << ", " << gradeIp.top().getGradeIp() << ")" << endl;
        gradeIp.pop();
    }
    outputFile2.close();

    //------------------------------------------------
    // Distancias mas cortas del bootmaster a cada IP
    //------------------------------------------------
    vector<pair<string, int>> distancias = Grafo.shortestPath(bootMaster.getIp());
    cout << "Guardando distancias del bootmaster a cada IP ..." << endl;
    outputFile3.open("distancia_bootmaster.txt");
    for(int i=0; i<distancias.size(); i++){
        outputFile3 << "("<< distancias[i].first << ", " << distancias[i].second << ")" << endl;

    }
    outputFile3.close();
    
    cout << "La dirección IP que presumiblemente requiere más esfuerzo para que el boot master la ataque es: " << distancias[0].first << endl;

    return 0;
}