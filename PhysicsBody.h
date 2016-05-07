#ifndef PHYSICS_BODY_H_
#define PHYSICS_BODY_H_

#include "Vector3.h"
#include "math_helper.h"

class PhysicsBody
{
public:
	float m_mass;
	float m_dumping;
	Vector3<float> m_radius;

	Vector3<float> m_velocity;
	Vector3<float> m_position;
	Vector3<float> m_direction;
	Vector3<float> m_angle;

	void init()
	{
		m_velocity = Vector3<float>(0, 0, 0);
		m_position = Vector3<float>(0, 0, 0);
		m_direction = Vector3<float>(1, 0, 0);
		m_angle = Vector3<float>(0, 0, 0);

		m_mass = 100.f;
		m_dumping = 0.5;
	};

	PhysicsBody()
	{
		init();
	};

	PhysicsBody(Vector3<float> radius)
	{
		init();
		m_radius = radius;
	};

	void update_static(Vector3<float> position, float orientation)
	{
		m_position = Vector3<float>(position.x, 0, position.z);
		m_angle = Vector3<float>(0.0, orientation + tanks::grad_to_rad(-45), 0.0); //*aicore::M_180_PI
		
		Matrix4<float> r_matrix = Matrix4<float>();
		r_matrix.rotate(m_angle.x, m_angle.y, m_angle.z);
		m_direction = r_matrix.vProduct(1, 0, 1);
	};
	
	float get_radius()
	{
		return (m_radius.x > m_radius.z) ? m_radius.x : m_radius.z;
	}
};

#endif /* PHYSICS_BODY_H_ */