#ifndef SCENE_H_
#define SCENE_H_

#include <iostream>
#include <map>

#include "../GLoader.h"
#include "../ObjectFactory.h"
#include "../MapStream.h"
#include "../model/Camera.h"
#include "../Settings.h"

class Scene {
public:
	enum SceneType
	{
		LEVEL1,
		LEVEL2,
		LEVEL3,
		MENU,
		HELP,
		LOADING,
		SETTINGS,
		AEDITOR
	};

	tanks::GameSettings * m_settings;
private:
	SceneType stype;
protected:
	bool redispaly;
	Camera *camera;
public:
	//std::map<std::string, GameObject*> game_objects;
	std::vector<GameObject*> game_objects;
	bool inited;

	Scene(SceneType level, tanks::GameSettings * settings):
		stype(level), m_settings(settings) {
		redispaly = false;
		inited = false;
	};

	~Scene()
	{
		/*for (go_it_type it = game_objects.begin(); it != game_objects.end();) {
			delete it->second;
			it = game_objects.erase(it);
		}
		*/
		for (std::vector<GameObject*>::iterator it = game_objects.begin(); it != game_objects.end();) {
			delete *it;
			it = game_objects.erase(it);
		}
	};

	void clean()
	{
		/*for (go_it_type it = game_objects.begin(); it != game_objects.end();) {
			GameObject* go = it->second;
			if (!go->state == GameObject::ObjectState::DESTROYED) {
				delete go;
				it = game_objects.erase(it);
			}
			else
				++it;
		}
		*/
		for (std::vector<GameObject*>::iterator it = game_objects.begin(); it != game_objects.end();) {
			if (!(*it)->state == GameObject::ObjectState::DESTROYED) {
				delete *it;
				it = game_objects.erase(it);
			}
			else
				++it;
		}
	};
	/*
	method to init all Game Objects 
	*/
	virtual void init() = 0;
	/*
		method to handle of a all Game Objects behavior
	*/
	virtual void play(float delta_time, tanks::MoveControlls * moving) = 0;
	/*
		method to update positions of a all Game Objects 
	*/
	virtual void update() = 0;
	/*
		method to display new positions of a all Game Objects
	*/
	virtual void display() = 0;
	/*
		method to handle of the user's input 
	*/
	virtual void keyboard(tanks::ButtonControlls button) = 0;


	SceneType getType() { return stype; }
	bool isRedisplay() { return redispaly; }
	Camera* getCamera() { return camera; }

	void set_init()
	{
		inited = true;
	};
	bool get_init()
	{
		return inited;
	};
};


#endif /* SCENE_H_ */