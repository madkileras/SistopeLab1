#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cstdint>
#include <bits/stdc++.h>
#include <vector>
using namespace std;

class ImageControl{
	private:
		vector<vector<vector<int>>> image;
		int imageWidth;
		int imageHeight;

	public:
		//funcion que carga la imagen en la variable de la clase image
		unsigned char* loadBMP(char* filename); 
		
		//funcion que obtiene un vector que contiene el grado RGB del pixel señalado
		vector<int> getRGBpixel(int i,int j);

		
};