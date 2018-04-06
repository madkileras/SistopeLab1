#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<iostream>
#include "imageControl.hpp"
#include <string>
using namespace std;
#define R 0
#define G 1
#define B 2
int main(int argc, char **argv){

    //DECLARACION DE VARIABLES PARA ARGUMENTOS RECIBIDOS
    //c:cantidad de imágenes ; u: umbral; n: umbral para clasificacion; b: bandera(?)
    int c,u,n,b;
    int opt;
    while((opt=getopt(argc, argv,"c:u:n:b:"))!=-1){
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
                b=atoi(optarg);
                break;
        }

    }

    //SE IMPRIMEN LOS VALORES RESCATADOS DESDE LA CONSOLA
    cout << endl;
    cout<<c<<" "<<u<<" "<<n<<" "<<b;
	string str= "tiger.bmp";
	char *cstr = &str[0u];
	ImageControl imageControl=ImageControl();
	imageControl.loadBMP(cstr);


    cout << imageControl.getRGBpixel(0,0)[R]<<endl;

	return 0;
}
                                                                                                                                                                                                                                                                                                                                                                                                                                                                