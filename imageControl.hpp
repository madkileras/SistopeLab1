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
		int imageWidth;
		int imageHeight;

	public:
		//funcion que carga la imagen en la variable de la clase image
		unsigned char* loadBMP(char* filename); 
		
		//funcion que obtiene un vector que contiene el grado RGB del pixel señalado
		int* getRGBpixel(int i,int j);

		//funcion que genera la imagen en blanco y negro
		void blancoYnegro(int umbral);

		int lum(int* pixel);
		
};