#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdint>
#include <bits/stdc++.h>
using namespace std;

class ImageControl{
	private:
		unsigned char* image;

	public:
		//funcion que carga la imagen en la variable de la clase image
		unsigned char* loadBMP(char* filename); 
		//funcion que realiza una lectura completa de la imagen

		
};