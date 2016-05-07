#ifndef STRAIGHT_FORCE_H_
#define STRAIGHT_FORCE_H_

#include "GameObject.h"
//#include "PhysicsForce.h"
#include "CollisionDetector.h"

class StraightForce : public PhysicsForce
{
	BoxCollider* m_collision_detector;
public:
	StraightForce(GameObject *go)
		:PhysicsForce(go)
	{
		m_collision_detector = new BoxCollider(this);
		m_velosity_max = 0.2;
	};

	bool exec(float delta_time);
	void apply();
	void reset();

	float get_max_velocity()
	{
		return m_velosity_max;
	};

	bool collide()
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			if (m_collision_detector->collide(m_colliders[i]))
			{
				m_collider = m_colliders[i];
				return true;
			}
				
		}
		return false;
	};
};

class SimpleForce : public PhysicsForce
{
	BoxCollider* m_collision_detector;
public:
	SimpleForce(GameObject *go)
		:PhysicsForce(go)
	{
		m_collision_detector = new BoxCollider(this);
		m_velosity_max = 10;
	};

	bool exec(float delta_time);
	void apply();

	float get_max_velocity()
	{
		return m_velosity_max;
	};

	void set_force(float force)
	{
		m_force = force;
	};

	bool collide()
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			if (m_collision_detector->collide(m_colliders[i]))
			{
				m_collider = m_colliders[i];
				return true;
			}

		}
		return false;
	};
};

class AngleForce : public PhysicsForce
{
public:
	AngleForce(GameObject *go)
		:PhysicsForce(go)
	{
	
	};
	
	float get_max_velocity()
	{
		return m_velosity_max;
	};

	void set_force(float force)
	{
		m_force = force;
		set_force(Vector3<float>(0.0, tanks::grad_to_rad(m_force), 0.0));
	};

	void set_force(Vector3<float> force)
	{
		v_force = force;
	};

	bool exec(float delta_time);
	void apply();

};

class GravityForce : public PhysicsForce
{
	TerrainCollider* m_collision_detector;
	float m_velosity_max;
public:
	
	GravityForce(GameObject *go)
		:PhysicsForce(go)
	{
		m_collision_detector = new TerrainCollider(this);
		m_velosity_max = 2;
	};
	float get_max_velocity()
	{
		return m_velosity_max;
	};

	bool exec(float delta_time);
	void apply();

	bool collide()
	{
		for (int i = 0; i < m_colliders.size(); i++)
		{
			if (m_collision_detector->collide(m_colliders[i]))
			{
				m_collider = m_colliders[i];
				return true;
			}
		}
		return false;
	};
};

#endif /* STRAIGHT_FORCE_H_ */