#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdint>
#include <bits/stdc++.h>
#include <vector>
using namespace std;
#define R 0
#define G 1
#define B 2
#define A 3

class ImageControl{
	private:
		int*** image;
		int*** byn;
		int*** escala;
		char type[2];
		int tam;
		int reservado;
		int offset;
		int tamMet;
		int imageWidth;
		int imageHeight;
		short bits;
		short prof;
		short numeroP;
		int compresion;
		int estructura;
		int pxmh;
		int pxmv;
		int coloresUsados;
		int coloresImportantes;
		unsigned char *header;


	public:
		//constructor
		ImageControl(void);
		//funcion que carga la imagen en la variable de la clase image
		unsigned char* loadBMP(char* filename);

		//funcion que obtiene un vector que contiene el grado RGB del pixel señalado
		int* getRGBpixel(int i,int j);

		//funcion que genera la imagen en blanco y negro
		void blancoYnegro(int umbral);

        void escalaGrises();
		int lum(int* pixel);

		//Función que guarda una imagen en un archivo BMP
		//Recibe el nombre del archivo de salida y un TAG, que corresponde a si necesita guarda
		//una imagen normal, en blanco y negro, o en escala de grises
		int saveImage(char *filename, int tag);

		//Función que determina si la imagen es nearly black o no
		//Retorna un booleano, true si es nearlyBlack o false si no
		bool nearlyBlack(int umbral);

		//Función que libera las imágenes del objeto
		int freeImages();

		~ImageControl(void);

};
