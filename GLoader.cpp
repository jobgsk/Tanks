#include "GLoader.h"

int GLoader::winid = -1;

GLoader::GLoader(int myargc, char** myargv, const char *app_name)
{
	glutInit(&myargc, myargv);

	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 50);
	GLoader::winid = glutCreateWindow(app_name);

	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	//glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	//glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	//glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//std::cout << " GLoader::GLoader " << std::endl;
}

void GLoader::Reshape(int w, int h)
{
	/*if (h == 0)
	h = 1;
	float ratio = w * 1.0 / h;


	glMatrixMode(GL_PROJECTION);
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(65.0f, ratio, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	*/
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Set the correct perspective.
	gluPerspective(60.0, (double)w / (double)h, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
}

void GLoader::Camera(float cx, float cy, float cz, float px, float py, float pz)
{
	//gluLookAt(2000.0, 20000.0, 2000.0,   // Camera position
	//0.0, 0.0, 0.0,    // Look at point
	//0.0, 1.0, 0.0);   // Up vector
	
	/*std::cout << " Camera "
		<< " cx " << cx 
		<< " cy " << cy
		<< " cz " << cz
		<< " px " << px
		<< " py " << py
		<< " pz " << pz << std::endl;
	*/
	// Set the camera position and lookat point
	gluLookAt(cx, cy, cz,   // Camera position
		px, py, pz,    // Look at point
		0.0, 1.0, 0.0);   // Up vector
	
}

void GLoader::Display(std::function<void()> dispaly)
{
	//SkyBlue = color red 0.196078 green 0.6 blue 0.8
	glClearColor(0.196078f, 0.6f, 0.8f, 0.0f);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	dispaly();

	glFlush();
	glutSwapBuffers();
}

void GLoader::Redispaly()
{
	glutPostRedisplay();
}

void GLoader::EnableTexture()
{
	glEnable(GL_TEXTURE_2D);	// Enable Texture Mapping
}

void GLoader::EnableLight()
{
	//Color for ambient light
	GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //white
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);

	//Color for positioned light
	GLfloat lightColor[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //white collor
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor);

	GLfloat secular[] = { 1.0f, 0.0f, 0.0f, 1.0 }; //red
	glLightfv(GL_LIGHT0, GL_SPECULAR, secular);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

}

void GLoader::DisableLight()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}

void GLoader::Run()
{
	glutMainLoop();
}

void GLoader::Exit()
{
	glutDestroyWindow(GLoader::winid);
}

GLoader::~GLoader()
{
	Exit();
}

GLuint GLoader::LoadTexture(const char *TexName)	// Load Bitmaps And Convert To Textures
{
	GLuint Texture;
	AUX_RGBImageRec *TextureImage[1];				// Create Storage Space For The Texture
	memset(TextureImage, 0, sizeof(void *) * 1);	// Set The Pointer To NULL

	// Load The Bitmap, Check For Errors, If Bitmap's Not Found Quit
	if (TextureImage[0] = LoadBMP(TexName)) // LoadBMP("grass.bmp"))
	{
		glGenTextures(1, &Texture);					// Create The Texture
		glBindTexture(GL_TEXTURE_2D, Texture);		// Typical Texture Generation Using Data From The Bitmap

		glTexImage2D(GL_TEXTURE_2D, 0, 3,
			TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0,
			GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);

		// Specify filtering and edge actions
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	}
	else
	{
		return -1;
	}

	if (TextureImage[0])									// If Texture Exists
	{
		if (TextureImage[0]->data)							// If Texture Image Exists
		{
			free(TextureImage[0]->data);					// Free The Texture Image Memory
		}
		free(TextureImage[0]);								// Free The Image Structure
	}

	std::cout << " GLoader::LoadTexture " << std::endl;
	return Texture;											// Return The Status
}

/*
	TGA Loader
*/
/*GLuint GLoader::LoadTexture(const char *TexName)
{
	TGAImg Img;        // Image loader
	GLuint Texture;

	// Load our Texture
	if (Img.Load(TexName) != IMG_OK)
		return -1;

	glGenTextures(1, &Texture);            // Allocate space for texture
	glBindTexture(GL_TEXTURE_2D, Texture); // Set our Tex handle as current

	// Create the texture
	if (Img.GetBPP() == 24)
		glTexImage2D(GL_TEXTURE_2D, 0, 3, 
			Img.GetWidth(), Img.GetHeight(), 0,
			GL_RGB, GL_UNSIGNED_BYTE, Img.GetImg());
	else if (Img.GetBPP() == 32)
		glTexImage2D(GL_TEXTURE_2D, 0, 4, 
			Img.GetWidth(), Img.GetHeight(), 0,
			GL_RGBA, GL_UNSIGNED_BYTE, Img.GetImg());
	else
		return -1;


	// Specify filtering and edge actions
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	std::cout << " GLoader::LoadTexture " << std::endl;

	return Texture;
}
*/