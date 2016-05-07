#ifndef TANK_H_
#define TANK_H_

#include <deque>

#include "Terrain.h"
#include "House.h"
#include "TankTower.h"

#include "../GameObject.h"
#include "../StraightForce.h"
#include "../Settings.h"

#include <SFML/Audio/Sound.hpp>

class Tank : public GameObject {
public:
	
	TankTower* tower;

	GravityForce *gf;
	StraightForce *sf;
	AngleForce *af;
	std::vector<PhysicsForce*> forces;

	std::deque<GameObject*> *m_bullets1_holder;
	std::deque<GameObject*> *m_bullets2_holder;
	std::deque<GameObject*> *m_bullets3_holder;

	int m_helth;
	int m_hits;
	int m_kills;

	float shoot_delay;
	float speed;

	sf::Sound				* sound1;
	sf::Sound				* sound2;
	tanks::GameSettings		* m_settings;
	tanks::BulletType bvalue;

	virtual void redefine()
	{
		GameObject::redefine();
		m_hits = 0;
		m_kills = 0;
		m_helth = 10;
		shoot_delay = 0;
	};

	void dec_helth(tanks::BulletType value)
	{
		m_helth = m_helth - value;
		if (m_helth <= 0)
			state = ObjectState::DESTROYED;
	}

	void fire();

	void init()
	{
		gf = new GravityForce(this);
		sf = new StraightForce(this);
		af = new AngleForce(this);

		forces.push_back(gf);
		forces.push_back(sf);
		forces.push_back(af);
		//GameObject::init();

		m_hits = 0;
		m_kills = 0;
		m_helth = 10;
		shoot_delay = 0;

		sound1 = m_settings->sound1;
		sound2 = m_settings->sound2;
		
		bvalue = tanks::BulletType::TYPE1;
		speed = 2;
	}

	void add_interacts(std::vector<GameObject*> interacts)
	{
		for (int i = 0; i < interacts.size(); i++)
		{
			GameObject * go = interacts[i];
			if (go == this)
				continue;

			if (dynamic_cast<Terrain*>(go))
			{
				gf->add_collider(go);
				m_interacts.push_back(go);
				continue;
			}

			if (dynamic_cast<Tank*>(go))
			{
				sf->add_collider(go);
				m_interacts.push_back(go);
				continue;
			}

			if (dynamic_cast<House*>(go))
			{
				sf->add_collider(go);
				m_interacts.push_back(go);
				continue;
			}
		}
	};

	void add_tower(TankTower *obj)
	{
		tower = obj;
		add_child(obj);
	}

	Tank(Render *render, PhysicsBody * body, tanks::GameSettings * settings, int id, tanks::ModelType type)
		:GameObject(render, body, id, type), m_settings(settings)
	{
		init();
	};

	//virtual void play(float delta_time) =0;
};

#endif /* TANK_H_ */