#include "Tank.h"

void Tank::fire()
{

	if (shoot_delay > 0)
		return;

	GameObject * bullet;
	if (bvalue == tanks::BulletType::TYPE1)
		bullet = m_bullets1_holder->front();
	else if (bvalue == tanks::BulletType::TYPE2)
		bullet = m_bullets2_holder->front();
	else
		bullet = m_bullets3_holder->front();

	bullet->set_instigator(this);
	
	bullet->m_body->m_position = tower->m_body->m_position;
	bullet->m_body->m_direction = tower->m_body->m_direction;

	bullet->state = ObjectState::ACTIVE;
	
	if (bvalue == tanks::BulletType::TYPE1)
	{
		m_bullets1_holder->pop_front();
		m_bullets1_holder->push_back(bullet);
	}
	else if (bvalue == tanks::BulletType::TYPE2)
	{
		m_bullets2_holder->pop_front();
		m_bullets2_holder->push_back(bullet);
	}
	else
	{
		m_bullets3_holder->pop_front();
		m_bullets3_holder->push_back(bullet);
	}
	
	/*std::cout << "fire" << shoot_delay << " "
		<< bullet->m_body->m_position.x << " "
		<< bullet->m_body->m_position.y << " "
		<< bullet->m_body->m_position.z << std::endl;
		*/
	sound1->play();
	shoot_delay = 1000;
}