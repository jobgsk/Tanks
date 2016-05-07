#ifndef BULLET_H_
#define BULLET_H_

#include "../gameObject.h"
#include "../StraightForce.h"
#include "../particles/ParticleSystem.h"

#include "Tank.h"
#include "House.h"

class Bullet : public GameObject {


public:
	std::vector<PhysicsForce*> forces;
	SimpleForce *sf;
	partic::ParticleSystem* m_particle;

	float shoot_delay;
	tanks::BulletType bvalue;
	float sf_value;

	virtual void redefine()
	{
		GameObject::redefine();
		state = ObjectState::DESTROYED;
	};

	void init()
	{
		m_body->m_mass = 1.1;
		m_body->m_dumping = 0.01;
		sf_value = 0.02;

		sf = new SimpleForce(this);
		forces.push_back(sf);

		state = ObjectState::DESTROYED;
		shoot_delay = 0;
	}

	Bullet(
		Render *render, 
		PhysicsBody * body, 
		partic::ParticleSystem* particle, 
		int id, tanks::ModelType type, 
		tanks::BulletType btype)
			:GameObject(render, body, id, type), 
			m_particle(particle),
			bvalue(btype)
	{
		init();
	};

	void add_interacts(std::vector<GameObject*> interacts)
	{
		for (int i = 0; i < interacts.size(); i++)
		{
			GameObject * go = interacts[i];
			if (go == this)
				continue;

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

	virtual void update()
	{
	};
	void play(float delta_time);
	void draw();

};

#endif /* BULLET_H_ */