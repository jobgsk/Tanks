#ifndef PHYSICS_FORCE_H_
#define PHYSICS_FORCE_H_

#include <vector>
#include <cmath>
#include <iostream>

#include "Vector3.h"
#include "Matrix4.h"
#include "math_helper.h"
 
class PhysicsForce
{
protected:
	bool m_direct = true;
public:
	GameObject *m_go;
	std::vector<GameObject*> m_colliders;
	GameObject* m_collider;

	float m_force;
	Vector3<float> v_force;
	float m_time;

	Vector3<float> m_delta_velocity;
	Vector3<float> m_delta_position;
	Vector3<float> m_delta_direction;
	Vector3<float> m_delta_angle;

	Vector3<float> m_velocity;
	//Vector3<float> m_position;
	//Vector3<float> m_direction;
	//Vector3<float> m_angle;
	float m_velosity_max;

	PhysicsForce(GameObject *go)
	{
		m_go = go;
		m_time = 0;

		m_delta_velocity = Vector3<float>(0, 0, 0);
		m_delta_position = Vector3<float>(0, 0, 0);
		m_delta_direction = Vector3<float>(0, 0, 0);
		m_delta_angle = Vector3<float>(0, 0, 0);

		m_velocity = Vector3<float>(0, 0, 0);
		//m_position = Vector3<float>(0, 0, 0);
		//m_direction = Vector3<float>(0, 0, 0);
		//m_angle = Vector3<float>(0, 0, 0);

		m_force = 0;
		v_force = Vector3<float>(0, 0, 0);
	};

	virtual float get_max_velocity() = 0;
	virtual void set_force(float force)
	{
		if (m_velocity.magnitude() < get_max_velocity())
		{
			//std::cout << " velosity max " << get_max_velocity() << std::endl;
			m_force = force;
		}
	};

	virtual void set_force(Vector3<float> force)
	{
		if (m_velocity.magnitude() < get_max_velocity())
			v_force = force;
	};


	void add_collider(GameObject* obj)
	{
		m_colliders.push_back(obj);
	};

	virtual bool collide()
	{
		return false;
	};

	virtual bool exec(float delta_time)
	{
		return false;
	};

	virtual void apply() {};
	virtual void reset()
	{
		m_velocity = Vector3<float>(0, 0, 0);
		
		m_delta_velocity = Vector3<float>(0, 0, 0);
		m_delta_position = Vector3<float>(0, 0, 0);
	};
};


#endif /* PHYSICS_FORCE_H_ */