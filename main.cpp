#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include "imageControl.hpp"
#include <string>
using namespace std;
#define R 0
#define G 1
#define B 2
#define A 3
int main(int argc, char **argv){
    
    //DECLARACION DE VARIABLES PARA ARGUMENTOS RECIBIDOS
    //c:cantidad de imágenes ; u: umbral; n: umbral para clasificacion; b: bandera(?)
    int c,u,n,b=0;
    int opt;
    while((opt=getopt(argc, argv,"c:u:n:b"))!=-1){
        //SE ASIGNAN LOS VALORES DE LA CONSOLA A LAS VARIABLES DEFINIDAS
        switch(opt){
            case 'c':
                c=atoi(optarg);
                break;
            case 'u':
                u=atoi(optarg);
                break;
            case 'n':
                n=atoi(optarg);
                break;
            case 'b':
                b++;
        }

    }
    //cout << "hello hello" << endl;

    int i=0;
    //Se reserva memoria para guardar los valores de nearlyBlack de cada imagen
    int *nbValues=(int*)malloc(sizeof(int)*c);
    std::string in;
    std::string out;
    char *inF;
    char *outF;
    //Se recorren todas la imagenes, se procesan y se guardan
    while(i<c){
        in="imagen_"+std::to_string(i+1)+".bmp";
        out="imagenSalida_"+std::to_string(i+1)+".bmp";
        inF=&in[0u];
        outF=&out[0u];
        cout << "nombre entrada " << inF << endl;
        cout << "nombre salida " << outF << endl;
        ImageControl received;
        received.loadBMP(inF);
        received.blancoYnegro(u);
        received.escalaGrises();
        received.saveImage(outF,1);
        if(received.nearlyBlack(n)){
            nbValues[i+1]=1;
        }
        else{
            nbValues[i+1]=0;
        }
        //received.freeImages();
        i++;
        
        
    }
    
    if(b){ //Se imprimen los resultados de nearlyBlack de cada imágen
        cout << endl << "Resultados:" << endl;
        cout << "|    image    |    nearly_black    |"<<endl;
        cout << "|-------------|--------------------|"<<endl;
        
        for(i=1;i<c+1;i++){
            if (nbValues[i]==0){
                cout << "|   imagen_" << i << "  | nearlyBlack: yes   |" << endl;
                
            }
            else{
                cout << "|   imagen_" << i << "  | nearlyBlack: no    |" << endl;  
            }
        }
    }
    
   
  

  
    return 0;
}

