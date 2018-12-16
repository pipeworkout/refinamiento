/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <fstream>
#include <iostream>
#include <math.h>
#include <vector>
#define PI 3.14159265
using namespace std;

struct coordenada{
    float x;
    float y;
};


void angulos(coordenada a, coordenada b, coordenada c, float &anguloA, float &anguloB, float &anguloC){
    coordenada AB, BC, CA;
    AB.x = b.x - a.x;
    AB.y = b.y - a.y;
    BC.x = c.x - b.x;
    BC.y = c.y - b.y;
    CA.x = a.x - c.x;
    CA.y = a.y - c.y;
    float moduloAB = sqrt((AB.x * AB.x) + (AB.y * AB.y));
    float moduloBC = sqrt((BC.x * BC.x) + (BC.y * BC.y));
    float moduloCA = sqrt((CA.x * CA.x) + (CA.y * CA.y));
    float escalarABCA = (AB.x * CA.x) + (AB.y * CA.y);
    float escalarABBC = (AB.x * BC.x) + (AB.y * BC.y);
    float escalarBCCA = (BC.x * CA.x) + (BC.y * CA.y);
 
    float anguloARad = acos (fabs(escalarABCA/(moduloAB * moduloCA)));
    float anguloBRad = acos (fabs(escalarABBC/(moduloAB * moduloBC)));
    float anguloCRad = acos (fabs(escalarBCCA/(moduloBC * moduloCA)));
    anguloA = (anguloARad * 180) / PI;
    anguloB = (anguloBRad * 180) / PI;
    anguloC = (anguloCRad * 180) / PI;
    
}

void lados(coordenada a, coordenada b, coordenada c, float &ladoAB, float &ladoBC, float &ladoCA){
    ladoAB = sqrt(pow((b.x - a.x), 2) + pow((b.y - a.y), 2));
    ladoBC = sqrt(pow((c.x - b.x), 2) + pow((c.y - b.y), 2));
    ladoCA = sqrt(pow((c.x - a.x), 2) + pow((c.y - a.y), 2));
}

void separar(string linea, string &n1, string &n2, string &n3){
    vector<string> nodos;
    size_t found,found2;

    //string cadena ="2132312314535647484 123312 2233124";
    found = linea.find(" ");
    found2 = linea.find(" " , found+1);
    nodos.push_back(linea.substr(0,found));
    nodos.push_back(linea.substr(found+1,found2-found-1));
    nodos.push_back(linea.substr(found2+1,linea.size()));
    n1 = nodos[0];
    n2 = nodos[1];
    n3 = nodos[2];
}

void leer(){
    string rutaEntradaMesh = "/home/pipeworkout/Escritorio/espiral.mesh";
    string rutaEntradaNode = "/home/pipeworkout/Escritorio/espiral.node";
    string lineaMesh;
    string lineaNode;
    coordenada coordNodo1, coordNodo2, coordNodo3;
    
    ifstream archivo_mesh;
    ifstream archivo_node;
    
    float anguloPrueba = 40.35;
    
    archivo_mesh.open(rutaEntradaMesh, ios::in); //abriendo archivo modo lectura
    archivo_node.open(rutaEntradaNode, ios::in);
    
    if(archivo_mesh.fail() || archivo_node.fail()){
        //si no se puede abrir el archivo o crear se termina el programa
        cout<<"Error con los archivos!"<<endl;
    }
    else{
        getline(archivo_mesh, lineaMesh);
        while(getline(archivo_mesh, lineaMesh)){ //recorre archivo txt  
            float anguloA, anguloB, anguloC;
            float ladoAB, ladoBC, ladoCA;
            string nodo1, nodo2, nodo3;
            separar(lineaMesh, nodo1, nodo2, nodo3);
            while(getline(archivo_node, lineaNode)){
                string nodo, valorX, valorY;
                separar(lineaNode, nodo, valorX, valorY);
                if(nodo1 == nodo){
                    coordNodo1.x = stof(valorX);
                    coordNodo1.y = stof(valorY);
                }
                if(nodo2 == nodo){
                    coordNodo2.x = stof(valorX);
                    coordNodo2.y = stof(valorY);
                }
                if(nodo3 == nodo){
                    coordNodo3.x = stof(valorX);
                    coordNodo3.y = stof(valorY);
                }
            }
            archivo_node.clear();
            archivo_node.seekg(0, ios::beg);
            angulos(coordNodo1, coordNodo2, coordNodo3, anguloA, anguloB, anguloC);
            if(anguloA <= anguloPrueba || anguloB <= anguloPrueba || anguloC <= anguloPrueba){
                coordenada nuevoNodo;
                lados(coordNodo1, coordNodo2, coordNodo3, ladoAB, ladoBC, ladoCA);
                if(ladoAB >= ladoBC && ladoAB >= ladoCA){
                    nuevoNodo.x = (coordNodo1.x + coordNodo2.x) / 2;
                    nuevoNodo.y = (coordNodo1.y + coordNodo2.y) / 2;
                }
                if(ladoBC >= ladoAB && ladoBC >= ladoCA){
                    nuevoNodo.x = (coordNodo2.x + coordNodo3.x) / 2;
                    nuevoNodo.y = (coordNodo2.y + coordNodo3.y) / 2;
                }
                if(ladoCA >= ladoBC && ladoCA >= ladoAB){
                    nuevoNodo.x = (coordNodo3.x + coordNodo1.x) / 2;
                    nuevoNodo.y = (coordNodo3.y + coordNodo1.y) / 2;
                }       
            }
            
            //cout << nodo1 << ", "<< nodo2 << ", "<< nodo3 << endl;
        }
    }
    archivo_mesh.close();
    archivo_node.close();
}

