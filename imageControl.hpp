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

		int lum(int* pixel);

		int saveImage(char *filename);

		//funcion que guarda una imagen

		~ImageControl(void);
	
};