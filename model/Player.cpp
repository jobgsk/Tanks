
#include "../math_helper.h"
#include "Player.h"
#include "House.h"
#include "Terrain.h"

void Player::play(float delta_time)
{
	if (state == ObjectState::DESTROYED)
		return;

	//std::cout << " shoot_delay " << shoot_delay << std::endl;
	if (shoot_delay > 0)
		shoot_delay -= delta_time * 2;
	/*std::cout << " position x" << m_body.m_position.x
	<< " y " << m_body.m_position.y
	<< " z" << m_body.m_position.z << std::endl;
	*/
	gf->set_force(0.005);
	if (move_forward || move_back)
	{
		if (move_forward)
		{
			sf->set_force(2.5);
		}
		else
		{
			sf->set_force(-2.5);
		}
		reset_actions();
	}

	if (turn_left || turn_right)
	{
		if (turn_left)
		{
			af->set_force(7.5);
		}
		else
		{
			af->set_force(-7.5);
		}
		reset_actions();
	}

	//std::cout << " delta_time " << delta_time << std::endl;

	/*
	apply physics forces to the game object
	*/
	for (int j = 0; j < this->forces.size(); j++)
	{
		if (!this->forces[j]->exec(delta_time / 20))
			continue;

		state = ObjectState::CHANGED;

		if (this->forces[j]->collide())
		{
			this->forces[j]->reset();
		}
		else
		{
			this->forces[j]->apply();
		}
	}
	
	if (state == ObjectState::CHANGED)
		tower->sync_parent();
	
	for (int i = 0; i < childs.size(); i++) 
	{
		childs[i]->play(delta_time);
	}

	//state = ObjectState::CHANGED;
}