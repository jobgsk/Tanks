#ifndef ENEMY_H_
#define ENEMY_H_

#include "Tank.h"
#include "Player.h"
#include "House.h"

#include "../AI.h"
#include "../movement.h"

class Enemy : public Tank {
	//AI ai;
	MovementBehavior *m_movement;
	VisionDetector * m_vision;

public:
	GameObject* m_target;
	std::vector<PhysicsBody*> obstacles;
	std::vector<GameObject*> waiting;

	virtual void redefine()
	{
		Tank::redefine();
	};

	void set_movement(std::vector<GameObject*> interacts, GameObject* target)
	{
		m_vision = new VisionDetector(this, 10.0);
		m_vision->set_target(target);
		m_target = target;

		for (int i = 0; i < interacts.size(); i++)
		{
			/*if (dynamic_cast<Player*>(interacts[i]))
			{
				target = ((Player*)interacts[i]);
				m_vision->set_target(target);
				continue;
			}
			*/
			if (dynamic_cast<House*>(interacts[i]))
			{
				obstacles.push_back(((House*)interacts[i])->m_body);
				m_vision->set_obstacles(interacts[i]);

				continue;
			}

			if (dynamic_cast<Enemy*>(interacts[i]))
			{
				obstacles.push_back(((Enemy*)interacts[i])->m_body);
				m_vision->set_obstacles(interacts[i]);

				continue;
			}
		}

		m_movement = new SteeringPipeline(m_body->m_position, m_body->m_direction, m_target->m_body, obstacles, speed);
		
	};

	Enemy(Render *render, PhysicsBody * body, tanks::GameSettings * settings, int id, tanks::ModelType type)
		:Tank(render, body, settings, id, type)
	{
	};

	void play(float delta_time);

	/*void fire()
	{

	};
	*/
};

#endif /* ENEMY_H_ */