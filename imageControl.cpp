#include "imageControl.hpp"

#define R 0
#define G 1
#define B 2
#define A 3

ImageControl::ImageControl(void)
{
    ;
}

//LEE PIXEL POR PIXEL Y LO GUARDA EN UNA MATRIZ ENTERA RGB
//RETORNA UNA MATRIZ
unsigned char *  ImageControl::loadBMP(char* filename){

    FILE* f = fopen(filename, "rb");
    if(f == NULL)
        throw "Argument Exception";
  
    fseek(f,0, SEEK_SET);
    fread(type, sizeof(char), 2, f);
    strcpy(type,"BM");
    //cout << "type " << type << endl;
    fread(&tam, sizeof(int), 1, f);
    //cout << "tam " << tam << endl;
    //reservado=*(int*)&info[6];
    fread(&reservado, sizeof(int), 1, f);
    //cout << "reservado " << reservado << endl;
    fread(&offset, sizeof(int), 1, f);
    //cout << "offset " << offset << endl;
    //fread(tam, sizeof(int), 1, f);
    //reservado=aux2;
    fread(&tamMet, sizeof(int), 1, f);
    //cout << "imageWidth " << imageWidth << endl;
    fread(&imageHeight,sizeof(int),1, f);
    fread(&imageWidth,sizeof(int),1, f);
    //cout << "imageHeight " << imageHeight << endl;
    fread(&numeroP, sizeof(short), 1, f);
    fread(&prof, sizeof(short), 1, f);
    fread(&compresion, sizeof(int), 1, f);
    fread(&estructura, sizeof(int), 1, f);
    fread(&pxmh, sizeof(int), 1, f);
    fread(&pxmv, sizeof(int), 1, f);
    fread(&coloresUsados, sizeof(int), 1, f);
    fread(&coloresImportantes, sizeof(int), 1, f);
    fseek(f,0, SEEK_SET);
    //offset=121;
    fread(&header, sizeof(unsigned char), offset, f);

    //cout << type << endl;


    image = (int***)malloc(sizeof(int**)*imageHeight);
    int row_padded = (imageWidth*4 + 4) & (~4);
    //cout << "row row_padded " << row_padded << endl;
    unsigned char* data = new unsigned char[row_padded];
   
    int j=0;
    //cout << (imageWidth-1)*3;
    for(int i = 0; i < imageHeight; i++)
    {
        //cout << "tengo un i: "<<i<<endl;
       //cout << "Se cayo aquí"<<endl;
        image[i]=(int**)malloc(sizeof(int*)*imageWidth);
        fread(data, sizeof(unsigned char), row_padded, f);

        for(j = 0; j < imageWidth*4; j += 4)
        {
            //cout << "Se cayo acá"<<endl;
            //cout << j << endl;;
          // Convert (B, G, R) to (R, G, B)

            image[i][j/4]=(int*)malloc(sizeof(int)*4);
            //cout << "aqui: " << image[i][j/3] << " i: " << i <<" j: " << j << endl;
            image[i][j/4][B]=(int)data[j];
            //cout << "image2 " << image[i][j/3][R] << endl;
            image[i][j/4][G]=(int)data[j+1];
            image[i][j/4][R]=(int)data[j+2];
            image[i][j/4][A]=(int)data[j+3];
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
            byn[i][j]=(int*)malloc(sizeof(int)*4);
            if(lum(getRGBpixel(i,j))>umbral){
                byn[i][j][B]=255;
                byn[i][j][R]=255;
                byn[i][j][G]=255;
                byn[i][j][A]=255;
            }
            else{
                byn[i][j][B]=0;
                byn[i][j][R]=0;
                byn[i][j][G]=0;
                byn[i][j][A]=255;
            }
        }
    }
    return;
}

void ImageControl::escalaGrises(){
    escala= (int***)malloc(sizeof(int**)*imageHeight);
    for (int i=0;i< imageHeight;i++){
        escala[i]=(int**)malloc(sizeof(int*)*imageWidth);
        for(int j=0;j<imageWidth;j++){
                escala[i][j]=(int*)malloc(sizeof(int)*4);
                //cout << lum(getRGBpixel(i,j))<<endl;
                escala[i][j][B]=lum(getRGBpixel(i,j));
                escala[i][j][R]=lum(getRGBpixel(i,j));
                escala[i][j][G]=lum(getRGBpixel(i,j));
                escala[i][j][A]=image[i][j][A];


        }
    }
    return;
}

int ImageControl::lum(int * pixel){
    return pixel[R]*0.3+pixel[G]*0.59+pixel[B]*0.11;
}

int ImageControl::saveImage(char *filename, int tag){
   
    FILE *prueba;
    prueba=fopen(filename,"wb");
    fwrite(&header,1,offset,prueba);
    if (true){
        //cout << "Height " << imageHeight << endl;
        //cout << "Width " << imageWidth << endl;
        for(int i=0; i<imageHeight ; i++)
        {
            for(int j = 0; j < imageWidth*4; j += 4)
            {
                if(tag==0){
                    fwrite(&(image[i][j/4][B]),sizeof(unsigned char),1,prueba);
                    fwrite(&(image[i][j/4][G]),sizeof(unsigned char),1,prueba);
                    fwrite(&(image[i][j/4][R]),sizeof(unsigned char),1,prueba);
                    fwrite(&(image[i][j/4][A]),sizeof(unsigned char),1,prueba);

                }
                else if(tag==1){

                    fwrite(&(byn[i][j/4][B]),sizeof(unsigned char),1,prueba);
                    fwrite(&(byn[i][j/4][G]),sizeof(unsigned char),1,prueba);
                    fwrite(&(byn[i][j/4][R]),sizeof(unsigned char),1,prueba);
                    fwrite(&(byn[i][j/4][A]),sizeof(unsigned char),1,prueba);
                }
                else{

                    fwrite(&(escala[i][j/4][B]),sizeof(unsigned char),1,prueba);
                    fwrite(&(escala[i][j/4][G]),sizeof(unsigned char),1,prueba);
                    fwrite(&(escala[i][j/4][R]),sizeof(unsigned char),1,prueba);
                    fwrite(&(escala[i][j/4][A]),sizeof(unsigned char),1,prueba);
                }


              
            }

        }
    }
    fclose(prueba);
    return 0;
}

bool ImageControl::nearlyBlack(int umbral){
    //cout << "Entraste a nearlyBlack" << endl;

    int countBlack=0;
    int countWhite=0;
    for(int i=0; i<imageHeight ; i++)
    {
        for(int j = 0; j < imageWidth; j++)
        {
            if((image[i][j][R]*0.3+image[i][j][G]*0.59+image[i][j][B]*0.11)>umbral){
                countBlack++;
            }
            else{
                countWhite++;
            }
        }
    }

    if(countBlack>countWhite){
        return true;
    }
    else{
        return false;
    }
    return true;

}
int ImageControl::freeImages(){
    for(int i=0; i<imageHeight ; i++)
    {
        for(int j = 0; j < imageWidth; j++)
        {
            free(&image[i][j][B]);
            free(&image[i][j][R]);
            free(&image[i][j][G]);
            free(&image[i][j][A]);
            free(&image[i][j]);

            free(&byn[i][j][B]);
            free(&byn[i][j][R]);
            free(&byn[i][j][G]);
            free(&byn[i][j][A]);
            free(&byn[i][j]);

            free(&escala[i][j][B]);
            free(&escala[i][j][R]);
            free(&escala[i][j][G]);
            free(&escala[i][j][A]);
            free(&escala[i][j]);
        }
        
        free(&image[i]);
        free(&byn[i]);
        free(&escala[i]);
       
        
    }
     free(&image);
        free(&byn);
        free(&escala);
    return 0;
}


ImageControl::~ImageControl(void)
{
    ;
}
