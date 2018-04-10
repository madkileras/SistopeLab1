#include "imageControl.hpp"

ImageControl::ImageControl(void)
{
    ;
}

//LEE PIXEL POR PIXEL Y LO GUARDA EN UNA MATRIZ ENTERA RGB
//RETORNA UNA MATRIZ    
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
    bits=*(short*)&info[28];
    cout << endl;
    cout << "  Nombre del archivo: " << filename << endl;
    cout << "  Ancho: " << imageWidth << endl;
    cout << "  Largo: " << imageHeight << endl;
    cout << "  Bits: " << bits << endl;

    image = (int***)malloc(sizeof(int**)*imageHeight); 
    int row_padded = (imageWidth*3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;  
    int j=0;
    //cout << (imageWidth-1)*3;
    for(int i = 0; i < imageHeight; i++)
    {
        //cout << "tengo un i: "<<i<<endl;
       //cout << "Se cayo aquí"<<endl;
        image[i]=(int**)malloc(sizeof(int*)*imageWidth);   
        fread(data, sizeof(unsigned char), row_padded, f);

        for(j = 0; j < imageWidth*3; j += 3)
        {
            //cout << "Se cayo acá"<<endl;
            //cout << j << endl;;
          // Convert (B, G, R) to (R, G, B)
            tmp = data[j];
            data[j] = data[j+2];
            data[j+2] = tmp;
            
            image[i][j/3]=(int*)malloc(sizeof(int)*3);
            image[i][j/3][R]=(int)data[j]; 
            image[i][j/3][G]=(int)data[j+1];
            image[i][j/3][B]=(int)data[j+2];
            //cout << "R: "<< (int)data[j] << " G: " << (int)data[j+1]<< " B: " << (int)data[j+2]<< endl;
        }
        //cout<<"sali del ciclo "<<j<<" con i "<<i<<endl;      
        
    }
    //out <<"finciclo";
    fclose(f);
    return data;
}

int* ImageControl::getRGBpixel(int i,int j){
    return image[i][j];    
}

void ImageControl::blancoYnegro(int umbral){
    byn= (int***)malloc(sizeof(int**)*imageHeight);
    for (int i=0;i< imageHeight;i++){
        byn[i]=(int**)malloc(sizeof(int*)*imageWidth); 
        for(int j=0;j<imageWidth;j++){
            byn[i][j]=(int*)malloc(sizeof(int)*3);
            if(lum(getRGBpixel(i,j))>umbral){
                byn[i][j][R]=255;
                byn[i][j][G]=255;
                byn[i][j][B]=255;
            }
            else{
                byn[i][j][R]=0;
                byn[i][j][G]=0;
                byn[i][j][B]=0;
            }
        }
    }
    return;
}

int ImageControl::lum(int * pixel){
    return pixel[R]*0.3+pixel[G]*0.59+pixel[B]*0.11;
}

ImageControl::~ImageControl(void)
{
    ; 
}