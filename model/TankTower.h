#ifndef TANK_TOWER_H_
#define TANK_TOWER_H_

#include "../GameObject.h"
#include "../StraightForce.h"

class TankTower : public GameObject {
public:
	bool turn_right;
	bool turn_left;

	AngleForce *af;
	Vector3<float> m_angle;
	std::vector<PhysicsForce*> forces;

	virtual void redefine()
	{
		GameObject::redefine();
		reset_actions();
		sync_parent();
	};

	void reset_actions()
	{
		turn_right = false;
		turn_left = false;
	}

	TankTower(Render *render, PhysicsBody * body, GameObject *tank, int id, tanks::ModelType type)
		:GameObject(render, body, id, type)
	{
		reset_actions();

		af = new AngleForce(this);
		forces.push_back(af);

		parent = tank;
	};

	void play(float delta_time);
	void sync_parent();
};

#endif /* TANK_TOWER_H_ */