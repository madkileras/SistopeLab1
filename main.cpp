#include "imageControl.hpp"
#include <string>
int main(){
	string str= "imagen.bmp";
	char *cstr = &str[0u];


	ImageControl imageControl=ImageControl();
	imageControl.loadBMP(cstr);
	
	return 0;
}