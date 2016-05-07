
#include <functional>
#include <exception>

#include "Application.h"

Application *app;

void __keyboard(unsigned char key, int x, int y)
{
	tanks::ButtonControlls button = tanks::ButtonControlls::NONE;

	if (key == 'w')
	{
		button = tanks::ButtonControlls::MOVE_UP;
		app->moving->move_forvard = true;
	}
		
	if (key == 's')
	{
		button = tanks::ButtonControlls::MOVE_DOWN;
		app->moving->move_back = true;
	}
		

	if (key == 'q')
	{
		button = tanks::ButtonControlls::TURN_LEFT;
		app->moving->move_left = true;
	}
	else if (key == 'e')
	{
		button = tanks::ButtonControlls::TURN_RIGHT;
		app->moving->move_right = true;
	}

	if (key == 'a')
	{
		button = tanks::ButtonControlls::MOVE_LEFT;
		app->moving->turn_left = true;
	}
	else if (key == 'd')
	{
		button = tanks::ButtonControlls::MOVE_RIGHT;
		app->moving->turn_right = true;
	}
		

	if (key == 'f')
		button = tanks::ButtonControlls::FIRE;
	else if (key == 'm')
		button = tanks::ButtonControlls::SHOW_MAP;
	else if (key == 'n')
		button = tanks::ButtonControlls::SHOW_GAME;
	else if((int)key == 27)
		button = tanks::ButtonControlls::ESCAPE;
	else if ((int)key == 13)
		button = tanks::ButtonControlls::ENTER;


	if (key == 'x')
		button = tanks::ButtonControlls::X_AXIS;
	else if (key == 'y')
		button = tanks::ButtonControlls::Y_AXIS;
	else if (key == 'z')
		button = tanks::ButtonControlls::Z_AXIS;
	if (key == 'c')
		button = tanks::ButtonControlls::CAMERA_CTRL;

	app->keyboard(button);
}

void __keyboard_up(unsigned char key, int x, int y)
{
	if (key == 'w')
		app->moving->move_forvard = false;
	else if (key == 's')
		app->moving->move_back = false;
	else if (key == 'q')
		app->moving->move_left = false;
	else if (key == 'e')
		app->moving->move_right = false;
	else if (key == 'a')
		app->moving->turn_left = false;
	else if (key == 'd')
		app->moving->turn_right = false;
	
	app->keyboard(tanks::ButtonControlls::NONE);
}


void __gamepad(unsigned int buttonMask, int x, int y, int z)
{
	if (y == 1000)
		app->moving->move_back = true;
	else if (y == -3)
		app->moving->move_back = false;

	if (y == -999)
		app->moving->move_forvard = true;
	else if (y == -3)
		app->moving->move_forvard = false;

	if (x == -999)
		app->moving->move_left = true;
	else if (x == 3)
		app->moving->move_left = false;

	if (x == 1000)
		app->moving->move_right = true;
	else if (x == 3)
		app->moving->move_right = false;


	if (z < 0)
	{
		app->moving->turn_left = true;
		app->moving->turn_right = false;
	}
	if (z > 0)
	{
		app->moving->turn_left = false;
		app->moving->turn_right = true;
	}
	if (z == 0)
	{
		app->moving->turn_left = false;
		app->moving->turn_right = false;
	}
		

	tanks::ButtonControlls button = tanks::ButtonControlls::NONE;

	if (buttonMask & GLUT_JOYSTICK_BUTTON_A)
		button = tanks::ButtonControlls::FIRE;
	else if (buttonMask & GLUT_JOYSTICK_BUTTON_B)
		button = tanks::ButtonControlls::SHOW_MAP;
	else if (buttonMask & GLUT_JOYSTICK_BUTTON_C)
		button = tanks::ButtonControlls::SHOW_GAME;
	//else if (buttonMask & GLUT_JOYSTICK_BUTTON_D)
	//	app->keyboard(tanks::GameControlls::FIRE);

	app->keyboard(button);
	std:cout << " x " << x << " y " << y << " z " << z << " buttonMask " << buttonMask << std::endl;
};

void __update()
{
	app->update();
}

void __display()
{
	auto fp = std::bind(&Application::display, app);
	GLoader::Display(fp);
}

void __reshape(int w, int h)
{
	GLoader::Reshape(w, h);
};


void __callbacks()
{
	glutKeyboardFunc(__keyboard);
	glutKeyboardUpFunc(__keyboard_up);

	glutDisplayFunc(__display);
	glutReshapeFunc(__reshape);
	glutIdleFunc(__update);

	glutJoystickFunc(__gamepad, 300);
	
	glutForceJoystickFunc();
}

int main(int argc, char** argv)
{
	try
	{
		GLoader *gl = new GLoader(argc, argv, "Tank");
		GLoader::EnableTexture();
		//GLoader::EnableLight();
		app = new Application();
		__callbacks();
		app->run();

	}
	catch (std::exception& e)
	{
		std::cout << " error " << &e << std::endl;
		std::cin.ignore();
	}

	return EXIT_SUCCESS;
}