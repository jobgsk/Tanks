#include "StraightForce.h"

/*
	StraightForce
*/
bool StraightForce::exec(float delta_time)
{
	//float gravity = 10;
	//float friction = 0.3;
	//float f_force = friction * gravity * m_body->m_mass;

	Vector3<float> direction = m_go->m_body->m_direction;
	direction.normalize();

	if (m_force != 0)
	{
		if (m_force > 0)
			m_direct = true;
		else
			m_direct = false;

		float s_acceleration = std::abs(m_force) / m_go->m_body->m_mass;
		Vector3<float> v_acceleration = direction * s_acceleration;

		m_delta_velocity = v_acceleration * delta_time;
		/*
		((acceleration * (0.5)) * pow(delta_time, 2)) + (velocity * delta_time)
		*/
		m_delta_position = (m_velocity * delta_time) + m_delta_velocity;
		if (m_direct)
			m_velocity += m_delta_velocity;
		else
			m_velocity -= m_delta_velocity;
	}
	else
	{
		m_delta_velocity = Vector3<float>(0, 0, 0);
		m_delta_position = (m_velocity * delta_time);
	}

	
	float s_dumping = m_go->m_body->m_dumping;
	if (m_go->m_body->m_velocity.magnitude() < 0.01)
	{
		m_go->m_body->m_velocity = Vector3<float>(0, 0, 0);
		m_velocity = Vector3<float>(0, 0, 0);
	}
	else
	{
		//Vector3<float> v_dumping = direction * s_dumping;
		m_go->m_body->m_velocity *= s_dumping;
		m_velocity *= s_dumping;
	}

	m_force = 0;
	return true;
};

void StraightForce::apply()
{
	if (m_direct)
		m_go->m_body->m_velocity += m_delta_velocity;
	else
		m_go->m_body->m_velocity -= m_delta_velocity;
	
	m_go->m_body->m_position += m_delta_position;

	m_delta_velocity = Vector3<float>(0, 0, 0);
	m_delta_position = Vector3<float>(0, 0, 0);
};

void StraightForce::reset()
{
	/*m_go->m_body->m_velocity -= m_delta_velocity;

	if (m_direct)
	{
		m_go->m_body->m_position -= m_delta_position * 0.2f;
	}
	else
	{
		m_go->m_body->m_position += m_delta_position * 0.2f;
	}
	*/
	m_velocity = Vector3<float>(0, 0, 0);
	m_delta_velocity = Vector3<float>(0, 0, 0);
	m_delta_position = Vector3<float>(0, 0, 0);
};

/*
	Force without physics
*/
bool SimpleForce::exec(float delta_time)
{
	//std::cout << " m_force " << m_force << std::endl;
	if (m_force == 0)
		return false;

	Vector3<float> direction = m_go->m_body->m_direction;
	direction.normalize();
	m_delta_position = direction * m_force * delta_time;
	
	m_force = 0;
	return true;
};

void SimpleForce::apply()
{
	m_go->m_body->m_position += m_delta_position;
	
	m_delta_velocity = Vector3<float>(0, 0, 0);
	m_delta_position = Vector3<float>(0, 0, 0);
};


/*
	GravityForce
*/
bool GravityForce::exec(float delta_time)
{
	if (m_force != 0)
	{
		Vector3<float> direction = Vector3<float>(0, -1, 0);
		/*
		gravity = 10
		force = gravity * mass
		acceleration = force / mass
		*/
		float s_acceleration = std::abs(m_force);
		Vector3<float> v_acceleration = direction * s_acceleration;

		m_delta_velocity = v_acceleration * delta_time;
		/*
		((acceleration * (0.5)) * pow(delta_time, 2)) + (velocity * delta_time)
		*/
		m_delta_position = (m_velocity * delta_time) + m_delta_velocity;
		m_velocity += m_delta_velocity;
		m_force = 0;
		return true;
	}
	else
	{
		m_delta_velocity = Vector3<float>(0, 0, 0);
		return false;
	}
};

void GravityForce::apply()
{

	m_go->m_body->m_velocity += m_delta_velocity;
	m_go->m_body->m_position += m_delta_position;
	
	m_delta_velocity = Vector3<float>(0, 0, 0);
	m_delta_position = Vector3<float>(0, 0, 0);
};


/*
	AngleForce
*/
bool AngleForce::exec(float delta_time)
{
	if (v_force.magnitude() == 0)
	{
		m_delta_angle = Vector3<float>(0, 0, 0);
		return false;
	}

	m_delta_angle = v_force;
	//if (m_force < 0)
	//	m_delta_angle.invert();

	m_go->m_body->m_angle += m_delta_angle;

	Matrix4<float> r_matrix = Matrix4<float>();
	r_matrix.rotate(m_go->m_body->m_angle.x, m_go->m_body->m_angle.y, m_go->m_body->m_angle.z);
	m_go->m_body->m_direction = r_matrix.vProduct(1, 1, 1);

	m_force = 0;
	v_force = Vector3<float>(0, 0, 0);
	return true;
};

void AngleForce::apply()
{

};