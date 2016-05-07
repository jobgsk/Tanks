#include "TankTower.h"

void TankTower::play(float delta_times)
{
	if (state == ObjectState::DESTROYED)
		return;

	m_body->m_position = parent->m_body->m_position;
	if (turn_left || turn_right)
	{
		if (turn_right)
		{
			af->set_force(5.0);
		}
		else
		{
			af->set_force(-5.0);
		}	
		af->exec(5);
		af->apply();
		m_angle += af->m_delta_angle;
	}

	


	reset_actions();
	state = ObjectState::CHANGED;
}

void TankTower::sync_parent()
{
	m_body->m_position = parent->m_body->m_position;
	m_body->m_angle = parent->m_body->m_angle + m_angle;

	Matrix4<float> r_matrix = Matrix4<float>();
	r_matrix.rotate(m_body->m_angle.x, m_body->m_angle.y, m_body->m_angle.z);
	m_body->m_direction = r_matrix.vProduct(1, 0, 1);
	state = ObjectState::CHANGED;
}