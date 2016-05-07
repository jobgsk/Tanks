#ifndef PLAYER_H_
#define PLAYER_H_

#include "Tank.h"

class Player : public Tank {
public:
	bool move_forward;
	bool move_back;
	bool turn_right;
	bool turn_left;
	
	virtual void redefine()
	{
		Tank::redefine();
		reset_actions();
		m_helth = 20;
	};

	void reset_actions()
	{
		move_forward = false;
		move_back = false;
		turn_right = false;
		turn_left = false;
	}

	Player(Render *render, PhysicsBody * body, tanks::GameSettings * settings, int id, tanks::ModelType type)
		:Tank(render, body, settings, id, type)
	{
		reset_actions();
		m_helth = 20;
	};

	void play(float delta_time);
};

#endif /* PLAYER_H_ */