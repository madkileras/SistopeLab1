#include "imageControl.hpp"

unsigned char *  ImageControl::loadBMP(char* filename){
	int i;
    FILE* f = fopen(filename, "rb");
    if(f == NULL)
        throw "Argument Exception";
    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
    // extract image height and width from header
    imageWidth = *(int*)&info[18];
    imageHeight = *(int*)&info[22];
    cout << endl;
    cout << "  Nombre del archivo: " << filename << endl;
    cout << "  Ancho: " << imageWidth << endl;
    cout << "  Largo: " << imageHeight << endl;
    image = (int***)malloc(sizeof(int**)*imageHeight); 
    int row_padded = (imageWidth*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;  
    for(int i = 0; i < imageHeight; i++)
    {
        image[i]=(int**)malloc(sizeof(int*)*imageWidth);   
        fread(data, sizeof(unsigned char), row_padded, f);
        for(int j = 0; j < imageWidth*3; j += 3)
        {
          // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;
            image[i][j/3]=(int*)malloc(sizeof(int)*3);
            image[i][j/3][0]=(int)data[j]; 
            image[i][j/3][0]=(int)data[j+1];
            image[i][j/3][0]=(int)data[j+2];

            //cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
        }      
    }
    fclose(f);
    return data;
}

int* ImageControl::getRGBpixel(int i,int j){
    return image[i][j];    
}
