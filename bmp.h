#ifndef BMP_H_
#define BMP_H_

#include <windows.h>		// Header File For Windows - has structures for BMP format
#include <stdio.h>    		// Header File For Standard Input/Output
#include <stdlib.h>

//typedef unsigned char       byte;

class AUX_RGBImageRec {
	void convertBGRtoRGB();
public:
	byte *data;
	DWORD sizeX;
	DWORD sizeY;
	bool NoErrors;
	AUX_RGBImageRec() : NoErrors(false), data(NULL) {};
	AUX_RGBImageRec(const char *FileName);
	~AUX_RGBImageRec();
	bool loadFile(const char *FileName);
	friend AUX_RGBImageRec *auxDIBImageLoad(const char *FileName);
	friend AUX_RGBImageRec *LoadBMP(const char *FileName);
};

#endif /* BMP_H_ */