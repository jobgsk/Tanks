#ifndef GLOADER_H_
#define GLOADER_H_

#include <functional>
#include <iostream>
//#include "Application.h"
//#include "tga.h"
#include "bmp.h"
#include <GL/glut.h>

class GLoader {
public:
	static int winid;
	GLoader(int myargc, char** myargv, const char *app_name);
	~GLoader();

	static void Display(std::function<void()> fun);
	static void Reshape(int w, int h);
	/*
		cx, cy, cz,   // Camera position
		px, py, pz,    // Look at point
	*/
	static void Camera(float cx, float cy, float cz, float px, float py, float pz);
	static void Redispaly();
	
	static void EnableLight();
	static void DisableLight();
	static void EnableTexture();
	static GLuint LoadTexture(const char *TexName);

	static void Run();
	static void Clean();
	static void Exit();

};

#endif /* GLOADER_H_ */