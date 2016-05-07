#ifndef APPLICATION_H_
#define APPLICATION_H_	

#include <iostream>

#include "GLoader.h"
#include "SceneManager.h"

#include <GL/glut.h>

/*
	#####################################
	Include it ones only in the main file
	#####################################
*/
class Application
{
private:
	SceneManager * sm;
	float base_time;
public:
	tanks::MoveControlls * moving;

	/*
		Load resourses
	*/
	Application()
	{
		sm = new SceneManager();
		moving = new tanks::MoveControlls();
	}
	/*
		Run Game loop
	*/
	void run()
	{
		base_time = glutGet(GLUT_ELAPSED_TIME);
		GLoader::Run();
	}
	/*
		render all objects in the scene
	*/
	void display()
	{
		Scene* current_scene = sm->getCurrent();
		
		Camera *camera = current_scene->getCamera();
		Vector3<float> c_position = camera->getPosition();
		Vector3<float> c_direction = camera->getDirection();
		GLoader::Camera(
			c_position.x, c_position.y, c_position.z, 
			c_direction.x, c_direction.y, c_direction.z);

		current_scene->display();
	};
	/*
		update positions of all objects in the scene 
	*/
	void update()
	{
		float time = glutGet(GLUT_ELAPSED_TIME);
		float delta = (time - base_time);

		// Find the duration of the last frame in seconds
		//float duration = delta * 0.0001f;
		//if (duration <= 0.00f) return;
		//else if (duration > 0.005f) duration = 0.005f;

		sm->init_scene();
		Scene* current_scene = sm->getCurrent();
		current_scene->play(delta, moving);
		current_scene->update();

		if (current_scene->isRedisplay())
		{
			GLoader::Redispaly();
		}
		base_time = time;
	};
	/*
		handle keys events or pass them to the current scene  
	*/
	void keyboard(tanks::ButtonControlls button)
	{
		try
		{
			sm->keyboard(button);
		}
		catch (ExitException& e)
		{
			cout << e.what() << '\n';
			quit();
			return;
		}
	};

	void quit()
	{
		delete sm;
		GLoader::Exit();
		exit(0);
	}
};


#endif /* APPLICATION_H_ */