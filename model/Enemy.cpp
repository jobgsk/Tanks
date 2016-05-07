
#include "Enemy.h"
#include "House.h"
#include "Terrain.h"

void Enemy::play(float delta_time)
{
	if (state == ObjectState::DESTROYED)
		return;

	if (state == ObjectState::WAITING)
	{
		bool active = true;
		//std::cout << " waiting " << m_id << " " << waiting.size() << std::endl;

		for (int i = 0; i < waiting.size(); i++)
		{
			if (waiting[i]->state != ObjectState::DESTROYED)
			{
				active = false;
				break;
			}
		}
		if (active)
			state = ObjectState::ACTIVE;
	}
	
	if (state == ObjectState::WAITING)
		return;


	//fire
	//if (m_vision->collide(target, 10))
	if (m_vision->find_target())
		fire();

	//std::cout << " shoot_delay " << delta_time << std::endl;
	if (shoot_delay > 0)
		shoot_delay -= delta_time*0.5;

	float target_distance = (m_target->m_body->m_position - m_body->m_position).magnitude();
	if (target_distance < 10)
		return;

	aicore::SteeringOutput steer = m_movement->update(delta_time);
	m_body->update_static(m_movement->kinematic->position, m_movement->kinematic->orientation);
	
	state = ObjectState::CHANGED;
	tower->sync_parent();
	
	for (int i = 0; i < childs.size(); i++) {
		childs[i]->play(delta_time);
	}

	//state = ObjectState::DESTROYED;
}