#include "stdafx.h"
#include "FreeImage.h"
#include <iostream>
#define BPP 24 // Since we're out putting three 8 bit RGB values
using namespace std ;






int main (int argc , char *argv []){
	
	
	
	
	FreeImage_Initialise();
	FIBITMAP* bitmap = FreeImage_Allocate(WIDTH, HEIGHT, BPP);
	RGBQUAD color ;
	if(!bitmap)
		exit(1); //WTF?! We can ' t even a l l o c a te images ? Die !
	//Draws a gr a d ient from bl u e to green :
	for ( int i =0; i<WIDTH; i++) {
		for ( int j =0; j<HEIGHT; j++) {
			color.rgbRed = 0;
			color.rgbGreen = (double ) i / WIDTH  * 255.0;
			color.rgbBlue  = (double ) j / HEIGHT * 255.0;
			FreeImage_SetPixelColor ( bitmap , i , j ,&color );
			// Notice how we ' re c a l l i n g the & operator on " c o l o r "
			// so t h a t we can pass a p o inter to the c o l o r s t r u ct .
		}
	}
	if ( FreeImage_Save (FIF_PNG, bitmap , " test.png" , 0))
		cout << "Image s u c c e ssf u l l y saved ! " << endl ;
	FreeImage_DeInitialise(); //Cleanup !
	cin.get();
}