#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <string>

#include "math_helper.h"

#include "GLoader.h"
#include "StaticModelLoader.h"
#include "Vector3.h"
#include "Matrix4.h"
#include "PhysicsBody.h"
#include "render.h"
#include "Settings.h"

class GameObject {

private:
	//void draw_poligon(int i);

protected:

	//ModelsStruct *model;
	//Matrix4<float> matrix;

public:
	int m_id;
	tanks::ModelType m_type;

	GameObject* parent;
	virtual void sync_parent(){};
	
	std::vector<GameObject*> childs;
	virtual void add_child(GameObject* obj)
	{
		childs.push_back(obj);
	};

	std::vector<GameObject*> m_interacts;
	virtual void add_interacts(std::vector<GameObject*> interacts)
	{
		for (int i = 0; i < interacts.size(); i++)
		{
			GameObject * go = interacts[i];
			if (go == this)
				continue;
			m_interacts.push_back(go);
		}
	};

	GameObject *m_instigator;
	void set_instigator(GameObject * instigator)
	{
		m_instigator = instigator;
	}

	enum ObjectState
	{
		ACTIVE,
		DESTROYED,
		CHANGED,
		WAITING
	};
	ObjectState state;

	PhysicsBody * m_body;
	Render * m_render;

	PhysicsBody m_default_body;
	virtual void redefine() 
	{
		m_body = &m_default_body;
		state = ObjectState::ACTIVE;
	}
	
	GameObject(int id, tanks::ModelType type):
		m_id(id), m_type(type)
	{
		m_body = new PhysicsBody();
		state = ObjectState::ACTIVE;
	};
	
	GameObject(Render * render, PhysicsBody * body, int id, tanks::ModelType type) :
		m_id(id), m_type(type)
	{
		m_render = render;
		m_body = body;

		state = ObjectState::ACTIVE;

		m_default_body = *m_body;
		//StaticModelLoader* loader = obj->model->loader;
		//model = CopyModel(loader);
		//init();
	};
	
	//GameObject(char *p, char *m)
	//{
		//StaticModelLoader* loader = new StaticModelLoader(p, m);
		//model = CopyModel(loader);
	//	init();
	//};
	
	virtual ~GameObject();

	//void load_texture(const char * dir_name);
	virtual void draw()
	{
		m_render->render();

		for (int i = 0; i < childs.size(); i++) {
			childs[i]->draw();
		}
	};

	virtual void update()
	{
		((MeshRender*)m_render)->m_matrix.init();
		((MeshRender*)m_render)->m_matrix.translate(
			m_body->m_position.x, m_body->m_position.y, m_body->m_position.z);
		((MeshRender*)m_render)->m_matrix.rotate(
			m_body->m_angle.x, m_body->m_angle.y, m_body->m_angle.z);

		for (int i = 0; i < childs.size(); i++) 
		{
			childs[i]->update();
		}
	};
	
	virtual void play(float delta_time) {};

	Vector3<float> getDirection() 
	{ 
		return Vector3<float>(
			m_body->m_direction.x,
			m_body->m_direction.y,
			m_body->m_direction.z);
	};

	Vector3<float> getPosition() 
	{ 
		return Vector3<float>(
			m_body->m_position.x,
			m_body->m_position.y,
			m_body->m_position.z);
	};
};

typedef std::map<std::string, GameObject*>::iterator go_it_type;


#endif /* GAMEOBJECT_H_ */